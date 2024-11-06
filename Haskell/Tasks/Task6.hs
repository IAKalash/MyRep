import Data.Char
import Text.Read (Lexeme(String))

encrypt :: Int -> Char -> Char
encrypt n sym | isLower sym = chr (97 + mod (ord sym - 97 + n) 26)
              | isUpper sym = chr (65 + mod (ord sym - 65 + n) 26)
              | otherwise = sym

caesarEncrypt :: String -> Int -> String
caesarEncrypt str shift = map (encrypt shift) str

caesarDecrypt :: String -> Int -> String
caesarDecrypt str shift =  map (encrypt (-shift)) str

caesarCrack :: String -> [String]
caesarCrack str = crack 1 str
        where crack :: Int -> String -> [String]
              crack count str | count == 26 = []
                              | otherwise = caesarDecrypt str count : crack (count + 1) str

isUnique :: String -> Bool
isUnique [] = True
isUnique (x:xs) = notElem x xs && isUnique xs 

delVow :: String -> String
delVow str = del str "aeiouyAEIOUY"
    where del :: String -> String -> String
          del [] vow = []
          del (x:xs) vow | elem x vow = del xs vow
                         | otherwise = x : del xs vow

isAnagram :: String -> String -> Bool
isAnagram str1 str2 | sum (map (ord . toLower) str1) == sum (map (ord . toLower) str2) = True
                    | otherwise = False


longPref :: [String] -> String
longPref [] = []
longPref [x] = x
longPref (s : str) | isEq (map head (s:str)) = head s : longPref (map tail (s:str))
                   | otherwise = []
                   where isEq [] = False
                         isEq (x:y:xs) | x == y = isEq (y:xs)
                                       | otherwise = False
                         isEq x = True

anagramsFor :: String -> [String] -> [String]
anagramsFor word list = foldl (func) word list
        where func (x:xs) y | isAnagram x y = 
                            | otherwise = []