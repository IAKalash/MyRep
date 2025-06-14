data Tree a = Empty | Node a (Tree a) (Tree a)
    deriving (Read, Eq)

instance Show a => Show (Tree a) where
    show :: Show a => Tree a -> String
    show = printTree 0 

isSym :: Eq a => Tree a -> Bool
isSym Empty = error "Empty Tree"
isSym (Node n l r) = isSym' l r

buildTree :: Ord a => [a] -> Tree a
buildTree [] = Empty
buildTree xs = buildTree' xs Empty

deleteMin :: (Ord a) => Tree a -> (Tree a, a)
deleteMin Empty = error "Empty tree"
deleteMin a = (deleteValue (minEl a) a, minEl a)

deleteValue :: (Ord a) => a -> Tree a -> Tree a
deleteValue x Empty = Empty
deleteValue x (Node n Empty Empty) | x == n = Empty
deleteValue x (Node n l Empty) | x == n = l
deleteValue x (Node n Empty r) | x == n = r
deleteValue x (Node n l r) | x < n = Node n (deleteValue x l) r
                           | x > n = Node n l (deleteValue x r)
                           | x == n = insertTree r l



printTree :: Show a => Int -> Tree a -> String
printTree spaces Empty = replicate spaces ' ' ++ "Empty"
printTree spaces (Node n l r) = replicate spaces ' ' ++ show n ++ "\n" ++ printTree (spaces + 2) l ++ "\n" ++ printTree (spaces + 2) r

isSym' :: Eq a => Tree a -> Tree a -> Bool
isSym' Empty Empty = True
isSym' Empty Node {} = False
isSym' Node {} Empty = False
isSym' (Node _ l r) (Node _ l2 r2) = isSym' l r2 && isSym' r l2

buildTree' :: Ord a => [a] -> Tree a -> Tree a
buildTree' [] n = n
buildTree' (x:xs) Empty = buildTree' xs (Node x Empty Empty)
buildTree' (x:xs) n = buildTree' xs (insert x n)

insert :: Ord a => a -> Tree a -> Tree a
insert x Empty = Node x Empty Empty
insert x (Node n l r) | x < n = Node n (insert x l) r
                      | x > n = Node n l (insert x r)

insertTree :: Ord a => Tree a -> Tree a -> Tree a
insertTree Empty b = b
insertTree a Empty = a
insertTree (Node n l r) (Node n2 l2 r2) | n2 == n = Node n (insertTree l2 l) (insertTree r2 r)
                                        | n2 > n = Node n l (insertTree (Node n2 l2 r2) r)
                                        | n2 < n = Node n (insertTree (Node n2 l2 r2) l) r

minEl :: Tree a -> a
minEl (Node n Empty _) = n
minEl (Node n l _) = minEl l