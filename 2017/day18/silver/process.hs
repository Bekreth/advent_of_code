import Data.Char
import qualified Data.Map as Map


data Instruction = Reg {instruction :: String, v1 :: String, v2 :: String} | IO {instruction :: String, v1 :: String} deriving Show


main = do
  file <- readFile "data.txt"
  let instructions = map (buildInstructions . words) $ lines file
  print $ solve (instructions, 0) 0 Map.empty


buildInstructions :: [String] -> Instruction
buildInstructions input = if l == 3
  then Reg (input !! 0) (input !! 1) (input !! 2)
  else 
    if l == 2
      then IO (input !! 0) (input !! 1)
      else error "Goofed"
  where
    l = length input


solve :: ([Instruction], Int) -> Int ->  Map.Map String Int -> Map.Map String Int
solve (instrcs, pos) output regs
  | current == "set" = solveNext (Map.insert vi1 vi2 regs)
  | current == "add" = solveNext (adjust (\x -> vi2 + x) vi1 regs) 
  | current == "mul" = solveNext (adjust (\x -> vi2 * x) vi1 regs) 
  | current == "mod" = solveNext (adjust (\x -> x `mod` vi2) vi1 regs) 
  | current == "snd" = solve next (Map.findWithDefault 0 vi1 regs) regs
  | current == "rcv" = if Map.findWithDefault 0 vi1 regs == 0
    then solveNext regs
    else Map.insert "ZZ" output regs
  | current == "jgz" = 
    let val = if (isAlpha . head) vi1 
          then 
            case Map.lookup vi1 regs of
              Just x -> if x > 0 then vi2 else 1
              Nothing -> 1
          else vi2
        nextInstruction = (instrcs, (pos + val))
    in solve nextInstruction output regs
  | current == "break" = eExit
  | otherwise = regs
  where
    currentInstruction = if pos >= length instrcs
      then Reg "None" "" ""
      else instrcs !! pos
    current = instruction currentInstruction
    vi1 = v1 currentInstruction
    vi2 = case currentInstruction of
      (Reg _ _ _) -> resolveV2 currentInstruction regs
      (IO _ _) -> 0
    next = (instrcs, pos + 1)
    solveNext = solve next output
    eExit = error $ show (instrcs !! (pos + 1), regs, pos, output)
    

resolveV2 :: Instruction -> Map.Map String Int -> Int
resolveV2 instruction register = if (isAlpha . head) iv2
  then Map.findWithDefault 0 iv2 register
  else (read::String -> Int) iv2
  where
    iv2 = v2 instruction


adjust :: (Int -> Int) -> String -> Map.Map String Int -> Map.Map String Int
adjust f key mIn = case Map.lookup key mIn of
  Just x -> Map.adjust f key mIn
  Nothing -> Map.insert key 0 mIn






