import Data.List


groupElems :: Eq a => [a] -> [[a]]
groupElems [] = []
groupElems [x] = [[x]]
groupElems (x1 : x2 : xs) | x1 == x2 = (x1:g) : gs
                          | otherwise = [x1] : g : gs
                          where (g:gs) = groupElems (x2:xs)

groupElems' :: Eq a => [a] -> [[a]]
groupElems' [] = []
groupElems' (x:xs) = (x : takeWhile (== x) xs) : groupElems' (dropWhile (== x) xs) 



encode :: Eq a => [a] -> [(Int, a)]
encode xs = foldr f [] xs
            where f a [] = (1,a) : []
                  f a ((b,c):y) | a == c = (b + 1, c) : y
                                | otherwise = (1,a): (b,c):y
                  


