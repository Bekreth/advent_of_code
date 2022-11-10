import Data.Char

main = do
  file <- readFile "data.txt"
  let stringLines = lines file
  let ints = map (read::String -> Int) stringLines
  print $ solve 0 0 ints

solve :: Int -> Int -> [Int] -> Int
solve count offset array
  | offset >= length array = count
  | otherwise = solve (count + 1) (offset + instruction) newArray
  where
    splitArray = splitAt (offset + 1) array
    instruction = (last $ fst splitArray)
    newArray = (init $ fst splitArray) ++ ((1 + instruction):[]) ++ (snd splitArray)


