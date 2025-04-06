data DayOfWeek = Monday | Tuesday | Wednesday | Thursday | Friday | Saturday | Sunday
            deriving Eq

isWeekend :: DayOfWeek -> Bool
isWeekend d | d == Saturday = True
            | d == Sunday = True
            | otherwise = False

data Shape = Circle Double | Rectangle Double Double | Triangle Double Double Double
    deriving Show

perimeter :: Shape -> Double
perimeter (Circle r) = 2 * pi * r
perimeter (Rectangle x y) = 2 * (x + y)
perimeter (Triangle a b c) = a + b + c

isSquare :: Shape -> Bool
isSquare (Rectangle a b) | a == b = True
isSquare _ = False 

area :: Shape -> Double
area (Circle r) = pi*r^2
area (Rectangle a b) = a*b
area (Triangle a b c) = geron ((a + b + c) / 2) a b c
                        where geron p a b c = sqrt(p * (p - a) * (p - b) * (p - c))

data Point a = Point a a

euclideanDistance :: Point Double -> Point Double -> Double
euclideanDistance (Point x1 y1) (Point x2 y2) = sqrt ((x1 - x2) ^ 2 + (y1 - y2) ^ 2)


manhDistance :: Point Int -> Point Int -> Int
manhDistance (Point x1 y1) (Point x2 y2) = abs (x1 - x2) + abs (y1 - y2)


data List a = Nil | Cons a (List a)
    deriving Show

fromList :: List a -> [a]
fromList (Nil) = []
fromList (Cons a as) = a : fromList as

toList :: [a] -> List a
toList [] = Nil
toList (a:as) = Cons a (toList as)

data Nat = Zero | Suc Nat
    deriving Show

fromNat :: Nat -> Integer
fromNat Zero = 0
fromNat (Suc n) = fromNat n + 1

toNat :: Integer -> Nat
toNat n | n < 0 = error "incorrect input"
        | n == 0 = Zero
        | otherwise = Suc (toNat (n - 1))

multNat :: Nat -> Nat -> Nat
multNat a b = toNat(fromNat a * fromNat b)

plusNat :: Nat -> Nat -> Nat
plusNat a b = toNat(fromNat a + fromNat b)

factNat :: Nat -> Nat 
factNat a = toNat(fact(fromNat a))
                where fact n | n == 0 = 0
                             | n == 1 = 1
                             | otherwise = n * fact (n - 1)
