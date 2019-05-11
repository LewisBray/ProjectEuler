main = print $ snd $ maximum [ (length $ collatzSequence x, x) | x <- [1..999999] ]

collatzSequence :: (Integral a) => a -> [a]
collatzSequence n
    | n == 1    = [1]
    | even n    = n : collatzSequence (div n 2)
    | otherwise = n : collatzSequence (3 * n + 1)
