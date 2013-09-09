import System.IO
import Data.Char(toUpper)
import Data.Binary
import Data.Word
import Data.Char
import Numeric
import Text.Printf

--import Data.ByteString.Builder
import Data.ByteString.Lazy.Builder.ASCII as LA
import qualified Data.ByteString      as B
import qualified Data.ByteString.Lazy as L

file_ascii :: B.ByteString -> [Word8]
--binary_to_hex [] = []
file_ascii  = (B.unpack)


binary_to_hex  :: [Word8] -> [String]
--binary_to_hex [] = []
binary_to_hex = map (\x -> printf "%02x," x)

test :: [Word8] -> IO ()
test li = putStrLn li


--binary_to_hex  = (showIntAtBase 16 intToDigit) . (B.unpack)

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
--                hPutStrLn outh (map LA.lazyByteStringHexFixed inpStr) 
--                mainloop inh outh

main :: IO () 
main = do 
       files <- B.readFile "test.txt" -- ReadMode
       print files
       print $ file_ascii files
       let x = (23 :: Word8)
       putStrLn $ printf "0x%02x," $ x
       test files
       --putStrLn $ map (\x -> printf "%02x," x) (file_ascii files)
       --let file = file_ascii files
       --putStrLn $ printf "0x%02x" $ (file :: [Word8])
       --putStrLn $ binary_to_hex file
       --print file
		