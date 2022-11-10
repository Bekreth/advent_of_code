import Data.Char
import Data.Maybe
import qualified Data.Map as Map
import qualified Data.List as List

main = do
  let inputData = [11,11,13,7,0,15,5,5,4,4,1,1,7,1,15,11]
  print $ solve inputData 0 Map.empty


solve :: [Int] -> Int -> Map.Map [Int] Int -> Int
solve input count seenSet
  | Map.member input seenSet = (fromJust (Map.lookup input seenSet)) - count
  | otherwise = solve newInput (count + 1) (Map.insert input count seenSet)
  where
    newInput = reallocate input


reallocate :: [Int] -> [Int]
reallocate inputArray = listWalker maxElement maxIndex evaluationArray
  where
    maxElement = maximum inputArray
    maxIndex = fromJust $ List.elemIndex maxElement inputArray
    evaluationArray = updateListElement inputArray 0 maxIndex


listWalker :: Int -> Int -> [Int] -> [Int]
listWalker remainder indexAt inputArray
  | remainder == 0 = inputArray
  | remainder > 0 = listWalker (remainder - 1) newIndex newArray
  where
    newIndex = if indexAt == (length inputArray) - 1
      then 0
      else (indexAt + 1)
    newArray = updateListElement inputArray ((inputArray !! newIndex) + 1) newIndex


updateListElement :: [Int] -> Int -> Int -> [Int]
updateListElement inputArray newValue index = front ++ [newValue] ++ back
  where
    (front, back) = if index /= length inputArray 
    then removeElement $ splitAt index inputArray
    else (init inputArray, [])


removeElement :: ([Int], [Int]) -> ([Int], [Int])
removeElement (x,y) = (x, tail y)

