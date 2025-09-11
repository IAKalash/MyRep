second:: [a] -> a
second [] = error "empty list"
second [x] = error "list is too small"
second (x:y:xs) =  y

sum' :: [Int] -> Int
sum' [] = 0
sum' (x:[]) = x
sum' (x:xs) = x + sum' (xs)

replicate' :: Int -> a -> [a]
replicate' 0 sym = []
replicate' 1 sym = (sym:[])
replicate' num sym = (sym:(replicate' (num - 1) sym))

lenght' :: [a] -> Int
lenght' [] = 0
lenght' (x:xs) = 1 + lenght' (xs)

last' :: a -> [a] -> a
last' def [] = def
last' def (x:[]) = x
last' def (x:xs) = last' def xs 

map' :: (a -> b) -> [a] -> [b]
map' f [] = []
map' f (x:xs) = f x : (map' f xs)

map2 :: (a -> b -> c) -> [a] -> [b] -> [c]
map2 f [] ys = []
map2 f xs [] = []
map2 f (x:xs) (y:ys) = f x y : (map2 f xs ys)

groupElems :: Eq a => [a] -> [[a]] 
groupElems [] = []
groupElems (x : y : xs) | x == y = [x,y] : groupElems xs
                        | otherwise = [x] : (groupElems (y:xs))