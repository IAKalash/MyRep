import Control.Monad.State
import Control.Monad.Writer
import Control.Monad.Trans.Maybe

parensMatch :: String -> Bool
parensMatch s = count == 0
    where (_, count) = runState (mapM_ paren s) 0

paren :: Char -> State Int ()
paren c = do
    cnt <- get
    if cnt < 0
        then
            return ()
        else
            case c of
                '(' -> put (cnt + 1)
                ')' -> put (cnt - 1)
                _ -> return ()


push :: a -> State [a] ()
push x = do
    st <- get
    put (x:st)

pop :: State [a] a
pop = do
    st <- get
    case st of
        [] -> error "Empty list"
        _ -> do put (tail st)
                return (head st)

isEmpty :: State [a] Bool
isEmpty = do
    st <- get
    case st of
        [] -> return True
        _ -> return False

stack :: State [Int] (Int, Int, Int)
stack = do
    push 42
    push 43
    push 44
    x <- pop
    y <- pop
    z <- pop
    return (x,y,z)

sPrintIncAccum :: (Num a, Show a) => StateT a IO String
sPrintIncAccum = do
    st <- get
    lift (print ("Hello, " ++ show st))
    put (st + 1)
    return (show st)


data Expr = Num Integer |
            Var Name |
            Bin Op Expr Expr |
            Let Name Expr Expr
data Op = Add | Mul | Sub | Div

type Name = String

instance Show Op where
    show Add = " + "
    show Mul = " * "
    show Sub = " - "
    show Div = " / "

instance Show Expr where
    show (Num n) = show n
    show (Var x) = x
    show (Bin op e1 e2) = "(" ++ show e1 ++ show op ++ show e2 ++ ")"
    show (Let x e1 e2) = "(let " ++ x ++ " = " ++ show e1 ++ " in " ++ show e2 ++ ")"

apply :: Op -> Integer -> Integer -> Integer
apply Add = (+)
apply Sub = (-)
apply Div = div
apply Mul = (*)

eval11 :: Expr -> WriterT String Maybe Integer
eval11 (Num n) = return n
eval11 (Var _) = lift Nothing
eval11 (Bin op e1 e2) = do
    x <- eval11 e1
    y <- eval11 e2
    case op of
        Add -> tell "add "
        Sub -> tell "sub "
        Mul -> tell "mul "
        Div -> tell "div "
    tell (show x ++ " " ++ show y ++ ";")
    return (apply op x y)
eval11 (Let x e1 e2) = lift Nothing

eval12 :: Expr -> MaybeT (Writer String) Integer
eval12 (Num n) = return n
-- eval12 (Var x) = do
--     tell ("var " ++ x ++ "is not defined")
--     Nothing 
eval12 (Bin op e1 e2) = do
    x <- eval12 e1
    y <- eval12 e2
    case op of
        Add -> tell "add "
        Sub -> tell "sub "
        Mul -> tell "mul "
        Div -> tell "div "
    tell (show x ++ " " ++ show y ++ ";")
    return (apply op x y)
-- eval12 (Let x e1 e2) = lift Nothing
e = (Bin Add (Bin Add (Num 2) (Num 3)) (Num 1))