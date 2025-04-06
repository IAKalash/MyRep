import qualified Data.Map as M

headE :: [a] -> Either String a
headE [] = Left "Can't take head of empty list"
headE (x:xs) = Right x

tailE :: [a] -> Either String [a]
tailE [] = Left "List is empty"
tailE (x:xs) = Right xs

sumFirst :: Num a => [a] -> Either String a
sumFirst xs = (+) <$> headE xs <*> (tailE xs >>= headE)


data Expr = Num Integer |
            Var Name |
            Bin Op Expr Expr |
            Let Name Expr Expr
data Op = Add | Mul | Sub | Div
type Name = String
data ExprErr = DivisionByZero | UnsetVariable Name
    deriving (Show, Eq)

evalE :: Expr -> M.Map Name Integer -> Either ExprErr Integer
evalE (Num n) env = Right n
evalE (Var x) env = case M.lookup x env of
                        Nothing -> Left (UnsetVariable x)
                        Just n -> Right n
evalE (Bin op e1 e2) env = do
            x <- evalE e1 env
            y <- evalE e2 env
            case op of
                Div -> if y == 0
                    then Left DivisionByZero
                    else Right (div x y)
                Add -> Right (x + y)
                Sub -> Right (x - y)
                Mul -> Right (x * y)
evalE (Let x e1 e2) env = do
        f <- evalE e1 env
        evalE e2 (M.insert x f env)