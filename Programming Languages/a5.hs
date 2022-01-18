module A3 where

--Write a function longestString' that does the exact same thing as longestString (from the Daily Homework 4) but returns the last one in case of a tie.
--Same rules apply with foldl, anonymous function, and recursion.

--this function named longestString', and this function can longest string one from list. It is return the string.
--type: string
longestString' :: [String] -> String
longestString' longestcase = if null longestcase
                         then " "
						             else foldl (\longestcase x -> if length x >= length longestcase then x else longestcase) (head longestcase) longestcase


--longestStringHelper has type (Int -> Int -> Bool) -> [String] -> String. Note the String may appear as [Char] instead depending on how Haskell feels at the time.
--This function will look a lot like longestString and longestString' but it is more general because it takes a function as an argument (Int -> Int -> Bool).
--Note: Depending on how you write it, you may get a type which looks like (Int -> Int -> Bool) -> [[a]] -> [a], which is also ok.

--this function named longestStringHelper, and this function can choose (<) or (>) to get longest or shortest string one from list. It is return the string.
--type: string
longestStringHelper :: (Int -> Int -> Bool) -> [String] -> String
longestStringHelper symbol list = if null list then " "
                               else foldl(\longestcase x -> if (symbol (length longestcase) (length x))
                                                        then longestcase
                                                        else x) (head list) list


--longestString3 has the same behavior as longestString and longestString4 has the same behavior as longestString'.

--this function named longestString3, and this function can get longest or shortest string one from list by longestStringHelper function. It is return the string.
--type: string
longestString3 :: [String] -> String
longestString3 longestcase = longestStringHelper (>) longestcase


--longestString3 and longestString4 are defined using just a binding and partial application of longestStringHelper.

--this function named longestString4, and this function can get longest string one from list by longestStringHelper function. if there are two strings are same length to get first one.. It is return the string.
--type: string
longestString4 :: [String] -> String
longestString4 lst  = longestStringHelper (>=) lst
