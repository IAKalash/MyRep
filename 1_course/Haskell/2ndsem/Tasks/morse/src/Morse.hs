module Morse where
import qualified Data.Map as M
import Data.Char (toLower)

type Morse = String

morseCodes :: M.Map Char Morse
morseCodes = M.fromList [
    ('a', ".-"),
    ('b', "-..."),
    ('c', "-.-."),
    ('d', "-.."),
    ('e', "."),
    ('f', "..-."),
    ('g', "--."),
    ('h', "...."),
    ('i', ".."),
    ('j', ".---"),
    ('k', "-.-"),
    ('l', ".-.."),
    ('m', "--"),
    ('n', "-."),
    ('o', "---"),
    ('p', ".--."),
    ('q', "--.-"),
    ('r', ".-."),
    ('s', "..."),
    ('t', "-"),
    ('u', "..-"),
    ('v', "...-"),
    ('w', ".--"),
    ('x', "-..-"),
    ('y', "-.--"),
    ('z', "--.."),
    ('1', ".----"),
    ('2', "..---"),
    ('3', "...--"),
    ('4', "....-"),
    ('5', "....."),
    ('6', "-...."),
    ('7', "--..."),
    ('8', "---.."),
    ('9', "----."),
    ('0', "-----"),
    (' ', "   ")
  ]


fromMaybe :: Maybe a -> a
fromMaybe (Just a) = a
fromMaybe Nothing = error ""

isJust :: Maybe a -> Bool
isJust (Just _) = True
isJust Nothing = False

chr :: [(Char, String)] -> Char
chr [(char, _)] = char

charToMorse :: Char -> Maybe Morse
charToMorse char = lookup (toLower char) (M.toList morseCodes)

stringToMorse :: String -> Maybe [Morse]
stringToMorse str | all (isJust . charToMorse) str = Just (map (fromMaybe . charToMorse) str)
                  | otherwise = Nothing

morseToChar :: Morse -> Maybe Char
morseToChar mor | mor `elem` M.elems morseCodes = Just (chr (filter p (M.assocs morseCodes)))
                | otherwise = Nothing
                where p :: (Char, String) -> Bool
                      p (_, str) | mor == str = True
                                   | otherwise = False

morseToString :: [Morse] -> Maybe String
morseToString list | all (`elem` M.elems morseCodes) list = Just (map (fromMaybe . morseToChar) list)
                   | otherwise = Nothing