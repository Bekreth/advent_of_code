import Data.Char
import Debug.Trace
import qualified Data.Map as Map

data Bridge = Empty | Leg (Int, Int) Bridge deriving (Show, Read, Eq, Ord)

main = do
  fIn <- readFile "data.txt"
  let input = map (map (read::String -> Int) . words) $ lines fIn
  let legs = map constructLegs input
  let output = solve legs (Leg (0, 30) Empty)
  print output
  print $ bridgeValue output


constructLegs :: [Int] -> Bridge
constructLegs [x,y] = Leg (x, y) Empty


rvrs :: (Int, Int) -> (Int, Int)
rvrs (x,y) = (y,x)


con :: Bridge -> (Int, Int)
con (Leg nxt _) = nxt
con Empty = (0, 0)


next :: Bridge -> Bridge
next (Leg _ nxt) = nxt
next Empty = Empty


bridgeTail :: Bridge -> Bridge
bridgeTail leg = case (next leg) of
  (Leg _ b) -> bridgeTail b
  Empty -> leg


solve :: [Bridge] -> Bridge -> Bridge
solve [] currentBridge = currentBridge
solve legs currentBridge
  {-| trace (show (currentBridge, legs)) False = undefined-}
  | length nextSegments == 0 = currentBridge
  | otherwise = 
      let bridgeList = map (\x -> lengthen legs x currentBridge) nextSegments 
      in  longestBridge bridgeList
  where
    nextSegments = searchBridge legs currentBridge


lengthen :: [Bridge] -> Bridge -> Bridge -> Bridge
lengthen remaining nextLeg currentBridge = solve filtered following
  where
    filtered = filter (\x -> x /= nextLeg) remaining
    following = 
      if (fst $ con nextLeg) == (snd $ con currentBridge)
        then  (con nextLeg) `Leg` currentBridge
        else  (rvrs $ con nextLeg) `Leg` currentBridge


searchBridge :: [Bridge] -> Bridge -> [Bridge]
searchBridge [] _ = []
searchBridge (x:xs) currentBridge = if legMatch currentBridge x
  then searchBridge xs currentBridge ++ [x]
  else searchBridge xs currentBridge


legMatch :: Bridge -> Bridge -> Bool
legMatch x y = notSelf && (v2x == v1y || v2x == v2y)
  where
    notSelf = x /= y
    v2x = snd $ con x
    v1y = fst $ con y
    v2y = snd $ con y


longestBridge :: [Bridge] -> Bridge
longestBridge [x] = x
longestBridge (x:y:xs) = 
  if xl == yl 
    then  longestBridge (xs ++ [(largestBridge [x,y])])
    else  
      if xl > yl
        then longestBridge (xs ++ [x])
        else longestBridge (xs ++ [y])
  where
    xl = bridgeLength x
    yl = bridgeLength y


largestBridge :: [Bridge] -> Bridge
largestBridge [x] = x
largestBridge (x:y:xs) = 
  let vx = bridgeValue x
      vy = bridgeValue y
      bigger = if vx > vy
        then x
        else y
  in  largestBridge $ xs ++ [bigger]


bridgeLength :: Bridge -> Int
bridgeLength Empty = 0
bridgeLength (Leg _ nL) = 1 + (bridgeLength nL)

bridgeValue :: Bridge -> Int
bridgeValue (Leg (x, y) n) = (x + y) + (bridgeValue n)
bridgeValue Empty = 0




