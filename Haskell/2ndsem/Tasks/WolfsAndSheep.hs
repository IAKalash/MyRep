module WolfsAndSheep where

import Control.Monad.Trans.Except
import Control.Monad.Trans.Writer
import Data.Char

-- Положение на доске
data Position = Position {f :: Char, r :: Int}
        deriving (Eq)

instance Show Position where
    show :: Position -> String
    show (Position f r) = f : show r

-- Один ход
data Step = Step {from :: Position, to :: Position}
        deriving (Eq)

instance Show Step where
    show (Step f t) = show f ++ " -> " ++ show t

data Game = Game {sheep :: Position, wolfs :: [Position]}
        deriving (Eq)

instance Show Game where
        show :: Game -> String
        show (Game sheep wolfs) = "\n  abcdefgh" ++ printGame (Game sheep wolfs)

printGame :: Game -> String
printGame (Game sheep wolfs) =  "\n8 " ++ checkLine sheep wolfs 8 line  ++
                                "\n7 " ++ checkLine sheep wolfs 7 line1 ++
                                "\n6 " ++ checkLine sheep wolfs 6 line  ++
                                "\n5 " ++ checkLine sheep wolfs 5 line1 ++
                                "\n4 " ++ checkLine sheep wolfs 4 line  ++
                                "\n3 " ++ checkLine sheep wolfs 3 line1 ++
                                "\n2 " ++ checkLine sheep wolfs 2 line  ++
                                "\n1 " ++ checkLine sheep wolfs 1 line1

checkLine :: Position -> [Position] -> Int -> String -> String
checkLine sheep wolfs sym str | num sheep == sym = replace str 'S' (ord (head (show sheep)) - 97)
                              | any ((==sym) . num) wolfs = replWolfs (map ((\x -> x - 97) . ord . char) (isInLine sym wolfs)) str
                              | otherwise = str

char :: Position -> Char
char (Position char _) = char

num :: Position -> Int
num (Position _ n) = n

isInLine :: Int -> [Position] -> [Position]
isInLine line [] = []
isInLine line (x:xs) | num x == line = x : isInLine line xs
                     | otherwise = isInLine line xs

replWolfs :: [Int] -> String -> String
replWolfs xs line = foldl (`replace` 'W') line xs

replace :: String -> Char -> Int -> String
replace [x] sym place = [sym]
replace (x:xs) sym place | place == 0 = sym : xs
                         | otherwise = x : replace xs sym (place - 1)

line :: String
line = " . . . ."
line1 :: String
line1 = ". . . . "

data GameResult = SheepWin | WolfsWin
        deriving (Show)

startSheep :: Position
startSheep = Position 'a' 1

startWolfs :: [Position]
startWolfs = [Position f 8 | f <- "bdfh"]

startGame :: Game
startGame = Game startSheep startWolfs

possibleSheepSteps :: Game -> [Step] -- list comprehension
possibleSheepSteps (Game (Position char num) wolfs) = isCollision [Step (Position char num) (Position char2 (ord num2 - 48)) | char2 <- choose char "abcdefgh", num2 <- choose (chr (num + 48)) "87654321"] (Position char num : wolfs)

choose :: Char -> String -> String
choose sym [] = []
choose sym [x] = []
choose sym (x:y:xs) | sym == x = [y]
                    | sym == y = x : choose sym (y:xs)
                    | otherwise = choose sym (y:xs)


possibleWolfsSteps :: Game -> [Step] -- list comprehension
possibleWolfsSteps (Game sheep [Position ch1 n1, Position ch2 n2, Position ch3 n3, Position ch4 n4]) = isCollision (unique
        [Step (Position char num) (Position char2 (ord num2 - 48)) | char <- ch1 : ch2 : ch3 : [ch4], num <- n1 : n2 : n3 : [n4], char2 <- choose char "abcdefgh", num2 <- chooseW (chr (num + 48)) "87654321"]) (sheep : [Position ch1 n1, Position ch2 n2, Position ch3 n3, Position ch4 n4])

isCollision :: [Step] -> [Position] -> [Step]
isCollision [] ws = []
isCollision ((Step oldpos newpos):xs) ws | newpos `elem` ws = isCollision xs ws
                                         | otherwise = Step oldpos newpos : isCollision xs ws

chooseW :: Char -> String -> String
chooseW sym [] = []
chooseW sym [x] = []
chooseW sym (x : xs) | x == sym = [head xs]
                     | otherwise = chooseW sym xs

unique :: [Step] -> [Step]
unique [] = []
unique (x:xs) | x `notElem` xs = x : unique xs
              | otherwise = unique xs

possibleSheepSteps2 :: Game -> [Step] -- do-notation
possibleSheepSteps2 (Game (Position char num) wolfs) = isCollision (unique f) (Position char num : wolfs)
        where f = do
                ch <- choose char "abcdefgh"
                n <- choose (chr (num + 48)) "87654321"
                return (Step (Position char num) (Position ch (ord n - 48)))

possibleWolfsSteps2 :: Game -> [Step] -- do-notation
possibleWolfsSteps2 (Game sheep [Position ch1 n1, Position ch2 n2, Position ch3 n3, Position ch4 n4]) = isCollision (unique f) (sheep : [Position ch1 n1, Position ch2 n2, Position ch3 n3, Position ch4 n4])
        where f = do
                char <- ch1 : ch2 : ch3 : [ch4]
                num <- n1 : n2 : n3 : [n4]
                ch <- choose char "abcdefgh"
                n <- chooseW (chr (num + 48)) "87654321"
                return (Step (Position char num) (Position ch (ord n - 48)))


simpleTurn :: Game -> Either GameResult Game
simpleTurn (Game (Position ch n) wolfs) | n == 8 = Left SheepWin
                                        | null (possibleSheepSteps (Game (Position ch n) wolfs)) = Left WolfsWin
                                        | otherwise =
                                                return (Game (sheepStep $ head $ possibleSheepSteps (Game (Position ch n) wolfs))
                                                (wolfsStep wolfs (head $ possibleWolfsSteps (Game (Position ch n) wolfs))))


sheepStep :: Step -> Position
sheepStep (Step _ pos) = pos

wolfsStep :: [Position] -> Step -> [Position]
wolfsStep [x] (Step oldpos newpos) = [newpos]
wolfsStep (x:xs) (Step oldpos newpos) | oldpos == x = newpos : xs
                                      | otherwise = x : wolfsStep xs (Step oldpos newpos)

run :: Monad m => (a -> m a) -> a -> m a
run turn = 

loggedTurn :: Game -> (WriterT [Step] (Either GameResult)) Game
loggedTurn = undefined
loggedTurn' :: Game -> ExceptT GameResult (Writer [Step]) Game
loggedTurn' = undefined