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
solve count walls = if calculateSolution count walls /= 0
  then solve (count + 1) walls
  else count


calculateSolution :: Int -> [[Int]] -> Int
calculateSolution counter walls
  | length walls == 0 = 0
  | otherwise = calculateThreat counter x + (calculateSolution nextCounter xs)
  where
    x = head walls
    xs = tail walls
    wallNumber = head x
    wallSize = last x
    nextCounter = counter + ((nextWall xs) - wallNumber)

nextWall :: [[Int]] -> Int
nextWall [] = 1000
nextWall (x:xs) = head x


calculateThreat :: Int -> [Int] -> Int
calculateThreat counter wall = if intersects
  then 1
  else 0
  where
    wallNumber = head wall
    depth = last wall
    intersects = counter `mod` ((depth - 1) * 2) == 0

