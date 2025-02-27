import Control.Monad.Reader
import Control.Monad.Writer
import Control.Monad.State
import Control.Monad
import qualified Data.Map as M

data Expr = Num Integer |
            Var Name |
            Bin Op Expr Expr |
            Let Name Expr Expr
data Op = Add | Mul | Sub | Div
type Name = String
data ExprErr = DivisionByZero | UnsetVariable Name
    deriving (Show, Eq)

apply :: Op -> Integer -> Integer -> Integer
apply Add = (+)
apply Sub = (-)
apply Div = div
apply Mul = (*)

evalR :: Expr -> Reader (M.Map Name Integer) Integer
evalR (Num n) = return n
evalR (Var x) = do
    env <- ask
    case M.lookup x env of
        Just n -> return n
        Nothing -> error "No var!"
evalR (Bin op e1 e2) = do
    x <- evalR e1
    y <- evalR e2
    return (apply op x y)
-- evalR (Let x e1 e2) = do
--     f <- evalR e1
--     runReader (evalR e2) (local (M.insert x f) ask)

minusLoggedR :: (Show a, Num a) => a -> [a] -> Writer String a
minusLoggedR acc [] = do
    tell (show acc)
    return acc
minusLoggedR acc (x:xs) = do
    tell "("
    tell (show x ++ "-")
    y <- minusLoggedR acc xs
    tell ")"
    return (x - y)

sumNotTwice :: [Int] -> Int
sumNotTwice xs = fst $ runState (foldM f2 0 xs) []

f2 :: Int -> Int -> State [Int] Int
f2 acc x = do
    env <- get
    if x `notElem` env
        then do 
            put (x:env)
            return (x + acc)
        else return acc