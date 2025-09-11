data Color = Red | Green | Blue | Mix Color Color | Invert Color
    deriving Show

rgb :: Color -> [Double]
rgb Red = [1,0,0]
rgb Green = [0,1,0]
rgb Blue = [0,0,1]
rgb (Invert col) = invert (rgb col)
            where invert [] = []
                  invert (x:xs) | x == 0 = 1 : invert xs
                                | otherwise = (1 - x) : invert xs

                                
rgb (Mix x y) = mix (rgb x) (rgb y)
            where mix [] [] = []
                  mix a [] = a
                  mix [] b = b
                  mix (a:as) (b:bs) = ((a + b) / 2) : mix as bs 
