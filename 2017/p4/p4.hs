import Data.Set (Set)
import Data.List (sort)
import qualified Data.Set as Set

areAllUnique :: Ord a => [a] -> Bool
areAllUnique items =
    let origLen = length items
        iset = Set.fromList items
        newLen = Set.size iset
    in origLen == newLen

p1 :: String -> Int
p1 s =
    let phrases = map words $ lines s
        valid   = filter (\l -> areAllUnique l) phrases
    in length valid

p2 :: String -> Int
p2 s =
    let phrases = map words $ lines s
        sorted  = map (\l -> map sort l) phrases
        valid   = filter (\l -> areAllUnique l) sorted
    in length valid

main = getContents
    >>= (\s -> return $ (p1 s, p2 s))
    >>= print
