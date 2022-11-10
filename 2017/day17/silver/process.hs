import Data.List
import Data.List.Split

main = do
  let fullArray = solve 2017 [0, 1]
  let after = case elemIndex 2017 fullArray of
        Just x -> x
        Nothing -> error "failed"
  print $ fullArray !! (after + 1)


solve :: Int -> [Int] -> [Int]
solve 1 iArray = iArray
solve counter iArray = solve (counter - 1) $ incrementSpinLock iArray


incrementSpinLock :: [Int] -> [Int]
incrementSpinLock input = insertAt newIndex listSize input
  where
    listSize = length input
    currentPos = case elemIndex (listSize - 1) input of
      Just x -> x
      Nothing -> error $ show (listSize, input)
    newIndex = insertIndex currentPos listSize


insertIndex :: Int -> Int -> Int
insertIndex pos length = if newPos > (length - 1)
  then newPos `mod` length
  else newPos
  where
    newPos = pos + step + 1
    step = 355


insertAt :: Int -> Int -> [Int] -> [Int] 
insertAt z y xs = as ++ (y:bs)
                  where (as,bs) = splitAt z xs

