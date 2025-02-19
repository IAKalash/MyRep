import Test.Hspec

main :: IO ()
main = hspec $ do
  describe "frequencies" $ do
    it "returns corteg" $ do
        frequencies [1,1,1,2,3,4,1,1] `shouldBe` [(1,5),(2,1),(3,1),(4,1)]
    it "returns corteg" $ do
        frequencies [12,24,24,13,12,12] `shouldBe` [(12,3),(24,2),(13,1)]
        
        
frequencies :: Eq a => [a] -> [(a,Int)]
frequencies [] = []
frequencies (x:xs) = (x,count xs x) : frequencies (filter (/=x) xs)

count :: Eq a => [a] -> a -> Int
count [] x = 1
count (y:ys) x | x == y = 1 + count ys x
               | otherwise = count ys x