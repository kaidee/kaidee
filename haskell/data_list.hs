import Data.List (nub, sort)
--import qualified Data.Map as M

num_uniques :: (Eq a) => [a] -> Int
num_uniques = length . nub

main :: IO()
main = do
	print $ num_uniques [3,4,5,6,5,4,9]