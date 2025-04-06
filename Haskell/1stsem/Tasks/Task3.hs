sign:: Double -> Int
sign n | n > 0 = 1
       | n == 0 = 0
       | n < 0 = -1

combinePredicates:: (Int -> Bool) -> (Int -> Bool) -> (Int -> Bool)
combinePredicates p1 p2 x = p1 x && p2 x 



differentiate:: (Double -> Double) -> Double -> Double -> Double
differentiate f x h | h > 0.1 = error "incorrect h"
differentiate f x h = (f(x + h) - f (x - h)) / (h * 2)


solver:: (Double -> Double) -> Double -> Double -> Double -> Double
solver f e a b | sign (f a) == sign (f b) = error "wrong signs"
               | abs (f ((a + b) / 2)) <= e = (a + b) / 2
               | abs (f ((a + b) / 2)) > e = if sign (f a) /= sign (f ((a + b) / 2)) 
                                                 then solver f e a ((a + b) / 2)
                                                 else solver f e ((a + b) / 2) b