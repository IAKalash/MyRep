doubleAll :: Num a => [a] -> [a]
doubleAll [] = []
doubleAll (x:xs) = (x * 2) : doubleAll xs

doubleAll' :: Num a => [a] -> [a]
doubleAll' xs = [x * 2 | x <- xs]

doubleAll'' :: Num a => [a] -> [a]
doubleAll''  = map ( * 2) 

lenght' :: [a] -> Int
lenght' xs = sum (map (f) xs)
            where f :: a -> Int
                  f _ = 1

reverse' :: [a] -> [a]
reverse'  = foldl f [] 
                    where f y x = x:y

last' :: [a] -> a
last'  = foldl1 f 
            where f _ a = a

prefixes' :: [a] -> [[a]]
prefixes' xs = foldr (\x acc -> [] : map (x:) acc ) [[]] xs
                     