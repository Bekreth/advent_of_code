import Data.Char
import Data.List.Split

main = do
  file <- readFile "data.txt"
  let splitData = splitOn "," file
  let newData = init splitData ++ [init $ last splitData]
  print $ solve newData (0, 0, 0) 0 


solve :: [String] -> (Int, Int, Int) -> Int -> Int 
solve [] coordinates max = max
solve (x:xs) (a,b,c) max
    | x == "n" = solve xs (a, b + 1, c - 1) newMax 
    | x == "ne" = solve xs (a + 1, b, c - 1) newMax 
    | x == "se" = solve xs (a + 1, b - 1, c) newMax 
    | x == "s" = solve xs (a, b - 1, c + 1) newMax 
    | x == "sw" = solve xs (a - 1, b, c + 1) newMax 
    | x == "nw" = solve xs (a - 1, b + 1, c) newMax 
    where
      newMax = if abs a > max
        then abs a
        else 
          if abs b > max
            then abs b
            else 
              if abs c > max
                then abs c
                else max
