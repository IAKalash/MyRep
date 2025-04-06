-- data Tree a = Empty | Node a (Tree a) (Tree a)
--     deriving (Show, Eq)


-- isStr :: Tree a -> Bool
-- isStr Empty = True
-- isStr (Node _ Empty Empty) = True
-- isStr (Node _ Empty (Node _ _ _)) = False
-- isStr (Node _ (Node _ _ _) Empty) = False
-- isStr (Node _ a b) = isStr a && isStr b

-- main :: IO ()
-- main = putStrLn "Hello, World"

-- main :: IO ()
-- main = do
--     putStrLn "Hello, what is your name?"
--     name <- getLine
--     putStrLn ("Hello, " ++ name ++ ", nice to meet you!")

-- main :: IO ()
-- import Data.Char
-- main = do
--     putStrLn "Ваше имя?"
--     firstName <- getLine
--     putStrLn "Ваша фамилия?"
--     lastName <- getLine
--     let bigFirstName = map toUpper firstName
--         bigLastName = map toUpper lastName
--     putStrLn $ "Привет, " ++ bigFirstName ++ " " ++ bigLastName ++ ", как дела?"

produceTwo :: IO Int
produceTwo = do return 1
                return 2

printList :: [Int] -> IO ()
printList [] = return ()
printList (x:xs) = do
                        print x
                        printList xs

readUntil :: (String -> Bool) -> IO [String]
readUntil f = do
                str <- getLine
                if f str
                    then
                        return []
                    else
                        do
                            lines <- readUntil f
                            return (str : lines)


cond :: IO Bool
cond = do
            print "Continue? Yes/No"
            str <- getLine
            if (str == "Yes")
                then do
                    return (True)
                else
                    return (False)

while :: IO Bool -> IO () -> IO ()
while cond op = do
                    bool <- cond 
                    if bool then 
                                do
                                op
                                while cond op
                        else
                            return ()



-- words' :: IO String -> [String]
-- words' = do
--             word <- getLine
--             if (word /= "")
--                 then do
--                     lines <- words'
--                     word : lines
--                 else
--                     []

-- reverseWords :: String -> String
-- reverseWords = unwords . map reverse . words'
