import qualified Data.Map as Map

data Expr = Var | Num Integer | Add Expr Expr |Sub Expr Expr

eval :: Expr -> Maybe Integer
eval Var = Nothing
eval (Num n) = Just n
eval (Add e1 e2) = do 
            n1 <- eval e1
            n2 <- eval e2
            Just (n1 + n2)
eval (Sub e1 e2) = do
            n1 <- eval e1
            n2 <- eval e2
            Just (n1 - n2)

eval' :: Expr -> Maybe Integer
eval' Var = Nothing
eval' (Num n) = Just n
eval' (Add e1 e2) = eval' e1 >>= (\x ->
                    eval' e2 >>= (\y ->
                    Just (x + y)))
eval' (Sub e1 e2) = eval' e1 >>= (\x ->
                    eval' e2 >>= (\y ->
                    Just (x - y)))

data Person = Person { name :: String, surname :: String }
    deriving (Show, Eq)

grades :: Map.Map Integer Integer
grades = Map.fromList [(124001, 2), (124002, 4)]

studentIds :: Map.Map String Integer
studentIds = Map.fromList [("Ivanov I.", 124001), ("Petrov P.", 124002), ("Sidorova S.", 124003)]

parse :: String -> Maybe Person
parse s = case words s of
    [name, surname] -> Just (Person name surname)
    _ -> Nothing

checkGrade :: String -> Maybe Integer
checkGrade = undefined