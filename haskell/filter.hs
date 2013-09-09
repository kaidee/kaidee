largest_divisible :: (Integral a) => a
largest_divisible = head (filter p [ 100000, 99999..])
	where p x = x `mod` 3829 == 0
