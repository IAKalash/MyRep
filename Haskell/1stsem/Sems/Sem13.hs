-- https://regex101.com/

-- ab+

-- ([0-9]{4})-([0-9]|1[0-2])-(3[01]|2[0-9]|1[0-9]|[1-9])

-- ([aeyuioAEUIOY])[A-Za-z]{2,}

-- [A-Z][A-Za-z]*

-- [A-Za-z]+-\n[A-Za-z]+

import Text.Regex.Posix

isCorrectHaskellFile :: String -> Bool
isCorrectHaskellFile filename = filename =~ "\\.hs$"

is :: String -> Bool
is str = str =~ "^[Hh][Ii][.,?!]{0,} "

isBin :: String -> Bool
isBin str = str =~ "^([01]+)+$"