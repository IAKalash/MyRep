
import qualified Data.Map as M
import Data.Char ( toLower )
import Data.List ( concat ) 
import System.Directory
import Text.Regex.Posix
import Text.Read (readMaybe)

main :: IO()
main = do
    let book = M.empty
    putStrLn "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
    putStrLn "\nДобро пожаловать в телефонный справочник!!!"
    menu book

menu :: M.Map String String -> IO()
menu book = do
    putStrLn "\n               МЕНЮ:\n"
    putStrLn "Что вы хотите сделать? Введите ЦИФРУ"
    putStrLn "1 - Добавить контакт"
    putStrLn "2 - Найти контакт"
    putStrLn "3 - Удалить контакт"
    putStrLn "4 - Импортировать справочник из файла"
    putStrLn "5 - Сохранить справочник в файл"
    putStrLn "6 - Выйти\n"
    check0 book

check0 :: M.Map String String -> IO()
check0 book = do
    choise <- getLine
    if choise == "1"
        then add book
    else if choise == "2"
        then find book
    else if choise == "3"
        then myDelete book
    else if choise == "4"
        then do
            putStrLn "\nОткуда загрузить справочник? [Введите имя файла]\n"
            importBook book
    else if choise == "5"
        then do
            putStrLn "\nКуда сохранить справочник? [Введите имя файла]\n"
            exportBook book 0
    else if choise == "6"
        then quit book
    else do
        putStrLn "\nНекорректный ввод. Вы должны ввести ТОЛЬКО ЦИФРУ от 1 ДО 6."
        putStrLn "Попробуйте ещё раз\n"
        check0 book



add :: M.Map String String -> IO()
add book = do
    putStrLn "\nВведите имя:\n"
    name <- getLine
    putStrLn "\nВведите номер телефона: [Например, \"+7-111-111-11-11\"]\n"
    numCheck book name

numCheck :: M.Map String String -> String -> IO()
numCheck book name = do
    phNum <- getLine
    if phNum =~ "^([+]7|8)[ -]?[(]?[0-9]{3}[)]?[ -]?[0-9]{3}([ -]?[0-9]{2}){2}$" then do
        if M.member name book then do
            putStrLn "\nТакой контакт уже существует. Обновить номер? [Да/Нет]\n"
            check1 book name phNum
        else do
            let book2 = M.insert name (correctNum phNum) book 
            putStrLn "\nКонтакт успешно добавлен."
            putStrLn "Добавим ещё один? [Да/Нет]\n"
            toMenu book2
    else do
        putStrLn "\nНекорректный ввод. Корректный пример: [+7-111-111-11-11]"
        putStrLn "Попробуйте ещё раз\n"
        numCheck book name

correctNum :: String -> String
correctNum num = do
    let nums = getAllTextMatches (num =~ "[0-9]") :: [String]
    let corNum = "+7-" ++ concat (myTake 3 (myDrop 1 nums)) ++ "-" ++ concat (myTake 3 (myDrop 4 nums)) ++ "-" ++ concat (myTake 2 (myDrop 7 nums)) ++ "-" ++ concat (myTake 2 (myDrop 9 nums))
    corNum

myDrop :: Int -> [String] -> [String]
myDrop n (x:xs) | n == 0 = x:xs
                | otherwise = myDrop (n-1) xs

myTake :: Int -> [String] -> [String]
myTake 1 [x] = [x]
myTake n (x:xs) | n == 0 = []
                | otherwise = x : myTake (n - 1) xs

check1 :: M.Map String String -> String -> String -> IO()
check1 book name phNum = do
        str <- getLine
        if map toLower str == "да" then do
            let book2 = M.insert name (correctNum phNum) book
            putStrLn "\nКонтакт успешно заменён."
            putStrLn "Добавим ещё один? [Да/Нет]\n"
            toMenu book2
        else if map toLower str == "нет" then do
            putStrLn "\nДобавить другой контакт? [Да/Нет]\n"
            toMenu book
        else do
            putStrLn "\nНекорректный ввод. Попробуйте ещё раз. [Да/Нет]\n"
            check1 book name phNum

toMenu :: M.Map String String -> IO()
toMenu book = do
        str <- getLine
        if map toLower str == "да" then do
            add book
        else if map toLower str == "нет" then do
            putStrLn "\nНу нет так нет. Тогда вернёмся в меню\n"
            menu book
        else do
            putStrLn "\nНекорректный ввод. Попробуйте ещё раз."
            putStrLn "Добавим ещё один контакт? [Да/Нет]\n"
            toMenu book



