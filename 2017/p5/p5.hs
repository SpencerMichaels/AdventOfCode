countJumps :: [Int] -> Int -> (Int -> Int) -> Int
countJumps jumps i f
    | (i < 0 || i >= length jumps) = 0
    | otherwise =
        let jump = jumps !! i
            jumps' = (take i jumps) ++ [(f jump)] ++ (drop (i+1) jumps)
            i' = i + jump
        in 1 + countJumps jumps' i' f
    
p1 :: [Int] -> Int
p1 jumps = countJumps jumps 0 (\j -> j+1)

p2 :: [Int] -> Int
p2 jumps = countJumps jumps 0 (\j -> if j < 3 then j+1
                                              else j-1)

readInts :: String -> [Int]
readInts = map read . words

main = getContents
    >>= (\s -> return $ readInts s)
    >>= (\ns -> return $ (p1 ns, p2 ns))
    >>= print
