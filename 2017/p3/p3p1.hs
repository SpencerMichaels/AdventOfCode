import Data.List (inits)
import Data.Map (Map)
import qualified Data.Map as Map

oddSquares = map (\i -> i*i) [1,3..]

countDown :: Int -> [Int]
countDown n = [n, n-1.. 0]

outerLoop :: Int -> [Int]
outerLoop dist =
    let l = countDown dist
        l' = drop 1 $ l ++ (drop 1 $ reverse l)
    in cycle l'

p1 :: Int -> Int
p1 n =
    let radDist  = length $ takeWhile (\i -> i < n) $ oddSquares
        perpDist = last $ take (n - (last $ take 1 oddSquares)) $ outerLoop radDist
    in radDist + perpDist

-- p2 is just annoying

main = getLine
    >>= (\ln -> return (read ln::Int))
    >>= (\n -> return $ p1 n)
    >>= print
