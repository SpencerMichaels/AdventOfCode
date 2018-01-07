import Data.List (find)

readInts :: String -> [Int]
readInts = map read . words

data MinMax = MinMax { mmin :: Int
                     , mmax :: Int
                     } deriving (Show)

getMinMax :: [Int] -> MinMax
getMinMax xs = MinMax (foldl min 99999 xs) (foldl max 0 xs)

mmDiff :: MinMax -> Int
mmDiff mm = (mmax mm) - (mmin mm)

p1 :: [[Int]] -> Int
p1 iss = sum . (map (\is -> mmDiff $ getMinMax is)) $ iss

findDivisor :: Int -> [Int] -> Maybe Int
findDivisor i is =
  let isDivisorOf = (\x y -> x `rem` y == 0 && x /= y && y /= 1)
  in find (isDivisorOf i) is

findNumDiv :: [Int] -> Maybe (Int, Int)
findNumDiv is =
  head
  $ filter (\x -> x /= Nothing)
  $ map ((\i -> findDivisor i is >>= (\j -> Just (i, j)))) is

p2 :: [[Int]] -> Int
p2 iss = foldl (\acc is -> case findNumDiv is of Nothing -> 0
                                                 Just (x, y) -> acc + x `div` y) 0 iss 

main = getContents
  >>= (\s -> return $ map readInts $ lines s)
  >>= (\is -> return $ (p1 is, p2 is))
  >>= print
