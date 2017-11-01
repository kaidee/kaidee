--helloWorld :: IO()
--helloWorld = putStr "Hello, World!\n"

--putNtimes :: Int -> String -> IO()
--putNtimes n str
--  = if n <= 1
--      then putStrLn str
--      else do
--          putStrLn str
--          putNtimes (n - 1) str
--put4times = putNtimes 4

--get_int :: IO Int
--get_int = do
--  line <- getLine
--  return (read line :: Int)

--main :: IO()
--main = do
--  let get_int1 = get_int
--  print get_int1

--copy_input_to_output :: IO()
--copy_input_to_output
--  = while (res)
--          (do res <- isEof
--              return (not res))
--          (do line <- getLine
--              putStrLn line)

go_until_empty :: IO()
go_until_empty = do
    line <- getLine
    if (line == [])
        then return()
        else putStrLn line >> go_until_empty
