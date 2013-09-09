-- 自定义数据类型
data Point = Point Double Double

--data Maybe a = Just a | Nothing

data Person = Person
    { personName ::String
    , personAge :: Maybe Int
    } deriving Show
john = Person "John" (Just 35)
jim = Person "Jim" Nothing

-- 输入输出
main :: IO ()
main = do
    print $ john
    print $ jim
    print $ jim { personAge = Just 20}
    putStrLn "You name:"
    name <- getLine
    putStrLn "You age:"
    age <- getLine
    putStrLn "You are:"
    print $ Person name (Just (read age))