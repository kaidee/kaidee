mymap :: (a -> a) -> [a] -> [a]

mymap _ [] = []
mymap f (x:xs) = (f x):(mymap f xs) 
