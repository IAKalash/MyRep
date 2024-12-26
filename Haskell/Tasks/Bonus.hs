import Text.Regex.PCRE

getWords :: IO()
getWords = do
    filePath <- getLine
    file <- readFile filePath
    print (getWords' file)

getWords' :: String -> [String]
getWords' content = getAllTextMatches (content =~ "[^{}]({([^{}]+|(?1))})[^{}}]") :: [String]