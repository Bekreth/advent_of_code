import Data.Char

main = do
  file <- readFile "data.txt"
  let fileLines = lines file
  let parsedFile = map words fileLines
  let walls = readToInt parsedFile
  print $ solve 0 walls


readToInt :: [[String]] -> [[Int]]
readToInt [] = []
readToInt (x:xs) = map (read::String -> Int) x : readToInt xs


solve :: Int -> [[Int]] -> Int
solve counter walls
  | length walls == 0 = 0
  | counter /= wallNumber = solve (counter + 1) walls
  | otherwise = calculateThreat counter x + (solve (counter + 1) xs)
  where
    x = head walls
    xs = tail walls
    wallNumber = head x
    wallSize = last x
    


calculateThreat :: Int -> [Int] -> Int
calculateThreat counter wall = if intersects
  then wallNumber * depth
  else 0
  where
    wallNumber = head wall
    depth = last wall
    intersects = counter `mod` ((depth - 1) * 2) == 0

