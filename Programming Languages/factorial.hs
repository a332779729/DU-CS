--Tenth class

data AntState = Sleeping | Eating | Foraging

instance Eq AntState where
  Sleeping == Sleeping = True
  Eating == Eating = True
  Foraging == Foraging = True
  _ == _ = False

instance Show AntState where
  show Sleeping = " Donot Bothor me!"
  show Eating = "Cant Talk, Eating..."
  show Foraging = " looking for food"

data Tree a = EmptyNode | TreeNode a (Tree a) (Tree a)
      deriving(Show)

instance Functor Tree where
  fmap f EmptyNode = EmptyNode
  fmap f (TreeNode val left right) = TreeNode (f val)
                                        (fmap f left)
                                        (fmap f right)


--Seventh Class
{--extendEnv name value e = Entry name value e

applyEnv name EmptyEnv = error "Unbound variable"
applyEnv name (Entry n value e) = if name == n
                                    then value
                                    else applyEnv name e

eval e env = case e of
                Number n -> n
                Var name -> applyEnv name env
                Bind name value expr -> (eval expr (extnedEnv name value))
                Plus a b -> (eval a env) + (eval b env)
                Sub


--Fifth Class
quicksort :: (Ord a) => [a] -> [a]
quicksort [] = []
quicksort (x:xs) =
            let smaller = [a | a <- xs, a <= x]
                larger = [a | a <- xs, a > x]
             in
                quicksort smaller ++ [x] ++ quicksort larger

split :: [a] -> ([a], [a])
split [] = ([], [])
split [x] = ([x], [])
split (x:y:xs) = let (a, b) = split xs
                    in
                      (x:a, y:b)


merge :: (Ord a) -> [a] -> [a]
merge [] [] = []
merge (x:xs) [] = (x:xs)
merge [] (y:ys) = (y:ys)
merge (x:xs) (y:ys) = if x < y
                        then x : (merge xs (y:ys))
                        else y : (merge (x:xs) ys)


--Forth Class
data MyType = TwoInts Int Int | Spaghetti [Char] | Pizza
      deriving (Show)

myFun x = case x of
              TwoInts x y -> x + y
              Spaghetti name -> 0
              Pizza -> 100

data MyList = Empty | Cons Int MyList
      deriving (Show)

myAdd theList = case theList of
                  Empty -> 0
                  Cons u tailList -> u + (myAdd tailList)

modify theList = case theList of
                  Empty -> Empty
                  Cons u tailList -> Cons (u+1) (modify tailList)

--data MyTree a = Empty | Node (MyTree a) (MyTree a)
    --deriving (Show)



--Third class
cylinder radius height =
  let circleArea = 2 * pi * radius
      sideArea = 2 * pi * radius * height
   in
      circleArea + sideArea


cyl radius height = circleArea + sideArea
  where
    circleArea = 2 * pi * radius * radius
    sideArea = 2 * pi * radius * height


search n someList =
  if someList == [] then False
    else
      if (head someList) == n
        then True
        else search n (tail someList)


findMin someList =
  if someList == []
    then Nothing
    else findMinHelper (head someList)
                       (tail someList)

findMinHelper n someList =
  if someList == []
    then Just n
  else
    if n < (head someList)
      then findMinHelper n (tail someList)
      else findMinHelper (head someList)
                        (tail someList)


foo = Nothing



--Second class
--
--Double element in a list if numbers
--Consumes a list of numbers
--Produces a list of numbers where each lement is
--  multipled by 2
doubleList theList = if theList == []
                        then []
                        else 2 * (head theList) : doubleList (tail theList)


reverseList theList = if theList == []
                         then []
                         else (reverseList (tail theList)) ++ [(head theList)]


--Lengths of String
--Consume a list of words
--Purduce a list if their Lengths
lengths theList = if theList == []
                     then []
                     else (length (head theList)) : lengths (tail theList)


--find element k in a
--Comsume a list and a number k
--produce the kth element
getElement k [] = error "Empty List"
getElement 0 (x:xs) = x
getElement k (x:xs) = getElement (k - 1) xs



--First class
--
-- Hello there this is a comment
factorial n = if n == 0
                then 1
                else n * factorial (n -1 )

newFact 0 = 1
newFact n = n * newFact (n - 1)

multOne a b = a * b

multTwo (a,b) = a * b

mymax (a,b) = if a < b then b else a

dotProduct (a,b) (c,d) = a*b + b*d

byTwo (a,b) = (2*a, 2*b)

--}
