data Tree a = Empty | Node a (Tree a) (Tree a)
    deriving (Show, Eq)

valAtRoot :: Tree a -> Maybe a
valAtRoot Empty = Nothing
valAtRoot (Node n _ _) = Just n


treeSize :: Tree a -> Int
treeSize Empty = 0
treeSize (Node _ a b) = 1 + treeSize a + treeSize b

treeSum :: Num a => Tree a -> a
treeSum Empty = 0
treeSum (Node n x y) = n + treeSum x + treeSum y

mapTree :: (a -> a) -> Tree a -> Tree a
mapTree f Empty = Empty
mapTree f (Node n l r) = (Node (f n) (mapTree f l) (mapTree f r))

preorder :: Tree a -> [a]
preorder Empty = []
preorder (Node n l r) = n : (preorder l) ++ (preorder r)

inorder :: Tree a -> [a]
inorder Empty = []
inorder (Node n l r) = (inorder l) ++ n : (inorder r)

postorder :: Tree a -> [a]
postorder Empty = []
postorder (Node n l r) = (postorder l) ++ (postorder r) ++ [n]

allValues :: (a -> Bool) -> Tree a -> Bool
allValues cond Empty = False
allValues cond (Node n Empty Empty) = cond n
allValues cond (Node n l Empty) = cond n && allValues cond l
allValues cond (Node n Empty r) = cond n && allValues cond r
allValues cond (Node n l r) = cond n && allValues cond l && allValues cond r

treeInsert :: (Ord a) => a -> Tree a -> Tree a
treeInsert x Empty = Node x Empty Empty
treeInsert x (Node val l r) | x < val = Node val (treeInsert x l) r
                            | x > val = Node val l (treeInsert x l)
                            | otherwise = Node val l r
