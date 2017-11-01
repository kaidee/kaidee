test = zip [1..] ["apple", "orange", "cherry", "mango", "pear"]
--test = zip [1..] [2..6]
--print test

rightTriangles = [ (a,b,c) | c <- [1..10], b <- [1..c], a <- [1..b], a^2 + b^2 == c^2, a+b+c == 24]  
--print rightTriangles'
--main = print rightTriangles

--factorial :: Int -> Int
factorial :: Integer -> Integer
factorial n = product [1..n]
factorials = factorial 20
--main = print factorials

circumference' :: Float -> Float

main::IO()
--main = print test
--main = putStrLn test
main = print 