import Data.Char
import Numeric
import Data.List.Split


main = do
  let dividens = 2147483647
  let generators = (16807, 48271)
  let genSeeds = (289, 629)
  let testSeeds = (65, 8921)
  print $ solve 0 generators genSeeds dividens


solve :: Int -> (Int, Int) -> (Int, Int) -> Int -> Int
solve count (genA, genB) (prevA, prevB) dividens
  | count == 5000000 = 0
  | otherwise = newValue + solve (count + 1) (genA, genB) (aOut, bOut) dividens
  where
    aOut = genValue genA prevA (4, dividens)
    bOut = genValue genB prevB (8, dividens)
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


genValue :: Int -> Int -> (Int, Int) -> Int
genValue gen prevValue (smallMod, bigMod) = if newValue `mod` smallMod == 0
  then newValue
  else genValue gen newValue (smallMod, bigMod)
  where
    newValue = (gen * prevValue) `mod` bigMod


