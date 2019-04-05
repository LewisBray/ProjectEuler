main = print $ sum $ takeWhile (< 2000000) primes
    where primes = filter isPrime [1..]

factors :: (Integral a) => a -> [a]
factors n = 
    let root = floor $ sqrt $ fromIntegral n
        factorAccumulator = \a x -> if n `mod` x == 0 then x:(div n x):a else a
    in foldl factorAccumulator [] [1..root]

isPrime :: (Integral a) => a -> Bool
isPrime n
    | n <= 1    = False
    | otherwise = (length $ factors n) == 2
