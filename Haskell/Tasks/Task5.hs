
or' :: [Bool] -> Bool
or' = foldr1 (||)

all' :: (a -> Bool) -> [a] -> Bool
all' f xs = foldr1 (&&) (map f xs)

map' :: (a -> b) -> [a] -> [b]
map' f = foldr (\a b -> f a : b) []

concatMap' :: (a -> [b]) -> [a] -> [b]
concatMap' f = foldr (\a b -> f a ++ b) []

filter' :: (a -> Bool) -> [a] -> [a]
filter' f = foldr g []
                  where g a b | f a = a : b
                              | otherwise = b

partition' :: (a -> Bool) -> [a] -> ([a],[a])
partition' f xs = (filter' f xs , foldr g [] xs)
                         where g a b | f a = b
                                     | otherwise = a : b

unzip' :: [(a,b)] -> ([a],[b])
unzip' = foldr f ([],[])
                  where f (a,b) (c,d) = (a : c , b : d)

null' :: [a] -> Bool
null' = foldr (\a b -> False) True

intersperse' :: a -> [a] -> [a]
intersperse' a xs = foldr (\x y -> x : a : y) [] (init xs) ++ [last xs]

group' :: Eq a => [a] -> [[a]]                 
group' [] = []
group' (x : y : xs) | x == y = [x,y] : group' xs
                    | otherwise = [x] : group' (y:xs)



lagrange :: [(Double, Double)] -> (Double -> Double)
lagrange list = \x -> foldl (\acc (x_i,y_i) -> acc + (y_i * l x_i x)) 0 list
                    where l x_i x = foldl (\acc (x_j, _) -> 
                                            if x_i == x_j 
                                            then acc 
                                            else acc * (x - x_j) / (x_i - x_j)) 1 list



-- 1. Да, одинаковый: [Int] -> Int (или другой числовой формат вместо Int)
-- 2. xs = [1] (подойдёт практически любой непустой список)
-- 3. [0] (список из 0 любой длины)
-- 4. f [1,2,3] <=> a - (b - (c - 0))       g [1,2,3] <=> 0 - a - b - c
--  Откуда a = -c. Значит, троек подходящих под условие бесконечно много 
-- (под данное условие подходят все тройки, где a = -c)
