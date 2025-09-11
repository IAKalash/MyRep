data Shape = Circle Double | Rectangle Double Double | Triangle Double Double Double
    deriving Show

isSym :: Shape -> Bool
isSym (Circle r) = True
isSym (Rectangle x y) = True
isSym (Triangle a b c) | a == b = True
                       | a == c = True
                       | c == b = True
                       | otherwise = False

data Expr = Var | Num Integer | Add Expr Expr | Sub Expr Expr 

instance Show Expr where
    show Var = "x"
    show (Num n) = show n
    show (Add ex1 ex2) = "(" ++ show ex1 ++ " + " ++ show ex2 ++ ")"
    show (Sub ex1 ex2) = "(" ++ show ex1 ++ " - " ++ show ex2 ++ ")"

eval :: Expr -> Maybe Integer
eval Var = Nothing
eval (Num n) = Just n
eval (Add ex1 ex2) = apply (eval ex1) (eval ex2) (+)
eval (Sub ex1 ex2) = apply (eval ex1) (eval ex2) (-)

apply :: Maybe Integer -> Maybe Integer -> (Integer -> Integer -> Integer) -> Maybe Integer
apply Nothing _ _ = Nothing
apply _ Nothing _ = Nothing
apply (Just x) (Just y) op = Just (x `op` y)

size :: Expr -> Int
size (Num n) = 0
size (Add ex1 ex2) = 1 + size ex1 + size ex2
size (Sub ex1 ex2) = 1 + size ex1 + size ex2


data Tree a = Empty | Node a (Tree a) (Tree a)
    deriving (Show, Eq)

valAtRoot :: Tree a -> Maybe a
valAtRoot Empty = Nothing
valAtRoot (Node n _ _) = Just n


treeSize :: Tree a -> Int
treeSize Empty = 0
treeSize (Node _ a b) = 1 + treeSize a + treeSize b

treeSum :: Num a => Tree a -> a
treeSum Empty = 0
treeSum (Node n x y) = n + treeSum x + treeSum y
