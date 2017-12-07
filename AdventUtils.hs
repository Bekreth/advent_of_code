module AdventUtils where

fileToData :: [String] -> [[Int]]
fileToData [] = []
fileToData (x:xs) = (map (read::String -> Int) stringArray) : fileToData xs
  where stringArray = words x


updateListElement :: [Int] -> Int -> Int -> [Int]
updateListElement inputArray newValue index = front ++ [newValue] ++ back
  where
  (front, back) = if index /= length inputArray 
    then removeElement $ splitAt index inputArray
    else (init inputArray, [])

removeElement :: ([Int], [Int]) -> ([Int], [Int])
removeElement (x,y) = (x, tail y)
