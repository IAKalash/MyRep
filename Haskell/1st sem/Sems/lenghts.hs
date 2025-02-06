lenghts :: [[a]] -> [Int]
lenghts [] = []
lenghts (x:xs) = (len x) : lenghts xs
                where len :: [a] -> Int
                      len [] = 0
                      len (x:xs) = 1 + len xs