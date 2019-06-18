import Data.Char (digitToInt)

main = print $ sum $ map digitToInt $ show $ factorial 100

factorial :: (Integral a) => a -> a
factorial n = product [1..n]
