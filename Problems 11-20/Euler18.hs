main = do
    triangle <- fmap inputToTriangle $ readFile "Euler18Numbers.txt"
    print $ head $ foldr1 maxPathValueFinder triangle

inputToTriangle :: String -> [[Int]]
inputToTriangle = map (map stringToInt . words) . lines
    where stringToInt = read :: String -> Int

maxPathValue :: Int -> Int -> Int -> Int
maxPathValue x y z = x + max y z

maxPathValueFinder :: [Int] -> [Int] -> [Int]
maxPathValueFinder row nextRow = zipWith3 maxPathValue row nextRow (tail nextRow)
