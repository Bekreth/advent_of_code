import Data.Char
import Data.Maybe 

import qualified Data.Map as Map

data Node = Node String Int deriving Show
data Tree = Empty | Tree Node [Tree] deriving Show

main = do
  file <- readFile "data.txt"
  let textLines = lines file
  print $ solve (map words textLines) Map.empty

solve :: [[String]] -> Map.Map String Tree -> Tree
solve inputStrings mIn 
  | length inputStrings == 0 = snd $ head $ Map.toList mIn
  | length currentNode == 2 = solve remainingNodes (Map.insert (head currentNode) (oneLeafTree currentNode) cleanedMap)
  | canCollapse = solve remainingNodes (Map.insert (head currentNode) collapsedTree cleanedMap)
  | otherwise = solve (remainingNodes ++ [currentNode]) mIn
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







