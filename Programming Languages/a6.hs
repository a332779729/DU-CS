module A6 where
import Data.Maybe

--Write a function firstAnswer :: ( a -> Maybe b ) -> [a] -> Maybe b.
--Notice the arguments are curried. The first argument should be applied to elements of the second argument (a list) in order until the first time it returns Just v for some v and then Just v is the result of the call to firstAnswer.
--If the first argument returns Nothing for all the elements in the list, then firstAnswer should return Nothing.
--Note, the solution isn't long and doesn't do anything fancy so don't overthink it. Also, the function that's passed can be thought of as a predicate (see its signature?).
--It returns Nothing or Just v for particular types of a if it determines those are invalid or valid answers.
--Note: The description of this has changed slightly to return Nothing instead of an error if there aren't any matches.

--this function named firstAnswer, and this function can get first Answer that is larger than 0 in list. It is return the list.
--type: Maybe
firstAnswer :: (a -> Maybe b) -> [a] -> Maybe b
firstAnswer function (x:xs) = if (isJust (function x))
                             then function x
                             else firstAnswer function xs
firstAnswer function [] = Nothing



--Write a function allAnswers :: (a -> Maybe [b]) -> [a] -> Maybe [b] (again, this has two curried arguments).
--The first argument should be applied to elements of the second argument.
--If it returns Nothing for any element, then the result for allAnswers is Nothing.
--Otherwise, calls to the first argument will have produced Just lst1, Just lst2, ..., Just lstn and the result of allAnswers is Just lst, where lst is [lst1, lst2, ..., lstn].
--Hint: The solution isn't long, uses a helper function with an accumulator and ++.

--this function named allAnswers, and this function can get all Answers that is larger than 0 in list. It is return the list.
--type: Maybe
allAnswersHelper function re lst =
  case lst of
    [] -> Just re
    (x:xs) ->
        case (function x) of
          Just lst -> allAnswersHelper function (re ++ lst) xs
          Nothing -> allAnswersHelper function re xs


allAnswers :: (a -> Maybe [b]) -> [a] -> Maybe [b]
allAnswers function myanswer =
    if null myanswer
      then Nothing
      else case allAnswersHelper function [] myanswer of
        Just [] -> Nothing
        x -> x
