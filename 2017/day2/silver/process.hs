import Data.Char

main = do
  file <- readFile "data.txt"
  let strings = lines file
  print $ solveAll strings

solveAll :: [String] -> Int
solveAll [x] = solveLine x
solveAll (x:xs) = solveLine x + (solveAll xs)

solveLine :: String -> Int
solveLine x = maximum numbers - (minimum numbers)
  where numbers = map read $ words x :: [Int]
