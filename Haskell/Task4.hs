len :: [a] -> Int
len [] = 0
len (x : xs) = 1 + len xs

map' :: ([a] -> [b]) -> [[a]] -> [[b]]
map' f (x : xs) = f x : map' f xs

map2 :: (a -> c) -> [a] -> [a] -> [c]
map2 f [] ys = []
map2 f xs [] = []
map2 f (x : xs) (y : ys) = f x : f y : map2 f xs ys

triples:: [(Int,Int,Int)]
triples = [(x,y,z) | z <- [1..], y <- [1..z] , x <- [1..y], x^2 + y^2 == z^2]

collatz :: Int -> [Int]
collatz n | n <= 0 = error "incorrect input"
          | n == 1 = [n]
          | even n = n : collatz (div n 2)
          | odd n = n : collatz (n * 3 + 1)


f0 :: [a] -> Int -> [[a]]
f0 xs 0 = []
f0 (x:xs) y = (xs++[x]) : f0 (xs ++ [x]) (y - 1)  

permutations :: [a] -> [[a]]
permutations [] = [[]]
permutations [x] = [[x]]
permutations [x,y] = f0 [x,y] (len [x,y])
permutations (x : xs) = map' f1 (map2 (x :) (f0 xs (len xs)) (f0 (reverse xs) (len xs)))
                        where f1 :: [a] -> [[a]]
                              f1 [x1] = f0 [x1] (len(x:xs))