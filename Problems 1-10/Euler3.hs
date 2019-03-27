main = print $ maximum $ primeFactors 600851475143
    where primeFactors n = filter isPrime (factors n)

factors :: (Integral a) => a -> [a]
factors n = concat [ [x, div n x] | x <- [1..limit], n `mod` x == 0 ]
    where limit = floor $ sqrt $ fromIntegral n

isPrime :: (Integral a) => a -> Bool
isPrime n
    | n <= 1    = False
    | otherwise = (length $ factors n) == 2
