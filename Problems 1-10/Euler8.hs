import Data.Char (digitToInt)

main = do
    digits <- fmap (map digitToInt . filter (/='\n')) $ readFile "Euler8Number.txt"
    print $ maximum $ sequentialProducts digits 13

sequentialProducts :: (Num a) => [a] -> Int -> [a]
sequentialProducts list sequenceLength
    | length list < sequenceLength = []
    | otherwise = product subsequence : sequentialProducts (tail list) sequenceLength
    where subsequence = take sequenceLength list
