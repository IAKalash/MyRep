data Expr = Num Integer | Add Expr Expr | Sub Expr Expr

data BoolExpr = BoolLit Bool | Not BoolExpr | And BoolExpr BoolExpr | Or BoolExpr BoolExpr | 
                Eq Expr Expr | Bigger Expr Expr

instance Show Expr where
  show (Num n) = show n
  show (Add ex1 ex2) = "(" ++ show ex1 ++ "+" ++ show ex2 ++ ")"
  show (Sub ex1 ex2) = "(" ++ show ex1 ++ "-" ++ show ex2 ++ ")"

instance Show BoolExpr where
    show (BoolLit n) = show n
    show (Not ex) = "not " ++ show ex 
    show (And ex1 ex2) = show ex1 ++ " && " ++ show ex2 
    show (Or ex1 ex2) = show ex1 ++ " || " ++ show ex2 
    show (Eq ex1 ex2) = show ex1 ++ " = " ++ show ex2 
    show (Bigger ex1 ex2) = show ex1 ++ " > " ++ show ex2 

eval :: Expr -> Integer
eval (Num n) = n
eval (Add ex1 ex2) = apply (eval ex1) (eval ex2) (+)
eval (Sub ex1 ex2) = apply (eval ex1) (eval ex2) (-)

apply :: Integer -> Integer -> (Integer -> Integer -> Integer) -> Integer
apply x y op = x `op` y

boolEval :: BoolExpr -> Bool
boolEval (BoolLit n) = n;
boolEval (Not ex) = not (boolEval ex);
boolEval (And ex1 ex2) = boolEval ex1 && boolEval ex2
boolEval (Or ex1 ex2) = boolEval ex1 || boolEval ex2
boolEval (Eq ex1 ex2) = eval ex1 == eval ex2
boolEval (Bigger ex1 ex2) = eval ex1 > eval ex2



data Bin = End | O Bin | I Bin
    deriving Show

instance Eq Bin where

  End == End = True
  End == ex = False
  ex == End = False
  
  (I ex1) == (O ex2) = False
  (O ex1) == (I ex2) = False
  (I ex1) == (I ex2) = ex1 == ex2
  (O ex1) == (O ex2) = ex1 == ex2

  -- (ex1 (O End)) == ex2 = (ex1 End) == ex2
  -- ex1 == (ex2 (O End)) = ex1 == (ex2 End)

  

inc :: Bin -> Bin
inc End = I End
inc (O b) = I b
inc (I b) = O (inc b)


fromBin :: Bin -> Int
fromBin (End) = 0
fromBin (O ex) = (fromBin ex) * 2
fromBin (I ex) = 1 + (fromBin ex) * 2 

toBin :: Int -> Bin
toBin 0 = O End
toBin 1 = I End
toBin n | mod n 2 == 1 = I (toBin (div n 2))
        | otherwise = O (toBin (div n 2))

pls :: Bin -> Bin -> Bin

pls (End) ex = ex
pls ex (End) = ex

pls (O End) (O End) = O End
pls (O ex1) (O End) = O ex1
pls (O End) (O ex2) = O ex2

pls (I End) (I End) = O (I End)
pls (I ex1) (I End) = O (inc ex1)
pls (I End) (I ex2) = O (inc ex2)

pls (I End) (O ex2) = I ex2
pls (O ex1) (I End) = I ex1

pls (O ex1) (O ex2) = O (pls ex1 ex2)
pls (I ex1) (O ex2) = I (pls ex1 ex2)
pls (O ex1) (I ex2) = I (pls ex1 ex2)
pls (I ex1) (I ex2) = O (pls (pls ex1 ex2) (I End))



mlt :: Bin -> Bin -> Bin

mlt (O End) _ = O End
mlt _ (O End) = O End

mlt (I End) ex = ex
mlt ex (I End) = ex

mlt (ex1) (O ex2) = O (mlt ex1 ex2)
mlt (ex1) (I ex2) = pls ex1 (O (mlt ex1 ex2))


