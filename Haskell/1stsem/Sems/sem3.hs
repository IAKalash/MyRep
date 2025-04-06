sumInts :: Int -> Int -> Int
sumInts a b = sumInts' a b 0
    where sumInts':: Int -> Int -> Int -> Int
          sumInts' a b res | a == b = (res + b)
          sumInts' a b res = sumInts' (a+1) b (res + a)

sumSquares :: Int -> Int -> Int
sumSquares a b = sumSquares' a b 0
    where sumSquares':: Int -> Int -> Int -> Int
          sumSquares' a b res | a == b = (res + b^2)
          sumSquares' a b res = sumSquares' (a+1) b (res + a^2)

higherOrderSum:: (Int -> Int) -> Int -> Int -> Int
higherOrderSum f a b | b == a = f b
                     | b < a = higherOrderSum f b a
                     | otherwise = f b + higherOrderSum f a (b-1)

