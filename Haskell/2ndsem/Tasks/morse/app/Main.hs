module Main where
import System.Environment
import Morse

main :: IO()
main = do
    putStrLn "Started successfully"
    mode <- getArgs
    if mode == ["from"] then
        from
    else if mode == ["to"] then
        to
    else putStrLn "Incorrect input"

from :: IO()
from = do
    arg <- getLine
    if arg /= "" then do
        print (morseToString $ words arg)
        from
    else putStrLn "Bye"

to :: IO()
to = do
    arg <- getLine
    if arg /= "" then do
        if isJust $ stringToMorse arg then
             putStrLn (unwords (fromMaybe $ stringToMorse arg))
        else putStrLn "Incorrect input"
        to
    else putStrLn "Bye"
