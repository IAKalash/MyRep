triples:: [(Int,Int,Int)]
triples = [(x,y,z) | z <- [1..], y <- [1..z] , x <- [1..y], x^2 + y^2 == z^2]

collatz :: Int -> [Int]
collatz n | n <= 0 = error "incorrect input"
          | n == 1 = [n]
          | even n = n : collatz (div n 2)
          | odd n = n : collatz (n * 3 + 1)

permutations :: Eq a => [a] -> [[a]]
permutations [] = [[]]
permutations (x:xs) = [y:ys | y <- x:xs, ys <- permutations (f y (x:xs))]
                                                            where f :: Eq a => a -> [a] -> [a]
                                                                  f n (x:xs) | n == x = xs
                                                                             | otherwise = x: (f n xs) 

subsequenses :: [a] -> [[a]]
subsequenses [] = [[]]
subsequenses (x:xs) = map (x:) (subsequenses xs) ++ subsequenses xs
