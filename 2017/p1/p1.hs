import Data.Char (digitToInt)

rotate :: Int -> [a] -> [a]
rotate _ [] = []
rotate n xs = zipWith const (drop n (cycle xs)) xs

captcha :: [Char] -> Int -> Int
captcha s rot =
  foldl (\acc (x, y) -> acc + digitToInt x) 0
    $ filter (\(x, y) -> x == y)
      $ zip s (rotate rot s)

p1 :: [Char] -> Int
p1 s = captcha s 1

p2 :: [Char] -> Int
p2 s = captcha s $ (length s) `div` 2

main = getLine
  >>= (\s -> return $ (p1 s, p2 s))
  >>= print

