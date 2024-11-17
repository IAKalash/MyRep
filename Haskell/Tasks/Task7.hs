data Expr = Num Integer | Add Expr Expr | Sub Expr Expr

data BoolExpr = BoolLit Bool | Not BoolExpr | And BoolExpr BoolExpr | Or BoolExpr BoolExpr | 
                Eq Expr Expr | Bigger Expr Expr

instance Show Expr where
  show (Num n) = show n
  show (Add ex1 ex2) = "(" ++ show ex1 ++ " + " ++ show ex2 ++ ")"
  show (Sub ex1 ex2) = "(" ++ show ex1 ++ " - " ++ show ex2 ++ ")"

instance Show BoolExpr where
    show (BoolLit n) = show n
    show (Not ex) = "not " ++ show ex 
    show (And ex1 ex2) = show ex1 ++ " && " ++ show ex2 
    show (Or ex1 ex2) = show ex1 ++ " || " ++ show ex2 
    show (Eq ex1 ex2) = show ex1 ++ " == " ++ show ex2 
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
