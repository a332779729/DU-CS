module W1 where

data TriTree a = EmptyNode
                | TriNode a (TriTree a) (TriTree a) (TriTree a)
                deriving Show

instance (Eq a) => Eq (TriTree a) where
  EmptyNode           == EmptyNode = True
  TriNode a la ma ra  == TriNode b lb mb rb = (a == b) &&
                                              (la == lb) &&
                                              (ma == mb) &&
                                              (ra == rb)
  _                   == _ = False


--nodeValue :: TriTree a -> a. This function takes a trinary tree and returns the value of the given node.
--This should return an error if you attempt to do this on an empty node.

--this function named nodeValue, and this function can show the node in the tree. It is return the node.
--type: node
nodeValue::TriTree a -> a
nodeValue EmptyNode = error "empty tree"
nodeValue (TriNode value leftChild middleChild rightChild) = value

--leftChild :: TriTree a -> TriTree a. Takes a trinary tree and returns the left child,
--or an error if the tree is an empty node.

--this function named leftChild, and this function can show the leftChild in the tree. It is return the node.
--type: node
leftChild::TriTree a -> TriTree a
leftChild EmptyNode = error "empty tree"
leftChild (TriNode value leftChild middleChild rightChild) = leftChild


--middleChild :: TriTree a -> TriTree a. Takes a trinary tree and returns the middle child,
--or an error of the tree is an empty node.

--this function named middleChild, and this function can show the middleChild in the tree. It is return the node.
--type: node
middleChild::TriTree a -> TriTree a
middleChild EmptyNode = error "empty tree"
middleChild (TriNode value leftChild middleChild rightChild) = middleChild


--rightChild :: TriTree a -> TriTree a. Takes a trinary tree and returns the right child, or an error if the tree is an empty node.

--this function named rightChild, and this function can show the rightChild in the tree. It is return the node.
--type: node
rightChild::TriTree a -> TriTree a
rightChild EmptyNode = error "empty tree"
rightChild (TriNode value leftChild middleChild rightChild) = rightChild


--inTree :: Eq a => a -> TriTree a -> Bool. Returns True or False if the given element is in a TrinaryTree.
--For example, assuming t contains a trinary tree, inTree 5 t returns True if 5 is in it, or False otherwise. You can't assume the tree is sorted.

--this function named inTree, and this function can check if the value is in this tree. It is return the booleam.
--type: bool
inTree::Eq a => a -> TriTree a -> Bool
inTree x EmptyNode = False
inTree x (TriNode value leftChild middleChild rightChild) = if x == value
                                                            then True
                                                            else inTree x leftChild || inTree x middleChild || inTree x rightChild


--leafList :: TriTree a -> [a]. Takes a trinary tree and returns a list of all the values in the leaves of the tree.
--A leaf is a node with three empty branches.

--this function named leafList, and this function can print all values in this tree. It is return the list.
--type: list
leafList::TriTree a -> [a]
lleafList EmptyNode = []
leafList (TriNode value EmptyNode EmptyNode EmptyNode) = [value]
leafList (TriNode value leftChild middleChild rightChild) = leafList leftChild ++ leafList middleChild ++ leafList rightChild


--inOrderMap :: (a -> b) -> TriTree a -> TriTree b. This function acts like map on a list, performing an in-order traversal of the tree.
--Thus, you pass a function that takes type a and returns type b, pass in a TriTree with type a, and get a resulting TriTree of type b. The trees will match in structure, but with each value transformed by the function you used.

--this function named inOrderMap, and this function can order all values in this tree. It is return the tree.
--type: tree
inOrderMap::(a->b) -> TriTree a -> TriTree b
inOrderMap x EmptyNode = EmptyNode
inOrderMap x (TriNode value leftChild middleChild rightChild) = (TriNode (x value) (inOrderMap x leftChild) (inOrderMap x middleChild) (inOrderMap x rightChild))


--preOrderFold:: (b -> a -> b) -> b -> TriTree a -> b. Similar to a foldl operation on lists, this function takes a function as the first argument, an accumulator value, a TriTree, and performs an pre-order walk of the tree, applying the function to each value and then using the result of that function in the next call of the folding in the tree.
--For example, a tree with (1 2 4 3), where 2, 4, and 3 are the children and then a call to preOrderFold (+) 0 (1 2 4 3), would result in 10. Ask questions if this isn't clear. Again, you can't do fancy things like derive from Foldable (it won't work as expected anyway).

--this function named preOrderFold, and this function can find the pre node put in First in this tree. It is return the tree.
--type: tree
preOrderFold::(b -> a -> b) -> b -> TriTree a-> b
preOrderFold x valueA EmptyNode = valueA
preOrderFold x valueA (TriNode valueB leftChild middleChild rightChild) = preOrderFold x valueC leftChild
               where
               valueC = (x valueC' valueB)
               valueC' = preOrderFold x valueC'' rightChild
               valueC'' = preOrderFold x valueA middleChild
