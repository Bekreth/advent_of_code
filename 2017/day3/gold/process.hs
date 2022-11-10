import qualified Data.Map as Map

data Point = Point Int Int deriving (Eq, Ord, Show)  
data Direction = UP | RIGHT | DOWN | LEFT deriving (Enum, Eq)
data PValue = PValue Point Int deriving (Show)  

main = do
  let valMap = Map.insert (Point 0 0) 1 . Map.insert (Point 1 0) 1 . Map.insert (Point 1 1) 2 . Map.insert (Point 0 1) 4 . Map.insert (Point (-1) 1) 5 . Map.insert (Point (-1) 0) 10 $ Map.empty
  print $ solve valMap (Point (-1) (-1)) RIGHT 3



solve :: Map.Map Point Int -> Point -> Direction -> Int -> Int
solve m p d i
  | value > 347991 = value 
  | otherwise = solve (Map.insert p value m) (f1 hold) (f2 hold) (f3 hold)
  where
    hold = step p d i
    value = ringLookup p m



ringLookup :: Point -> Map.Map Point Int -> Int
ringLookup p m = sum $ tryLookup (ring p) m


ring :: Point -> [Point]
ring (Point x y) = points
  where points = (Point (x+1) y) : (Point (x+1) (y+1)) : (Point x (y+1)) : (Point (x-1) (y+1)) : (Point (x-1) y) : (Point (x-1) (y-1)) : (Point x (y-1)) : (Point (x+1) (y-1)) : []


tryLookup :: [Point] -> Map.Map Point Int -> [Int]
tryLookup [p] m = case (Map.lookup p m) of
  Nothing -> []
  Just p -> [p]
tryLookup (p:ps) m = case (Map.lookup p m) of
  Nothing -> tryLookup ps m
  Just v -> v : tryLookup ps m 



step :: Point -> Direction -> Int -> (Point, Direction, Int)
step p d i
  | i > 0 = (plusDirection p d, d, i - 1)
  | i == 0 = (plusDirection p newDirection, newDirection, stepCount)
  where
    newDirection = rotate d
    stepCount = determineStepCount p newDirection

determineStepCount :: Point -> Direction -> Int
determineStepCount (Point px py) d
  | d == RIGHT = (abs $ px * 2)
  | d == UP = (abs $ py * 2)
  | d == LEFT = (abs $ px * 2) - 1
  | d == DOWN = (abs $ py * 2) - 1

plusDirection :: Point -> Direction -> Point
plusDirection (Point px py) d
  | d == UP = Point px (py + 1)
  | d == RIGHT = Point (px + 1) py
  | d == DOWN = Point px (py - 1)
  | d == LEFT = Point (px - 1) py


rotate :: Direction -> Direction
rotate UP = LEFT
rotate LEFT = DOWN
rotate DOWN = RIGHT
rotate RIGHT = UP

f1 :: (Point, Direction, Int) -> Point
f1 (x, _, _) = x

f2 :: (Point, Direction, Int) -> Direction
f2 (_, x, _) = x

f3 :: (Point, Direction, Int) -> Int
f3 (_, _, x) = x



