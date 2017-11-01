import qualified Data.Set as Set

text1 = "I just had an anime dreamAnime..Reality..Are they so different?"  
text2 = "The old man left his garbage can out and now his trash is all over my lawn!"

set1 = Set.fromList text1
set2 = Set.fromList text2

main :: IO()
main = do
	print set2
	print $ Set.difference set2 set1