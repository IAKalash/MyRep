gcd':: Int -> Int -> Int
gcd' a b | a <= 0 = b
         | b <= 0 = a
         | a >= b = gcd' b (mod a b)
         | a < b = gcd' a (mod b a)

isFib:: Int -> Bool
isFib z = fib 0 1 z
            where fib:: Int -> Int -> Int -> Bool
                  fib x y z | x == z = True
                            | x > z = False
                            |otherwise = fib y (x + y) z

power:: Int -> Int -> Int
power x n | n == 0 = 1
          | n < 0 = error""
          | otherwise = power x (n - 1) * x