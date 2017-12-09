import Data.Char
import qualified Data.Set as Set


main = do
  file <- readFile "data.txt"
  let textLines = lines file
  let controlSet = Set.fromList ['{', '}', '<', '>', '!']
  let cancelFreeData = removeCancels (head textLines)
  let cleanedData = removeNonControl cancelFreeData controlSet
  let bracketData = removeGarbage cleanedData False 
  print $ solve bracketData 0


solve :: [Char] -> Int -> Int
solve [] _ = 0
solve (x:xs) inValue 
  | x == '{' = solve xs (inValue + 1)
  | x == '}' = inValue + (solve xs (inValue - 1))


removeNonControl :: [Char] -> Set.Set Char -> [Char]
removeNonControl [] _ = []
removeNonControl (x:xs) control = if Set.member x control
  then x:(removeNonControl xs control)
  else removeNonControl xs control

removeCancels :: [Char] -> [Char]
removeCancels [] = []
removeCancels (x:xs)
  | x == '!' = removeCancels $ tail xs
  | otherwise = x:(removeCancels xs)

removeGarbage :: [Char] -> Bool -> [Char]
removeGarbage [] _ = []
removeGarbage (x:xs) openGarbage
  | x == '<' && not openGarbage = removeGarbage xs True
  | x == '<' && openGarbage = removeGarbage xs openGarbage
  | x == '>' && openGarbage = removeGarbage xs False
  | x == '>' && not openGarbage = removeGarbage xs openGarbage
  | openGarbage = removeGarbage xs openGarbage
  | otherwise = x:(removeGarbage xs openGarbage)

