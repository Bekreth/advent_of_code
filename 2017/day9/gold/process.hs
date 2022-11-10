import Data.Char

main = do
  file <- readFile "data.txt"
  let textLines = lines file
  print $ removeGarbage (removeCancels $ head textLines) False

removeCancels :: [Char] -> [Char]
removeCancels [] = []
removeCancels (x:xs)
  | x == '!' = removeCancels $ tail xs
  | otherwise = x:(removeCancels xs)

removeGarbage :: [Char] -> Bool -> Int
removeGarbage [] _ = 0
removeGarbage (x:xs) openGarbage
  | x == '<' && not openGarbage = removeGarbage xs True
  | x == '<' && openGarbage = 1 + (removeGarbage xs openGarbage)
  | x == '>' && openGarbage = removeGarbage xs False
  | x == '>' && not openGarbage = 1 + (removeGarbage xs openGarbage)
  | openGarbage = 1 + (removeGarbage xs openGarbage)
  | otherwise = removeGarbage xs openGarbage
