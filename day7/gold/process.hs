import Data.Char
import Data.Maybe 
import Data.List
import qualified Data.Map as Map

data Node = Node String Int deriving (Show, Ord, Eq)
data Tree = Empty | Tree Node [Tree] deriving (Show, Ord, Eq)

main = do
  file <- readFile "data.txt"
  let textLines = lines file
  let bigTree = buildBaseTree (map words textLines) Map.empty
  print $ findDiscrepency (0, 0, bigTree)

findDiscrepency :: (Int, Int, Tree) -> Int
findDiscrepency (previous, current, (Tree (Node name value) trees))
  | noDiscrepency = (previous - current) + value
  | otherwise = findDiscrepency nextIteration
  where 
    noDiscrepency = if fst weightHead == fst weightTail
      then True
      else False
    weights = sort $ treeTuple trees
    weightHead = head weights
    weightTail = last weights
    weightThird = head $ init weights
    nextIteration = if fst weightHead == fst weightThird
      then (fst weightHead, fst weightTail, snd weightTail)
      else (fst weightTail, fst weightHead, snd weightHead)

treeTuple :: [Tree] -> [(Int, Tree)]
treeTuple [] = []
treeTuple (x:xs) = (treeWeight [x], x) : treeTuple xs

treeWeight :: [Tree] -> Int
treeWeight [] = 0
treeWeight ((Tree (Node _ value) t):ts) = value + (treeWeight ts) + (treeWeight t)

buildBaseTree :: [[String]] -> Map.Map String Tree -> Tree
buildBaseTree inputStrings mIn 
  | length inputStrings == 0 = snd $ head $ Map.toList mIn
  | length currentNode == 2 = buildBaseTree remainingNodes (Map.insert (head currentNode) (oneLeafTree currentNode) cleanedMap)
  | canCollapse = buildBaseTree remainingNodes (Map.insert (head currentNode) collapsedTree cleanedMap)
  | otherwise = buildBaseTree (remainingNodes ++ [currentNode]) mIn
  where
    currentNode = head inputStrings
    remainingNodes = tail inputStrings
    canCollapse = if length currentNode == 2
      then False
      else checkTreeMap (tail $ tail currentNode) mIn
    collapsedTree = if canCollapse
      then collapseTree currentNode mIn
      else Empty
    cleanedMap = if canCollapse
      then cleanMap (tail $ tail currentNode) mIn
      else mIn

oneLeafTree :: [String] -> Tree
oneLeafTree [name, value] = Tree (Node name $ (read::String->Int) value) []


checkTreeMap :: [String] -> Map.Map String Tree -> Bool
checkTreeMap [x] mIn = Map.member x mIn
checkTreeMap (x:xs) mIn = Map.member x mIn && (checkTreeMap xs mIn)


collapseTree :: [String] -> Map.Map String Tree -> Tree
collapseTree (name:value:others) mIn = Tree (Node name $ (read::String->Int) value) (getTrees others mIn)


getTrees :: [String] -> Map.Map String Tree -> [Tree]
getTrees [] _ = []
getTrees (x:xs) mIn = (fromJust $ Map.lookup x mIn) : (getTrees xs mIn)


cleanMap :: [String] -> Map.Map String Tree -> Map.Map String Tree
cleanMap [] mIn = mIn
cleanMap (x:xs) mIn = cleanMap xs $ Map.delete x mIn







