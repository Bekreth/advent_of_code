main = do
  let s1 = solve 10000000 (1, 2, 1)
  print s1
  let s2 = solve 10000001 s1
  print s2
  let s3 = solve 10000001 s2
  print s3
  let s4 = solve 10000001 s3
  print s4
  let s5 = solve 10000001 s4
  print s5


solve :: Int -> (Int, Int, Int) -> (Int, Int, Int)
solve 1 (pos, length, currentAnswer) = (pos, length, currentAnswer)
solve count (pos, length, currentAnswer) = solve (count - 1) (newPos, length + 1, newAnswer)
  where
    newPos = insertIndex pos length
    newAnswer = if newPos == 1
      then length
      else currentAnswer


insertIndex :: Int -> Int -> Int
insertIndex pos length = if newPos > length
  then newPos `mod` length
  else newPos
  where
    newPos = pos + step + 1
    step = 355

