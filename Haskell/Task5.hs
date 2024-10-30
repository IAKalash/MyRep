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