import Text.ParserCombinators.Parsec
import Data.Char

data Graph = Digraph ID [Node] [Edge] [Attr]
        deriving (Show)
data Node = Node ID [Attr]
        deriving (Show)
data Edge = Edge ID ID [Attr]
        deriving (Show)
data Attr = Attr ID ID
        deriving (Show)
type ID = String

identifier :: Parser String
identifier = many1 (alphaNum <|> oneOf "_") -- Поддержка символа "_" для имён вроде "graph_name"

-- Парсер всего графа
graph :: Parser Graph
graph = do
    string "digraph" >> spaces
    graphName <- identifier
    spaces >> string "{" >> spaces
    (nodes, edges, attrs) <- stmtList
    spaces >> string "}"
    return (Digraph graphName nodes edges attrs)

-- Парсер списка утверждений (stmt_list)
stmtList :: Parser ([Node], [Edge], [Attr])
stmtList = do
    stmts <- sepEndBy stmt (optional (char ';') >> spaces)
    let (nodes, edges, attrs) = foldl splitStmt ([], [], []) stmts
    return (nodes, edges, attrs)

-- Разделение утверждений на вершины, рёбра и атрибуты
splitStmt :: ([Node], [Edge], [Attr]) -> Either (Either Node Edge) Attr -> ([Node], [Edge], [Attr])
splitStmt (ns, es, as) stmt = case stmt of
    Left (Left node) -> (node:ns, es, as)
    Left (Right edge) -> (ns, edge:es, as)
    Right attr -> (ns, es, attr:as)

-- Парсер одного утверждения (stmt)
stmt :: Parser (Either (Either Node Edge) Attr)
stmt = do
    spaces
    try (do
        attr <- attrStmt
        return (Right attr))
    <|> try (do
        edge <- edgeStmt
        return (Left (Right edge)))
    <|> do
        node <- nodeStmt
        return (Left (Left node))

-- Парсер атрибута графа (ID = ID)
attrStmt :: Parser Attr
attrStmt = do
    key <- identifier
    spaces >> char '=' >> spaces
    value <- identifier
    return (Attr key value)

-- Парсер вершины (node_stmt)
nodeStmt :: Parser Node
nodeStmt = do
    nodeId <- identifier
    attrs <- option [] attrList
    return (Node nodeId attrs)

-- Парсер ребра (edge_stmt)
edgeStmt :: Parser Edge
edgeStmt = do
    fromId <- identifier
    spaces >> string "->" >> spaces
    toId <- identifier
    attrs <- option [] attrList
    moreEdges <- optionMaybe edgeRHS
    case moreEdges of
        Nothing -> return (Edge fromId toId attrs)
        Just nextEdge -> do
            let Edge _ nextTo nextAttrs = nextEdge
            return (Edge fromId toId attrs) -- Возвращаем только первое ребро, остальные обрабатываются в edgeRHS

-- Парсер цепочки рёбер (edgeRHS)
edgeRHS :: Parser Edge
edgeRHS = do
    spaces >> string "->" >> spaces
    toId <- identifier
    attrs <- option [] attrList
    moreEdges <- optionMaybe edgeRHS
    case moreEdges of
        Nothing -> return (Edge toId toId attrs) -- Заглушка для последнего ребра
        Just nextEdge -> return (Edge toId (getEdgeTo nextEdge) attrs)
    where
        getEdgeTo (Edge _ to _) = to

-- Парсер списка атрибутов (attr_list)
attrList :: Parser [Attr]
attrList = do
    char '[' >> spaces
    attrs <- sepEndBy attr (char ',' <|> char ';') -- Поддержка разделителей , и ;
    spaces >> char ']'
    return attrs

-- Парсер одного атрибута (a_list)
attr :: Parser Attr
attr = do
    spaces
    key <- identifier
    spaces >> char '=' >> spaces
    value <- identifier
    return (Attr key value)

-- Точка входа для тестирования
main :: IO ()
main = do
    putStrLn "\nДобро пожаловать в парсер графов DOT!!!"
    putStrLn "Читаем файл graph.txt...\n"
    text <- readFile "graph.txt"
    let result = parse graph "" text
    case result of
        Left e -> do
            putStrLn "Ой, что-то пошло не так :("
            print e
        Right g -> do
            putStrLn "Граф успешно прочитан:"
            print g
            putStrLn "\nКрасивый, правда? Хотите ещё раз? [Да/Нет]\n"
            checkAgain

-- Рекурсивная проверка для повторного запуска
checkAgain :: IO ()
checkAgain = do
    str <- getLine
    if map toLower str == "да" then do
        main
    else if map toLower str == "нет" then do
        putStrLn "\nДо встречи! Не забывайте свои графы :)\n"
    else do
        putStrLn "\nНекорректный ввод. Попробуйте ещё раз. [Да/Нет]\n"
        checkAgain