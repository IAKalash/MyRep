len:: Int -> Int
len n | n < 10 = 1
len n = 1 + len (div n 10)

f1:: Int -> Int
f1 n | n < 10 = n
f1 n = mod n 10 * 10^(len n - 1) + f1 (div n 10)




isPrime :: Int -> String
isPrime n = f20 n 2
    where f20:: Int -> Int -> String
          f20 n d | n == d = "Yes"
          f20 n d = if mod n d == 0
            then "No"
            else f20 n (d + 1)



fib:: Int -> Int
fib n | n == 0 = 0
      | otherwise = fib' 0 1 n
    where fib':: Int -> Int -> Int -> Int
          fib' a b n | n == 1 = b
                     | otherwise = fib' b (a+b) (n-1)




fprogSum:: Float -> Float -> Int -> Float
fprogSum b q n = (b * (1 - q^n)) / (1-q)

fAllSum:: Float -> Float -> Float
fAllSum b q = if abs q < 1
                then b / (1 - q)
                else error "Ряд расходится"


f3 :: Float -> Float -> Float -> Int
f3 b q e = f30 b q e 1
    where f30:: Float -> Float -> Float -> Int -> Int
          f30 b q e n = if abs (fprogSum b q n - fAllSum b q) < e
            then n
            else f30 b q e (n + 1)


