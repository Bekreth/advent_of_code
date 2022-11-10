import Data.Char
import Data.List.Split
import Data.List

main = do
  inputFile <- readFile "data.txt"
  let comandList = splitOn "," $ init inputFile
  let charList = ['a'..'p']
  print $ solve comandList charList


solve :: [String] -> [Char] -> [Char]
solve [] input = "pink"
solve [x] input = editChars x input
solve (x:xs) input = solve xs $ editChars x input


editChars :: String -> [Char] -> [Char]
editChars x input
  | head x == 's' = let index = (read::String -> Int) $ tail' x
    in spin index input
  | head x == 'x' = let indicies = readTuple $ splitOn "/" $ tail' x
    in swapPos indicies input
  | head x == 'p' = let chrs = map head $ splitOn "/" $ tail' x
    in swapChar (chrs !! 0, chrs !! 1) input
  | otherwise = error "failure"


tail' :: [a] -> [a]
tail' input = if length input == 0
  then []
  else tail input


spin :: Int -> [Char] -> [Char]
spin spinCount input = newCharList
  where
    (top, bottom) = splitAt (length input - spinCount) input
    newCharList = bottom ++ top


swapPos :: (Int, Int) -> [Char] -> [Char]
swapPos (x, y) input = newCharList
  where
    val1 = input !! x
    val2 = input !! y
    (top, bottom) = splitAt x input
    newTop = top ++ [val2]
    (nTop, nBottom) = splitAt (y - x) bottom
    newBottom = (tail' nTop) ++ [val1] ++ (tail' nBottom)
    newCharList = newTop ++ newBottom


swapChar :: (Char, Char) -> [Char] -> [Char]
swapChar (cx, cy) input = swapPos indicies input
  where
    index1 = getCharPos cx input
    index2 = getCharPos cy input
    indicies = if index1 < index2
      then (index1, index2)
      else (index2, index1)
      

readTuple :: [String] -> (Int, Int)
readTuple (x:y:xs) = tuple
  where
    newX = (read::String -> Int) x
    newY = (read::String -> Int) y 
    tuple = if newX < newY
      then (newX, newY)
      else (newY, newX)

getCharPos :: Char -> [Char] -> Int
getCharPos ch input = case elemIndex ch input of
  Just x -> x
  Nothing -> error "Failed"
