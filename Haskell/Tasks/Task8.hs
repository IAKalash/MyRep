data Tree a = Empty | Node a (Tree a) (Tree a)
    deriving (Show, Read, Eq)

isSym :: Eq a => Tree a -> Bool
isSym Empty = error "Empty Tree"
isSym (Node n l r) = isSym' l r

isSym' :: Eq a => Tree a -> Tree a -> Bool
isSym' Empty Empty = True
isSym' Empty Node {} = False
isSym' Node {} Empty = False
isSym' (Node n l r) (Node n2 l2 r2) | n == n2 = isSym' l r2 && isSym' r l2
                                    | otherwise = False


buildTree :: Ord a => [a] -> Tree a
buildTree [] = error "Empty list"
buildTree xs = buildTree' xs Empty

buildTree' :: Ord a => [a] -> Tree a -> Tree a
buildTree' [] n = n
buildTree' (x:xs) Empty = buildTree' xs (Node x Empty Empty)
buildTree' (x:xs) n = buildTree' xs (insert x n)

insert :: Ord a => a -> Tree a -> Tree a
insert x Empty = Node x Empty Empty
insert x (Node n l r) | x < n = Node n (insert x l) r
                                            | x > n = Node n l (insert x r)

deleteMin :: (Ord a) => Tree a -> (Tree a, a)
deleteMin Empty = error "Empty tree"
deleteMin (Node n Empty Empty) = (Empty, n)
deleteMin (Node n Empty r) = (r, n)
deleteMin (Node n l r) = 

delete