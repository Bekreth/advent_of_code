import Data.Char

main = do
  file <- readFile "data.txt"
  let strings = lines file
  print $ solveAll strings

solveAll :: [String] -> Int
solveAll [x] = solveLine x
solveAll (x:xs) = solveLine x + (solveAll xs)

solveLine :: String -> Int
solveLine x = head [ v1 `div` v2 | v1 <- list, v2 <- list, v1 `div` v2 /= 1, v1 `mod` v2 == 0]
  where list = map read $ words x :: [Int]


