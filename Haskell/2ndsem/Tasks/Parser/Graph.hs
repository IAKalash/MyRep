module Graph where
import Text.ParserCombinators.Parsec
import Data.Char (isAlphaNum)

data Graph = Digraph ID [Node] [Edge] [Attr]
    deriving (Show)

data Node = Node ID [Attr]
    deriving (Show)

data Edge = Edge ID ID [Attr]
    deriving (Show)

data Attr = Attr ID ID
    deriving (Show)

type ID = String

getName :: Parser String
getName = many1 (alphaNum <|> char '_')

skipSpaces :: Parser ()
skipSpaces = skipMany space

graph :: Parser Graph
graph = do
    skipSpaces
    string "digraph"
    skipSpaces
    name <- getName
    skipSpaces
    char '{'
    skipSpaces
    (nodes, edges, attrs) <- getStmts
    skipSpaces
    char '}'
    skipSpaces
    return (Digraph name nodes edges attrs)

getStmts :: Parser ([Node], [Edge], [Attr])
getStmts = do
    skipSpaces
    stmts <- many (do
        stmt <- getStmt
        skipSpaces
        return stmt)
    let nodes = concat [ns | (ns, _, _) <- stmts]
        edges = concat [es | (_, es, _) <- stmts]
        attrs = concat [as | (_, _, as) <- stmts]
        edgeNodeIds = [id | Edge from to _ <- edges, id <- [from, to]]
        uniqueIds = foldr (\id acc -> if id `elem` acc then acc else id : acc) [] edgeNodeIds
        extraNodes = [Node id [] | id <- uniqueIds, not (any (\(Node id' _) -> id' == id) nodes)]
        allNodes = nodes ++ extraNodes
    return (allNodes, edges, attrs)

getStmt :: Parser ([Node], [Edge], [Attr])
getStmt = do
    skipSpaces
    key <- getName
    skipSpaces
    next <- many (char '=')
    if not (null next) then do
        skipSpaces
        value <- getName
        skipSpaces
        optional (char ';')
        return ([], [], [Attr key value])
    else do
        nextArrow <- many (string "->")
        if not (null nextArrow) then do
            skipSpaces
            result <- addEdges key
            skipSpaces
            optional (char ';')
            return result
        else do
            attrs <- getAttrs
            skipSpaces
            optional (char ';')
            return ([Node key attrs], [], [])

addEdges :: String -> Parser ([Node], [Edge], [Attr])
addEdges from = do
    skipSpaces
    to <- getName
    skipSpaces
    next <- many (string "->")
    if null next then do
        attrs <- getAttrs
        return ([], [Edge from to attrs], [])
    else do
        attrs <- getAttrs
        skipSpaces
        (_, moreEdges, _) <- addEdges to
        return ([], Edge from to attrs : moreEdges, [])

getAttrs :: Parser [Attr]
getAttrs = do
    next <- many (char '[')
    if null next then return []
    else do
        skipSpaces
        attrs <- sepEndBy addAttr (char ',' <|> char ';')
        skipSpaces
        char ']'
        return attrs

addAttr :: Parser Attr
addAttr = do
    skipSpaces
    key <- getName
    skipSpaces
    char '='
    skipSpaces
    Attr key <$> getName

main :: IO ()
main = do
    text <- readFile "graph.txt"
    case parse graph "" text of
        Left err -> print err
        Right g -> do
            putStrLn "Read graph:"
            print g