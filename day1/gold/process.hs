import Data.Char

main = do
  input <- getLine
  let number = map digitToInt input
  let index = (length number) `div` 2
  let pairs = splitAt index number
  print $ join pairs

join :: ([Int], [Int]) -> Int
join ([], []) = 0
join ([x], [y]) = if x == y
  then x + y
  else 0
join (x:xs, y:ys) = if x == y
  then x + y + (join (xs, ys))
  else join (xs, ys)

