import Data.Char
import qualified Data.List as List
import qualified Data.Map as Map

data Register = Register { name :: String,
  value :: Int
  } deriving Show
data Operation = Inc | Dec deriving (Show, Eq)
data Equality = LT | LTE | E | NE | GTE | GT deriving (Show, Eq)
data Instruction = Instruction { baseRegister :: Register,
  op :: Operation,
  shiftValue :: Int,
  compareRegister :: Register,
  equality :: Equality,
  compareValue ::Int
  } deriving Show


instance Eq Register 
  where
    Register name1 value1 == Register name2 value2 = value1 == value2


instance Ord Register
  where
    Register name1 value1 < Register name2 value2 = value1 < value2
    Register name1 value1 > Register name2 value2 = value1 > value2
    Register name1 value1 <= Register name2 value2 = value1 <= value2


main = do
  file <- readFile "data.txt"
  let textLines = lines file
  print $ solve (map words textLines) Map.empty 0


solve :: [[String]] -> Map.Map String Register -> Int -> Int
solve inputStrings mIn peakValue
  | length inputStrings == 0 = sortRegisters mIn peakValue
  | otherwise = solve carryOver (executeInstruction instruction newM) updatedPeak
  where 
    leadingValue = head inputStrings
    carryOver = tail inputStrings
    (instruction, newM) = readInstruction leadingValue mIn
    updatedPeak = sortRegisters newM peakValue


readInstruction :: [String] -> Map.Map String Register -> (Instruction, Map.Map String Register)
readInstruction [r, o, i, _, cr, e, v] mIn = (Instruction register opperation value compareRegister equality compareValue, newMap)
  where
    register = Map.findWithDefault (Register r 0) r mIn
    opperation = if o == "inc"
      then Inc
      else Dec
    value = (read::String -> Int) i
    compareRegister = Map.findWithDefault (Register cr 0) cr mIn
    equality = case e of
      "<" -> Main.LT
      "<=" -> Main.LTE
      "==" -> Main.E
      "!=" -> Main.NE
      ">=" -> Main.GTE
      ">" -> Main.GT
    compareValue = (read::String -> Int) v
    newMap = Map.insert (name compareRegister) compareRegister (Map.insert (name register) register mIn)


executeInstruction :: Instruction -> Map.Map String Register -> Map.Map String Register
executeInstruction instruction mIn = if evaluteExpression instruction == True
  then Map.insert registerName updatedRegister mIn
  else mIn
  where
    register = (baseRegister instruction)
    registerName = (name register)
    v1 = (value register)
    updatedRegister = if (op instruction) == Inc
      then Register registerName (v1 + (shiftValue instruction))
      else Register registerName (v1 - (shiftValue instruction))


evaluteExpression :: Instruction -> Bool
evaluteExpression instruction
  | e == Main.LT = rv < v3 
  | e == Main.LTE = rv <= v3
  | e == Main.E = rv == v3
  | e == Main.NE = rv /= v3
  | e == Main.GTE = rv >= v3
  | e == Main.GT = rv > v3
  where
    e = (equality instruction)
    rv = (value (compareRegister instruction))
    v3 = (compareValue instruction)


sortRegisters :: Map.Map String Register -> Int -> Int
sortRegisters mIn peakValue = if (value register) > peakValue
  then (value register)
  else peakValue
    where
      register = last $ List.sort $ map snd (Map.toList mIn)



