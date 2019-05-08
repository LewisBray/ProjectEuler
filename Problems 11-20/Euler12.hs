main = print $ head $ filter ((> 500) . length . factors) triangleNumbers

triangleNumbers :: [Integer]
triangleNumbers = scanl1 (+) [1..]

factors :: (Integral a) => a -> [a]
factors n = 
    let root = floor $ sqrt $ fromIntegral n
        factorAccumulator = \a x -> if n `mod` x == 0 then x:(div n x):a else a
    in foldl factorAccumulator [] [1..root]
