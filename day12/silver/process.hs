import Data.Char
import qualified Data.Set as Set

main = do
  file <- readFile "data.txt"
  let fileLines = lines file
  let limitation = 1000 * length fileLines
  let readDigit = map (read::String -> Int) . words
  let digits = map readDigit fileLines
  print $ Set.size $ solve (Set.insert 0 Set.empty) limitation digits


solve :: Set.Set Int -> Int -> [[Int]] -> Set.Set Int
solve inSet limiter (x:xs)
  | limiter == 0 = inSet
  | otherwise = solve newSet (limiter - 1) updatedData
  where
    lead = head x
    updatedData = if Set.member lead inSet
      then xs
      else xs ++ [x]
    newSet = if Set.member lead inSet
      then insertToSet inSet (tail x)
      else inSet

insertToSet :: Set.Set Int -> [Int] -> Set.Set Int
insertToSet inSet [] = inSet
insertToSet inSet (x:xs) = insertToSet (Set.insert x inSet) xs
