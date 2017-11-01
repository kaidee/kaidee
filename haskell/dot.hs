negated = map (negate . abs) [5, -3, -6, 7, -2, 9, 33]
negated_lambda = map (\x -> negate (abs x)) [5, -3, -6, 7, -2, 9, 33]

three = map (negate . sum . tail) [[1..5],[3..6],[1..7]]
three_lambda = map (\xs -> negate (sum (tail xs))) [[1..5],[3..6],[1..7]]

main :: IO()
main = do
	print negated
	print negated_lambda
	
	print three
	print three_lambda