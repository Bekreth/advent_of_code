import Data.Char
import Data.List.Split

main = do
  file <- readFile "data.txt"
  let splitData = splitOn "," file
  let newData = init splitData ++ [init $ last splitData]
  print "In hex coordinates, the largest value is the steps from the coorindate center"
  print $ solve newData (0, 0, 0) 


solve :: [String] -> (Int, Int, Int) -> (Int, Int, Int)
solve [] coordinates = coordinates
solve (x:xs) (a,b,c)
    | x == "n" = solve xs (a, b + 1, c - 1)  
    | x == "ne" = solve xs (a + 1, b, c - 1)
    | x == "se" = solve xs (a + 1, b - 1, c) 
    | x == "s" = solve xs (a, b - 1, c + 1) 
    | x == "sw" = solve xs (a - 1, b, c + 1) 
    | x == "nw" = solve xs (a - 1, b + 1, c) 
