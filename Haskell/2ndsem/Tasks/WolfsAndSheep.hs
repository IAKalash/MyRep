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
        show (Game sheep wolfs) = "  abcdefgh" ++ printGame (Game sheep wolfs)

printGame :: Game -> String
printGame (Game sheep wolfs) =  "\n8 " ++ checkLine sheep wolfs '8' line  ++
                                "\n7 " ++ checkLine sheep wolfs '7' line1 ++
                                "\n6 " ++ checkLine sheep wolfs '6' line  ++
                                "\n5 " ++ checkLine sheep wolfs '5' line1 ++
                                "\n4 " ++ checkLine sheep wolfs '4' line  ++
                                "\n3 " ++ checkLine sheep wolfs '3' line1 ++
                                "\n2 " ++ checkLine sheep wolfs '2' line  ++
                                "\n1 " ++ checkLine sheep wolfs '1' line1

checkLine :: Position -> [Position] -> Char -> String -> String
checkLine sheep wolfs sym str | last (show sheep) == sym = replace str 'S' (ord (head (show sheep)) - 97)
                              | any (((== [sym]) . tail) . show) wolfs = replWolfs str 'W' (map ((\x -> x - 97) . ord) (filter (`elem` "abcdefgh") (show wolfs)))
                              | otherwise = str

replWolfs :: String -> Char -> [Int] -> String
replWolfs xs sym [] = xs
replWolfs xs sym [x] = replace xs sym x
replWolfs xs sym (y:ys) = replWolfs (replace xs sym y) sym ys

replace :: String -> Char -> Int -> String
replace (x:xs) sym place | place == 0 = sym : xs
                         | otherwise = x : replace xs sym (place - 1)

line :: String
line = " . . . ."
line1 :: String
line1 = ". . . ."

data GameResult = SheepWin | WolfsWin
        deriving (Show)

startSheep :: Position
startSheep = Position 'a' 1

startWolfs :: [Position]
startWolfs = [Position f 8 | f <- "bdfh"]

startGame :: Game
startGame = Game startSheep startWolfs

possibleSheepSteps :: Game -> [Step] -- list comprehension
possibleSheepSteps (Game (Position char num) [_,_,_,_]) = [Step (Position char num) (Position char2 (ord num2 - 48)) | char2 <- choose char "abcdefgh", num2 <- choose (chr (num + 48)) "87654321"]

choose :: Char -> String -> String
choose sym [] = []
choose sym [x] = []
choose sym (x:y:xs) | sym == x = [y]
                    | sym == y = x : choose sym (y:xs)
                    | otherwise = choose sym (y:xs)


possibleWolfsSteps :: Game -> [Step] -- list comprehension
possibleWolfsSteps (Game _ [Position ch1 n1, Position ch2 n2, Position ch3 n3, Position ch4 n4]) = unique
        [Step (Position char num) (Position char2 (ord num2 - 48)) | char <- ch1 : ch2 : ch3 : [ch4], num <- n1 : n2 : n3 : [n4], char2 <- choose char "abcdefgh", num2 <- chooseW (chr (num + 48)) "87654321"]

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
possibleSheepSteps2 = undefined

possibleWolfsSteps2 :: Game -> [Step] -- do-notation
possibleWolfsSteps2 = undefined

simpleTurn :: Game -> Either GameResult Game
simpleTurn = undefined

run :: Monad m => (a -> m a) -> a -> m a
run = undefined

loggedTurn :: Game -> (WriterT [Step] (Either GameResult)) Game
loggedTurn = undefined
loggedTurn' :: Game -> ExceptT GameResult (Writer [Step]) Game
loggedTurn' = undefined



