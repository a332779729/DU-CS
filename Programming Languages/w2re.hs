module W2 where
import Data.List
import Data.Char
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

allAnswersHelper function re lst =
  case lst of
    [] -> Just re
    (x:xs) ->
        case (function x) of
          Just lst -> allAnswersHelper function (re ++ lst) xs
          Nothing -> allAnswersHelper function re xs

--Write a function allAnswers :: (a -> Maybe [b]) -> [a] -> Maybe [b] (again, this has two curried arguments).
--The first argument should be applied to elements of the second argument.
--If it returns Nothing for any element, then the result for allAnswers is Nothing.
--Otherwise, calls to the first argument will have produced Just lst1, Just lst2, ..., Just lstn and the result of allAnswers is Just lst, where lst is [lst1, lst2, ..., lstn].
--Hint: The solution isn't long, uses a helper function with an accumulator and ++.

--this function named allAnswers, and this function can get all Answers that is larger than 0 in list. It is return the list.
--type: Maybe
allAnswers :: (a -> Maybe [b]) -> [a] -> Maybe [b]
allAnswers function myanswer =
    if null myanswer
      then Nothing
      else case allAnswersHelper function [] myanswer of
        Just [] -> Nothing
        x -> x


data Pattern = WildcardPat | VariablePat (String) | UnitPat | ConstantPat (Int) | ConstructorPat (String, Pattern) | TuplePat ([Pattern]) deriving (Eq, Show)
data Value = Constant (Int) | Unit | Constructor (String, Value) | Tuple [Value] deriving (Eq, Show)

--Write a function checkPat that takes a Pattern and returns true if and only if all the variables appearing in the pattern are distinct from each other (i.e., use different strings).
--The constructor names are not relevant. Hint: My solution uses two helper functions.
--The first takes a pattern and returns a list of all the strings it uses for variables. Using foldl with a function that uses ++ is useful in one case.
--The second takes a list of strings and decides if it has repeats. elem might be useful in this case. We're not requiring these, but they may make it easier.

--this function named checkPat, and this function can check the pat. It is return the bool.
--type: Bool
variableshelper pattern = case pattern of
                    VariablePat string -> [string]
                    ConstructorPat (string, pattern) -> variableshelper pattern
                    TuplePat (pattern) -> foldl (\x y -> (variableshelper y) ++ x) [] pattern
                    _ -> []

uniqueStringhelper [] = True
uniqueStringhelper (x:xs) = if (elem x xs) then False
       else uniqueStringhelper (xs)

checkPat pattern = uniqueStringhelper (variableshelper pattern)



--Write a function match that takes a (Value, Pattern) and returns a Maybe [(String, Value)] (note the list is inside the Maybe type, it's not a list of Maybe types).
--It should be Nothing if the Pattern does not match and Just lst where lst is the list of bindings if it does.
--Note that if the Value matches but the Pattern has no Patterns of the form VariablePat s, then the result is Just [].
--Hints: The solution has one case expression with 7 branches (that's a pretty big hint...). The branch in particular for tuples uses allAnswers and Data.List.zip.
--Sample solution is around 13 lines of code. Remember to look above for the rules for what patterns match what values, and what bindings they produce.
--These are hints: we don't require allAnswers and Data.List.zip, but they make it easier.

--this function named match, and this function can help us to match the data. It is return the Maybe.
--type: Maybe
match :: (Value, Pattern) -> Maybe [(String, Value)]
match (value, pattern) = case pattern of
                  WildcardPat -> Just []
                  VariablePat v -> Just [(v, value)]
                  UnitPat -> case value of
                                Unit -> Just []
                                _ -> Nothing
                  ConstantPat ex -> case value of
                                    Constant ac -> if ac == ex then Just [] else Nothing
                                    _ -> Nothing
                  ConstructorPat (ex, subpa) -> case value of
                                    Constructor (ac, subv) -> if ex == ac then match (subv, subpa) else Nothing
                                    _ -> Nothing
                  TuplePat (patterns) -> case value of
                                    Tuple values -> tupleHelper values patterns
                                    _ -> Nothing


tupleHelper [] [] = Just []
tupleHelper [] _ = Nothing
tupleHelper _ [] = Nothing
tupleHelper (v:vs) (p:ps) = case match (v, p) of
  Just bind -> case tupleHelper vs ps of
    Just binds -> Just ( bind ++ binds )
    _ -> Nothing
  _ -> Nothing

--Write a function, firstMatch, that takes a Value and a list of Patterns and returns a Maybe [(String, Value)], in particular, Nothing if no pattern in the list matches, or Just lst, where lst is the list of bindings for the first pattern in the list that matches. Use firstAnswer.
--Hint: Sample solution is approximately 3 lines.

--this function named firstMatch, and this function can help us to get first data in match. It is return the Maybe.
--type: Maybe
firstMatch value pas = firstAnswer (\pa -> match (value, pa)) pas
