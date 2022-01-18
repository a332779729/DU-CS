module A4 where

import Data.Char
import Data.List
--Write a function called onlyLowercase that takes a String list and returns a string list that only has the strings in the given list that begin with a lower-case letter.
--Assume all strings have at least one character and use filter (in Data.List) and isLower (in Data.Char) for a 1-2 line solution.
--checkIsLower :: Char -> Bool
--checkIsLower (x:xs) = if isLower x == True
                      --then True
                      --else False

--onlyLowercase :: [[Char]] -> [[Char]]

--this function named onlyLowercase, and this function can delete all char that are not lower case. It is return the list.
--type: list
onlyLowercase lowercase = if null lowercase
                      then []
                      else filter (\x -> isLower (head x)) lowercase



--Write a function longestString that takes a String list and returns the longest string in the list. If the list is empty, return "".
--If there is a tie, return the first one. Use foldl, an anonymous function passed to it, and no recursion directly (obviously foldl uses recursion and that's ok).

--this function named longestString, and this function can get longest from list. It is return the list.
--type: list
longestString :: [String] -> String
longestString longestcase = if null longestcase
                        then " "
						            else foldl (\longestcase x -> if (length x) > (length longestcase)
                                                      then x
                                                      else longestcase) (head longestcase) longestcase



--Write a function called multpairs that takes a list of pairs of integers and returns a list of the products of each pair.
--multpairs :: Num a => [(a,a)] -> [a]

--this function named multpairs, and this function can let first one times second one in list. It is return the list.
--type: list
multpairs [] = []
multpairs ((a, b):xs) = if ((a, b):xs) == []
                        then []
                        else (a * b) : multpairs xs



--Write a function called sqsum that takes a list of integers and returns the sum of the squares of those integers.
--sqsum ::

--this function named sqsum, and this function can let everyone times itself and sum all case in list. It is return the list.
--type: num
sqsum [] = 0
sqsum (x:xs) = if (x:xs) == []
                then 0
                else x * x + sqsum xs



--Write a function called duplist that takes a list as input and creates a new list but with each element duplicated.
--For example, if the input list if [1,3,2] then it should produce [1,1,3,3,2,2]. This function should work with any type of list.

--this function named multpairs, and this function can let copy one more case in list. It is return the list.
--type: list
duplist :: [a] -> [a]
duplist [] = []
duplist (x:xs) = x: (x:duplist xs)
