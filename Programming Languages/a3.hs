module A3 where

--removeAllExcept :: Eq a => a -> [a] -> [a]. This function will remove everything that is not equal to the given element.
--For example, removeAllExcept 'a' ['b', 'a', 'c', 'a'] will return the list of Char "aa" (Note that "aa" is a String which is the same as [Char].
--Another example: removeAllExcept 1 [2, 3, 4, 1] should return [1].

--this function named removeAllExcept, and this function can remove all except numbers that is user enter. It is return the list.
--type: list
removeAllExcept a [] = []
removeAllExcept a (x:xs) = if a == x
                           then a:removeAllExcept a xs
                           else removeAllExcept a xs



--removeAll :: Eq a => a -> [a] -> [a]. This function will remove all occurrences of the given element.
--For example, removeAll 'a' ['a', 'b', 'a', 'c'] will return "bc" and removeAll 1 [1, 2, 4, 5, 2, 1] would return [2, 4, 5, 2].

--this function named removeAll, and this function can remove all numbers that is user enter. It is return the list.
--type: list
removeAll a [] = []
removeAll a (x:xs) = if a == x
                     then removeAll a xs
                     else x:removeAll a xs



--substitute :: Eq a => a -> a -> [a] -> [a]. Replace all occurrences of the first argument with the second argument in the list and return the new list.
--For example, substitute 3 4 [1, 2, 3, 4] will give you [1, 2, 4, 4]

--this function named substitute, and this function can change the first number to second number in list. It is return the list
--type: list
substitute a b [] = []
substitute a b (x:xs) = if a == x
                        then b:substitute a b xs
                        else x:substitute a b xs


--mergeSorted3 :: Ord a => [a] -> [a] -> [a] -> [a]. This function takes 3 lists which are in sorted order and merges them so that the final list is sorted in increasing order.
--For example, mergeSorted3 [2, 3, 5] [1, 8] [-1, 0, 4, 10] is [-1, 0, 1, 2, 3, 4, 5, 8, 10].
--As before, don't use list comprehensions or built-in sorting functions.

--this function named mergeSorted2. This function can sort two different lists, and it will help the mergeSorted3. It is return the list.
--type: list
mergeSorted2 [] [] = []
mergeSorted2 (x:xs) [] = (x:xs)
mergeSorted2 [] (y:ys) = (y:ys)
mergeSorted2 (x:xs) (y:ys) = if x < y
                             then x : mergeSorted2 xs (y:ys)
                             else y : mergeSorted2 (x:xs) ys

--this function named mergeSorted3. This function can sort three different lists, and it will use the mergeSorted2. It is return the list.
--type: list
mergeSorted3 [] [] [] = []
mergeSorted3 [] (y:ys) (z:zs) = mergeSorted2 (y:ys) (z:zs)
mergeSorted3 (x:xs) [] (z:zs) = mergeSorted2 (x:xs) (z:zs)
mergeSorted3 (x:xs) (y:ys) [] = mergeSorted2 (x:xs) (y:ys)
mergeSorted3 (x:xs) [] [] = mergeSorted2 (x:xs) []
mergeSorted3 [] (y:ys) [] = mergeSorted2 [] (y:ys)
mergeSorted3 [] [] (z:zs) = mergeSorted2 [] (z:zs)

mergeSorted3 (x:xs) (y:ys) (z:zs) = mergeSorted2 (x:xs) (mergeSorted2 (y:ys) (z:zs))
