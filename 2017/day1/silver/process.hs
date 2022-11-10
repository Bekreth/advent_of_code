import Data.Char

main = do
  input <- getLine
  let number = map digitToInt input
  print $ sumDigits number

sumDigits :: Integral x => [x] -> x
sumDigits [x,y] = if x == y
  then x
  else 0
sumDigits (x:y:xs) = if x == y 
  then x + (sumDigits $ y:xs)
  else sumDigits $ y:xs
