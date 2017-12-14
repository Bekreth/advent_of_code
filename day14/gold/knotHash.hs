import Data.List
import Data.List.Split
import Data.Char
import qualified Data.Set as Set
import Numeric


main = do
  let seed = "vbqugkhl-"
  let memory = calculateHash [seed ++ (show x)|x <- [0..127]]
  print $ countBlocks (0,0) Set.empty memory


countBlocks :: (Int, Int) -> Set.Set (Int, Int) -> [String] -> Int
countBlocks (x, y) currentCount hashData
  | x == 128 = countBlocks (0, y + 1) currentCount hashData
  | y == 128 = 0
  | otherwise = if newBlock
    then 1 + (countBlocks (x + 1, y) updatedCount hashData)
    else countBlocks (x + 1, y) currentCount hashData
  where  
    xyValue = hashData !! x !! y
    newBlock = xyValue == '1' && Set.notMember (x, y) currentCount
    updatedCount = if newBlock
      then digUpBlock [(x, y)] currentCount hashData
      else currentCount


digUpBlock :: [(Int, Int)] -> Set.Set (Int, Int) -> [String] -> Set.Set (Int, Int)
digUpBlock [] inSet _ = inSet
digUpBlock (x:xs) inSet hashData = digUpBlock xs increment hashData
  where 
    increment = digUpBlock (adjacentFreeBlocks x inSet hashData) (Set.insert x inSet) hashData


adjacentFreeBlocks :: (Int, Int) -> Set.Set (Int, Int) -> [String] -> [(Int, Int)]
adjacentFreeBlocks (x, y) inSet hashData = outSet
  where
    outSet = up ++ right ++ down ++ left
    up = if y > 0
      then getFreeBlock (x, (y - 1)) inSet hashData
      else []
    right = if x < 127
      then getFreeBlock ((x + 1), y) inSet hashData
      else []
    down = if y < 127
      then getFreeBlock (x, (y + 1)) inSet hashData
      else []
    left = if x > 0
      then getFreeBlock ((x - 1), y) inSet hashData
      else []


getFreeBlock :: (Int, Int) -> Set.Set (Int, Int) -> [String] -> [(Int, Int)]
getFreeBlock (x,y) inSet hashData = if (hashData !! x !! y) == '1' && Set.notMember (x, y) inSet
  then [(x,y)]
  else []


calculateHash :: [String] -> [String]
calculateHash [] = []
calculateHash (x:xs) = (concat $ map xorString chunkStrings) : calculateHash xs
  where
    appendInt = [17, 31, 73, 47, 23]
    knotList = (map ord x) ++ appendInt
    inList = [0..255]
    sparse = iterateHash inList knotList (0, 0) 64
    chunks = splitEvery 16 sparse
    chunkStrings = map toBin chunks


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


