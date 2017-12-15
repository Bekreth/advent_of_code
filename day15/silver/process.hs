import Data.Char
import Numeric
import Data.List.Split


main = do
  let dividens = 2147483647
  let generators = (16807, 48271)
  let genSeeds = (289, 629)
  print $ solve 0 generators genSeeds dividens


solve :: Int -> (Int, Int) -> (Int, Int) -> Int -> Int
solve count (genA, genB) (prevA, prevB) dividens
  | count == 40000000 = 0
  | otherwise = newValue + solve (count + 1) (genA, genB) (aOut, bOut) dividens
  where
    aOut = (prevA * genA) `mod` dividens
    bOut = (prevB * genB) `mod` dividens
    aBin = snd $ splitAt 16 $ toBin aOut
    bBin = snd $ splitAt 16 $ toBin bOut
    newValue = if aBin == bBin
      then 1
      else 0
    

toBin :: Int -> String
toBin input = 
  let newString = showIntAtBase 2 intToDigit input ""
      padLength = 32 - (length newString)
      allPad = ['0'| x <- [0..32]]
      padding = (fst $ splitAt padLength allPad) ++ newString
  in padding
