import Data.List
import Data.List.Split
import Data.Char
import Numeric


main = do
  let knotString = "183,0,31,146,254,240,223,150,2,206,161,1,255,232,199,88"
  let appendInt = [17, 31, 73, 47, 23]
  let knotList = (map ord knotString) ++ appendInt
  let inList = [0..255]
  let sparse = iterateHash inList knotList (0, 0) 64
  let chunks = splitEvery 16 sparse
  let chunkStrings = map toBin chunks
  print "I got fed up trying to convert binary to hexadecimal.  You can do it."
  print $ map xorString chunkStrings


toBin :: [Int] -> [String]
toBin [] = []
toBin (x:xs) = 
  let newString = showIntAtBase 2 intToDigit x ""
      padLength = 8 - (length newString)
      allPad = "00000000"
      padding = (fst $ splitAt padLength allPad) ++ newString
  in padding:(toBin xs)




xorString :: [String] -> String
xorString [x, y] = xor x y
xorString (x:y:xs) = 
  let newString = xor x y
      newInput = newString:xs
  in xorString newInput


xor :: [Char] -> [Char] -> [Char]
xor [] [] = []
xor (x:xs) (y:ys)
  | x == y = '0' : iteration
  | otherwise = '1' : iteration
  where
    iteration = xor xs ys


iterateHash :: [Int] -> [Int] -> (Int, Int) -> Int -> [Int]
iterateHash x _ _ 0 = x
iterateHash cycle knot (pos, skip) counter = iterateHash newCycle knot (newPos, newSkip) (counter - 1)
  where
    (newCycle, newPos, newSkip) = sparseHash cycle knot (pos, skip)


sparseHash :: [Int] -> [Int] -> (Int, Int) -> ([Int], Int, Int)
sparseHash x [] (pos, skip) = (x, pos, skip)
sparseHash cycle (x:xs) (pos, skip) = sparseHash newCycle xs (newPos, newSkip)
  where
    inverseRotate = (length cycle) - pos
    cycle1 = resetCyclic cycle pos
    (top, bot) = splitAt x cycle1
    newCycle = resetCyclic (reverse top ++ bot) inverseRotate
    newPos = (pos + x + skip) `mod` (length cycle)
    newSkip = skip + 1


resetCyclic :: [Int] -> Int -> [Int]
resetCyclic cyclic offset = bottom ++ top
  where
    (top, bottom) = splitAt offset cyclic