find :: M.Map String String -> IO()
find book = do
    putStrLn "\nЧей номер вы хотите найти? [Введите имя]\n"
    name <- getLine
    let phNum = M.lookup name book
    if phNum == Nothing then do
        putStrLn "\nТакого контакта не найдено :("
        putStrLn "Ищем дальше? [Да/Нет]\n"
        backToMenu book
    else do
        putStrLn ("\nВот номер контакта " ++ name ++ ":")
        putStrLn (correctNum (fromMaybe phNum ++ "\n"))
        putStrLn "Ищем дальше? [Да/Нет]\n"
        backToMenu book

backToMenu :: M.Map String String -> IO()
backToMenu book = do
    str <- getLine
    if map toLower str == "да" then do
            find book
        else if map toLower str == "нет" then do
            putStrLn "\nТогда вернёмся в меню\n"
            menu book
        else do
            putStrLn "\nНекорректный ввод. Попробуйте ещё раз."
            putStrLn "Ищем дальше? [Да/Нет]\n"
            backToMenu book

fromMaybe :: Maybe a -> a
fromMaybe (Just a) = a



myDelete :: M.Map String String -> IO()
myDelete book = do
    putStrLn "\nКакой контакт вы хотите удалить? [Введите имя]\n"
    str <- getLine
    if M.member str book then do
        let book2 = M.delete str book
        putStrLn "\nКонтакт успешно удалён."
        putStrLn "Продолжим удалять лишние контакты? [Да/Нет]\n"
        toMenu2 book2
    else do
        putStrLn "\nТакого контакта нет. Удалим какой-нибудь другой? [Да/Нет]\n"
        toMenu2 book

toMenu2 :: M.Map String String -> IO()
toMenu2 book = do
    str <- getLine
    if map toLower str == "да" then do
            myDelete book
        else if map toLower str == "нет" then do
            putStrLn "\nТогда вернёмся в меню\n"
            menu book
        else do
            putStrLn "\nНекорректный ввод. Попробуйте ещё раз."
            putStrLn "Удалим что-нибудь ещё? [Да/Нет]\n"
            toMenu2 book



quit :: M.Map String String -> IO()
quit book = do
    putStrLn "\nВы точно хотите выйти? [Да/Нет]\n"
    qcheck book

qcheck :: M.Map String String -> IO()
qcheck book = do
        str <- getLine
        if map toLower str == "да" then do
            putStrLn "\nОчень жаль :("
            putStrLn "Сохранить Справочник? [Да/Нет]\n"
            saveCheck book
        else if map toLower str == "нет" then do
            putStrLn "\nНе пугайте так больше :(\n"
            menu book
        else do
            putStrLn "\nНекорректный ввод. Лучше вернёмся в меню, пока вы здесь чего-нибудь не натворили\n"
            menu book

saveCheck :: M.Map String String -> IO()
saveCheck book = do
    choise <- getLine
    if map toLower choise == "да" then do
        putStrLn "\nКуда сохранить справочник? [Введите имя файла]\n"
        exportBook book 1
    else do
        putStrLn "\n******************************"
        putStrLn "\nМы же ещё встретимся, да?\n"
        putStrLn "******************************\n"



importBook :: M.Map String String -> IO()
importBook book = do
    filePath <- getLine
    ex <- doesFileExist filePath
    if ex then do
        file <- readFile filePath
        let contents = readMaybe file :: Maybe [(String, String)]
        if contents == Nothing then do
            putStrLn "\nНЕКОРРЕКТНЫЙ ФОРМАТ ВВОДА"
            menu book
        else do
            let book2 = M.union book (M.fromList (read file :: [(String, String)]))
            putStrLn "\nСправочник обновлён\n"
            menu book2
    else do
        putStrLn "\nТакого файла не существует :("
        putStrLn "Попробуем ещё раз? [Да/Нет]\n"
        choise <- getLine
        if map toLower choise == "да" then do
            putStrLn "\n[Введите путь до файла]\n"
            importBook book
        else
            menu book

    

exportBook :: M.Map String String -> Int -> IO()
exportBook book ch = do
    filePath <- getLine
    ex <- doesFileExist filePath
    if ex && ch == 0 then do
        writeFile filePath (show (M.toList book))
        putStrLn "\nСправочник сохранён\n"
        menu book
    else if ex && ch == 1 then do
        writeFile filePath (show (M.toList book))
        putStrLn "\n******************************"
        putStrLn "\nСправочник сохранён\n"
        putStrLn "******************************\n"        
    else do
        putStrLn "\nФайл не найден :("
        putStrLn "Попробуем ещё раз? [Да/Нет]\n"
        choise <- getLine
        if map toLower choise == "да" then do
            putStrLn "\n[Введите имя файла]\n"
            exportBook book ch
        else if ch == 1 then do
            putStrLn "\n******************************"
            putStrLn "\nНе забывай меня, пожалуйста...\n"
            putStrLn "******************************\n"
        else
            menu book