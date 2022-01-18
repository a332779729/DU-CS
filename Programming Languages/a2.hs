module A2 where
--Write a function called findMin that takes a list and finds the smallest element in the list and returns it as the result.
--You should really only have at most n-1 comparisons (i.e., don't do anything weird and quadratic).
--You may comparison functions. You may not use min, foldl, foldr, or any such thing. Just solve this using recursion please.

--this function named the findMin, we need to find min number in the list, and return the min number.
--the type is number
findMin (x:xs) = if xs == []
                  then x
                  else if  x < findMin xs
                 then x
                 else findMin xs

--findMin (x:y:ys) = if y == []
                   --then x
                  --else if x < y
                     --then findMin (x:ys)
                     --else findMin (y:ys)
--findMin [x] = x
--findMin [] = []



--Write a function called tupleDotProduct that takes two lists of numbers and finds the dot product between them.
--We assume the list is just a very big n-dimensional coordinate. You can assume both lists will be the same size.
--Use the generalized dot product formula: LaTeX: dot(q, p) = (q_1 * p_1) + (q_2 * p_2) + ... + (q_n * p_n)d o t ( q , p ) = ( q 1 ∗ p 1 ) + ( q 2 ∗ p 2 ) + . . . + ( q n ∗ p n ). Hint: remember you need a base case. The tupleDotProduct of two empty lists is 0. You may obviously use +, *. Not foldl, foldr, etc.

--this function named the tupleDotProduct, we should let the list A's number times other number of list B , and return the number.
--the type is number
tupleDotProduct (x:xs) (y:ys) = (x * y) + tupleDotProduct xs ys
tupleDotProduct [] [] = 0;


--Write a function called revZip2Lists that takes two lists as arguments and creates a list with a pair from each list consecutively, but in reverse.
--For example, revZip2Lists [1, 2, 3] ['a', 'b', 'c'] would produce [('c', 3), ('b', 2), ('a', 1)].
--You can assume the lists are the same size (because it would be impossible to make a tuple of one element to mix properly with tuples of two elements from a typing perspective).
--You may not use use zip or reverse. Hint: You will need append (the ++ operation) to solve this.
--reverseList theList = if theList == []
                         --then []
                         --else (reverseList (tail theList)) ++ [(head theList)]

--this function named the revZip2Lists, we should let the two lists be reversed, and return the list.
--the type is list of tuples
revZip2Lists (x:xs) (y:ys) = revZip2Lists xs ys ++ [(y,x)]
revZip2Lists a b = []


--Write a function called everyThird that takes a list and constructs a new list only consisting of every third element in it.
--This means that calling it on [1, 2, 3, 4, 5, 6] would return [3, 6]. You may not use anything like drop, or other such things.
--If you use drop, you  turn a nice linear time solution into a quadratic time solution!

--this function named the everyThird, we should find the third number in list, and return the list.
--the type is list of numbers.
everyThird (x:y:z:zs) = [z] ++ everyThird zs;
everyThird a = []
