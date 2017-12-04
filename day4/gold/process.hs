import Data.List
import Data.Char
import qualified Data.Set as Set

main = do
  file <- readFile "data.txt"
  let strings = lines file
  print $ solveAll 0 strings

solveAll :: Int -> [String] -> Int
solveAll output [x] = if solveLine Set.empty (words x)
  then output + 1
  else output
solveAll output (x:xs) = if solveLine Set.empty (words x)
  then (solveAll output xs) + 1
  else solveAll output xs

solveLine :: Set.Set String ->[String] -> Bool
solveLine s [x] = Set.notMember (sort x) s
solveLine s (x:xs) = if Set.member (sort x) s
  then False
  else solveLine (Set.insert (sort x) s) xs
