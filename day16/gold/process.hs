import Data.Char
import Data.List.Split
import Data.List
import qualified Data.Map as Map

data Command = Command Bool ([Char] -> [Char]) 


main = do
  inputFile <- readFile "data.txt"
  let commandList = splitOn "," $ init inputFile
  let charList = ['a'..'p']
  let commands = map parseCommands commandList
  print $ findRepeat Map.empty 0 solve commands charList


{- Operates the transform function on the input value -}
findRepeat :: Map.Map [Char] Int -> Int -> ([Command] -> [Char] -> [Char]) -> [Command] -> [Char] -> (([Char], Int), ([Char], Int))
findRepeat mIn counter f commands input = if counter == 1000
  then error "noMatach"
  else case Map.lookup opperated mIn of
    Just x -> ((opperated, x), (opperated, counter))
    Nothing -> findRepeat (Map.insert opperated counter mIn) (counter + 1) f commands opperated
  where
    opperated = f commands input


solve :: [Command] -> [Char] -> [Char]
solve [] input = "pink"
solve [(Command _ x)] input = x input
solve ((Command _ x):xs) input = solve xs $ x input

{- Create commands -}
parseCommands :: String -> Command
parseCommands x
  | head x == 's' = let index = (read::String -> Int) $ tail' x
    in Command True (spin index)
  | head x == 'x' = let indicies = readTuple $ splitOn "/" $ tail' x
    in Command True (swapPos indicies)
  | head x == 'p' = let chrs = map head $ splitOn "/" $ tail' x
    in Command False (swapChar (chrs !! 0, chrs !! 1))
  | otherwise = error "failure"

tail' :: [a] -> [a]
tail' input = if length input == 0
  then []
  else tail input


{- Base utility mapping -}
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
