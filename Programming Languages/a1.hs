
module A1 where
--Write a function called quadratic that takes four parameters: a, b, c, and x.
--The function should return the value of a + b*x + c*x^2.

--comment:This function named quadratic.This taked four numbers, and it can return or calculated the a + b*x + c*x^2
--Answer:
quadratic a b c x = a + b*x + c*x^2
--type: number


--Write a function called scaleVector that takes a single number along with a 2-tuple which represents a two dimensional vector.
--The function should return a 2-tuple which represents the vector scaled by the value.
--For example, scaleVector of 5 and  (3, 4) should produce (15, 20).

--comment:This function named scaleVector.This taked single number and a 2-tuple which represents a two dimensional vector,
-- and it can return or calculated the (a*b, a*c)
--Answer:
scaleVector a (b,c) = (a*b, a*c)
--type: 2-tuple


--Write a function called tripleDistance that takes two 3-tuples which represent three dimensional points and finds the cartesian distance between them.
--Note that this is calculated as follows:
--LaTeX: d = \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2 + (z_2 - z_1)^2}d = ( x 2 − x 1 ) 2 + ( y 2 − y 1 ) 2 + ( z 2 − z 1 ) 2.

--comment:This function named tripleDistance.This taked two 3-tuples, and it can return or calculated the distance formula.
--Answer:
--tripleDistance (x,y) (a,b) (c,d) = sqrt(((y-x)^2) + ((b-a)^2) + ((d-c)^2))
tripleDistance (x,a,c) (y,b,d) = sqrt(((y-x)^2) + ((b-a)^2) + ((d-c)^2))
--type: decimals
