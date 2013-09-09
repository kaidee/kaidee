sayMe :: (Integral a) => a -> String
sayMe 1 = "One!" 
sayMe 2 = "Two!"
sayMe 3 = "Three"
sayMe 4 = "Four"
sayMe 5 = "Five"
sayMe x = "not between 1 and 5" 

factorial :: (Integral a) => a -> a
factorial 0 = 1
factorial n = n * factorial  (n - 1)
