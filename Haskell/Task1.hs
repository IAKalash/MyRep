{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Redundant if" #-}

f1:: Double -> Double
f1 x = x^2 / (1 + x)

f2 :: Double -> Double
f2 x = sqrt(x * 3 - x^3)

f3 :: Double -> Double
f3 x = logBase 10 (x^2 - 21)

f4 :: Double -> Double
f4 x = logBase 2 (logBase 3 (logBase 4 x))

f5 :: Double -> Double
f5 x = sqrt(sin (2*x)) - sqrt(sin (3*x))

distance :: Double -> Double -> Double -> Double -> Double
distance x1 y1 x2 y2 = sqrt((x2 - x1)^2 + (y2 - y1)^2)

leap:: Int -> Bool
leap x = if mod x 4 == 0 
         then if mod x 100 == 0 
              then if mod x 400 == 0 
                   then True 
                   else False
              else True
         else False