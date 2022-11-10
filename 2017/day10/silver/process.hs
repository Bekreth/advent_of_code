import Data.List


main = do
  let knotList = [183,0,31,146,254,240,223,150,2,206,161,1,255,232,199,88]
  let inList = [0..255]
  print $ solve inList knotList (0, 0)


solve :: [Int] -> [Int] -> (Int, Int) -> Int
solve (x:y:xs) [] _ = x * y
solve cycle (x:xs) (pos, skip) = solve newCycle xs (newPos, newSkip)
  where
    inverseRotate = (length cycle) - pos
    cycle1 = resetCyclic cycle pos
    (top, bot) = splitAt x cycle1
    newCycle = resetCyclic (reverse top ++ bot) inverseRotate
    newPos = (pos + x + skip) `mod` (length cycle)
    newSkip = skip + 1


resetCyclic :: [Int] -> Int -> [Int]
resetCyclic cyclic offset = bottom ++ top
  where
    (top, bottom) = splitAt offset cyclic
