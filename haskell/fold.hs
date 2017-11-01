sum' :: (Num a) => [a] -> a
sum' = foldl (+) 0
summ = sum [3,4,7]

maximum' :: (Ord a) => [a] -> a  
maximum' = foldr1 (\x acc -> if x > acc then x else acc)  

reverse' :: [a] -> [a]  
reverse' = foldl (\acc x -> x : acc) []  

product' :: (Num a) => [a] -> a  
product' = foldr1 (*)  

filter' :: (a -> Bool) -> [a] -> [a]  
filter' p = foldr (\x acc -> if p x then x : acc else acc) []  

head' :: [a] -> a  
head' = foldr1 (\x _ -> x)  

last' :: [a] -> a  
last' = foldl1 (\_ x -> x)

main :: IO ()
main = do
	--print summ
	--print (maximum [4,3,7,6])
	--print (maximum ['d','f','g'])
	--print (reverse ['d','f','g'])

	print $ sum [1,5]