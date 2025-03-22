module WolfsAndSheep where

import Control.Monad.Trans
import Control.Monad.Trans.Except
import Control.Monad.Trans.Writer
import Data.Char
import System.Random
import System.IO.Unsafe ( unsafePerformIO )


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
checkLine sheep wolfs sym str | num sheep == sym = replace (checkLine (Position 'a' 10) wolfs sym str) 'S' (ord (head (show sheep)) - 97)
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
possibleWolfsSteps (Game sheep wolfs) = isCollision (unique [Step pos (Position char2 (ord num2 - 48))
        | pos <- wolfs , char2 <- choose (char pos) "abcdefgh", num2 <- chooseW (chr (num pos + 48)) "87654321"]) (sheep : wolfs)

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
possibleWolfsSteps2 (Game sheep wolfs) = isCollision (unique f) (sheep : wolfs)
        where f = do
                pos <- wolfs
                ch <- choose (char pos) "abcdefgh"
                n <- chooseW (chr (num pos + 48)) "87654321"
                return (Step pos (Position ch (ord n - 48)))


simpleTurn :: Game -> Either GameResult Game
simpleTurn (Game sheep wolfs) | num sheep == 8 = Left SheepWin
                              | null (possibleSheepSteps (Game sheep wolfs)) = Left WolfsWin
                              | null (possibleWolfsSteps (Game sheep wolfs)) = Left SheepWin
                              | otherwise = do
                                let shPos = sheepStep $ head $ possibleSheepSteps (Game sheep wolfs)
                                return (Game shPos (wolfsStep wolfs (head $ possibleWolfsSteps (Game shPos wolfs))))


sheepStep :: Step -> Position
sheepStep (Step _ pos) = pos

wolfsStep :: [Position] -> Step -> [Position]
wolfsStep [x] (Step oldpos newpos) = [newpos]
wolfsStep (x:xs) (Step oldpos newpos) | oldpos == x = newpos : xs
                                      | otherwise = x : wolfsStep xs (Step oldpos newpos)

run :: Monad m => (a -> m a) -> a -> m a
run turn game = turn game >>= run turn

loggedTurn :: Game -> (WriterT [Step] (Either GameResult)) Game
loggedTurn (Game sheep wolfs) | num sheep == 8 = lift $ Left SheepWin
                              | null (possibleSheepSteps (Game sheep wolfs)) = lift $ Left WolfsWin
                              | null (possibleWolfsSteps (Game sheep wolfs)) = lift $ Left SheepWin
                              | otherwise = do
                                let shStep = head $ possibleSheepSteps (Game sheep wolfs)
                                let wlStep = head $ possibleWolfsSteps (Game (sheepStep shStep) wolfs)
                                tell $ shStep : [wlStep]
                                return (Game (sheepStep shStep) (wolfsStep wolfs wlStep))

loggedTurn' :: Game -> ExceptT GameResult (Writer [Step]) Game
loggedTurn' (Game sheep wolfs) | num sheep == 8 = ExceptT $ return $ Left SheepWin
                               | null (possibleSheepSteps (Game sheep wolfs)) = ExceptT $ return $ Left WolfsWin
                               | null (possibleWolfsSteps (Game sheep wolfs)) = ExceptT $ return $ Left SheepWin
                               | otherwise = do
                                let shStep = head $ possibleSheepSteps (Game sheep wolfs)
                                let wlStep = head $ possibleWolfsSteps (Game (sheepStep shStep) wolfs)
                                lift $ tell $ shStep : [wlStep]
                                return (Game (sheepStep shStep) (wolfsStep wolfs wlStep))

-- Функции отличаются выводом из-за разной конфигурации монад. Первая выводит только результат при завершении игры, 
-- а вторая выводит результат и лог (при промежуточных шагах обе функции выводят лог помимо промежуточного результата)
-- Предпочтительнее использовать вторую функцию чтобы не терять логи

randomTurn :: Game -> ExceptT GameResult (Writer [Step]) Game
randomTurn (Game sheep wolfs) | num sheep == 8 = ExceptT $ return $ Left SheepWin
                              | null (possibleSheepSteps (Game sheep wolfs)) = ExceptT $ return $ Left WolfsWin
                              | null (possibleWolfsSteps (Game sheep wolfs)) = ExceptT $ return $ Left SheepWin
                              | otherwise = do
                                let shStep = rnd $ possibleSheepSteps (Game sheep wolfs)
                                let step = possibleWolfsSteps (Game (sheepStep shStep) wolfs)
                                case step of
                                        [] -> ExceptT $ return $ Left SheepWin
                                        _ -> do
                                                let wlStep = rnd step
                                                lift $ tell [shStep,wlStep]
                                                return (Game (sheepStep shStep) (wolfsStep wolfs wlStep))

rnd :: [Step] -> Step
rnd steps = unsafePerformIO $ do
    randNum <- randomRIO (0, len steps - 1)
    return $ steps !! randNum

len :: [a] -> Int
len = foldr (\ x -> (+) 1) 0

runGame :: Game -> IO [Step] -- is needed only for playerTurn (Task 6)
runGame game = do
        (res, log) <- playerTurn game
        case res of 
                Left SheepWin -> do
                        print res
                        putStrLn "Log:"
                        return log
                Left WolfsWin -> do
                        print res
                        putStrLn "Log:"
                        return log
                Right next -> do
                        rest <- runGame next
                        return (log ++ rest)

--PlayerTurn не работает с оператором >>= и run из-за наличия в сигнатуре "грязной" монады IO, которую невозможно "развернуть"

playerTurn :: Game -> IO (Either GameResult Game, [Step])
playerTurn game = runWriterT (runExceptT (playerTurn' game))

playerTurn' :: Game -> ExceptT GameResult (WriterT [Step] IO) Game 
playerTurn' (Game sheep wolfs) | num sheep == 8 = ExceptT $ return $ Left SheepWin
                              | null (possibleSheepSteps (Game sheep wolfs)) = ExceptT $ return $ Left WolfsWin
                              | null (possibleWolfsSteps (Game sheep wolfs)) = ExceptT $ return $ Left SheepWin
                              | otherwise = do
                                liftIO $ print $ Game sheep wolfs
                                liftIO $ putStrLn ("Possible turns: " ++ show (possibleSheepSteps (Game sheep wolfs)))
                                liftIO $ putStrLn "Print the new position of the sheep like in this way: b2"
                                line <- liftIO getLine
                                let choise = Step sheep (Position (head line) ((\x -> x - 48) $ ord $ last line))
                                if choise `elem` possibleSheepSteps (Game sheep wolfs)
                                        then do 
                                                let step = possibleWolfsSteps (Game (sheepStep choise) wolfs)
                                                case step of
                                                        [] -> ExceptT $ return $ Left SheepWin
                                                        _ -> do
                                                                let wlStep = rnd step
                                                                lift $ tell [choise,wlStep]
                                                                return (Game (sheepStep choise) (wolfsStep wolfs wlStep))
                                        else do
                                                liftIO $ putStrLn "\nIncorrect step"
                                                playerTurn' (Game sheep wolfs)