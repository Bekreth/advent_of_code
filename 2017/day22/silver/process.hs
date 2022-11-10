import Data.Char
import Debug.Trace
import qualified Data.Map as Map

data Orientation = North | East | South | West deriving (Bounded, Enum, Eq, Show)
data Point = Point { xPos :: Int, yPos :: Int} deriving (Eq, Show, Ord)
data Virus = Virus { location :: Point,  ori :: Orientation} deriving Show

main = do
  input <- readFile "data.txt"
  let info = map words $ lines input
  let walkMap = buildMap info
  let startVirus = Virus (Point 0 0) North
  print $ (solve (startVirus, walkMap) 10000) - 1


buildMap :: [[String]] -> Map.Map Point Bool
buildMap input = foldl (\mIn (k, v) -> Map.insert k v mIn) Map.empty output
  where
    cop = ((length input) - 1) `div` 2
    con = (-1 * cop)
    ray = [con..cop]
    boolList = map (\x -> map (\y -> y == "#") x) input
    output = [((Point x y), b) | y <- ray, x <- ray, let b = ((boolList !! ((-1 * y) + cop)) !! (x + cop))]


solve :: (Virus, Map.Map Point Bool) -> Int -> Int
solve input counter
  | counter == 0 = outputValue
  | otherwise = outputValue + solve (newVirus, newMap) (counter - 1)
  where
    (newVirus, newMap, output) = iterateV input
    outputValue = if output
      then 1
      else 0


iterateV :: (Virus, Map.Map Point Bool) -> (Virus, Map.Map Point Bool, Bool)
iterateV (virus, mIn) = (newVirus, newMap, flipped)
  where
    start = location virus
    localValue = Map.findWithDefault False start mIn
    flipped = not localValue
    rotate = if localValue
      then Virus start ((cycleNext . ori) virus)
      else Virus start ((cyclePrev . ori) virus)
    newVirus = walk rotate
    newMap = Map.insert start flipped mIn

walk :: Virus -> Virus
walk (Virus (Point x y) North) = (Virus (Point x (y + 1)) North)
walk (Virus (Point x y) West) = (Virus (Point (x - 1) y) West)
walk (Virus (Point x y) South) = (Virus (Point x (y - 1)) South)
walk (Virus (Point x y) East) = (Virus (Point (x + 1) y) East)


cyclePrev :: (Eq a, Enum a, Bounded a) => a -> a
cyclePrev x = if x == minBound then maxBound else pred x

cycleNext :: (Eq a, Enum a, Bounded a) => a -> a
cycleNext x = if x == maxBound then minBound else succ x

