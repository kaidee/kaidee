--module Main where
--import System.IO
--main :: IO()
--main = do
--	hSetBuffering stdin LineBuffering  
--	doLoop
--doLoop = do
--	putStrLn "Enter a command rFN wFN or q to quit:"
--	command <- getLine
--	case command of
--		'q':_ -> return ()
--		'r':filename -> do putStrLn ("Reading " ++ filename)
--							doRead filename
--							doLoop
--		'w':filename -> do putStrLn ("Writing " ++ filename)
--							doWrite filename
--							doLoop
--		_			-> doLoop
--doRead filename =
--	bracket (openFile filename ReadMode) hClose
--		(\h -> 
--			do contents <- hGetContents h
--				putStrLn "The first 100 chars:"
--				putStrLn (take 100 contents))
--doWrite filename = do
--	putStrLn "Enter text to go into the file:"
--	contents <- getLine
--	bracket (openFile filename WriteMode) hClose
--		(\h -> hPutStrLn h contents)

import System.IO
import Data.Char(toUpper)
import qualified Data.ByteString      as B
import qualified Data.ByteString.Lazy as L
import Data.ByteString.Lazy.Builder.ASCII as LA

--main :: IO () 
--main = do 
--       inh <- openFile "test.txt" ReadMode
--       outh <- openFile "output.txt" WriteMode
--       mainloop inh outh
--       hClose inh
--       hClose outh
    
--mainloop :: Handle -> Handle -> IO ()
--mainloop inh outh = 
--    do ineof <- hIsEOF inh 
--       if ineof
--           then return ()
--        else do inpStr <- hGetLine inh
--                print $ (map toUpper inpStr) 
--                mainloop inh outh

main :: IO () 
main = do 
       files <- B.readFile "test.txt" -- ReadMode
       print files
