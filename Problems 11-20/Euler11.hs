import Data.List (transpose, tails)

main = do
    numbers <- fmap toNumberGrid $ readFile "Euler11Numbers.txt"
    let combinators = [subRows, subColumns, rightDiagonals, leftDiagonals]
        allCombinations = concatMap ($ numbers) combinators
    print $ maximum $ map product $ allCombinations

toNumberGrid :: String -> [[Integer]]
toNumberGrid = map (map read . words) . lines

subRowsGenerator :: Int -> [Integer] -> [[Integer]]
subRowsGenerator size row
    | length row < size = []
    | otherwise         = (take size row):(subRowsGenerator size $ tail row)

subRows :: [[Integer]] -> [[Integer]]
subRows = concatMap (subRowsGenerator 4)

subColumns :: [[Integer]] -> [[Integer]]
subColumns = subRows . transpose

rightDiagonals :: [[Integer]] -> [[Integer]]
rightDiagonals = concatMap (subColumns . zipWith drop [0..]) . tails

leftDiagonals :: [[Integer]] -> [[Integer]]
leftDiagonals = rightDiagonals . map reverse
