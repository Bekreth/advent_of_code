import Data.Char
import qualified Data.Set as Set
import qualified Data.Map as Map

main = do
  file <- readFile "data.txt"
  let fileLines = lines file
  let limitation = 1000 * length fileLines
  let readDigit = map (read::String -> Int) . words
  let digits = map readDigit fileLines
  let dMap = mapCreator digits Map.empty
  print $ countGroups 2000 dMap 0
  {-print $ Set.size $ solve (Set.insert 0 Set.empty) limitation digits
-}

mapCreator :: [[Int]] -> Map.Map Int [Int] -> Map.Map Int [Int]
mapCreator [] mIn = mIn
mapCreator (x:xs) mIn = mapCreator xs $ Map.insert lead follow mIn
  where
    lead = head x
    follow = filter (/= lead) (tail x)


countGroups :: Int -> Map.Map Int [Int] -> Int -> Int
countGroups counter mIn groups
  | Map.size mIn == 0 = groups
  | Map.notMember counter mIn = countGroups (counter - 1) mIn groups
  | otherwise = countGroups (counter - 1) newMap (groups + 1)
  where
    newMap = cullMap [counter] mIn

cullMap :: [Int] -> Map.Map Int [Int] -> Map.Map Int [Int]
cullMap [] mIn = mIn
cullMap (x:xs) mIn = cullMap updatedList (Map.delete x mIn)
  where 
    updatedList = case (Map.lookup x mIn) of
      Just n -> xs ++ n
      Nothing -> xs
   
