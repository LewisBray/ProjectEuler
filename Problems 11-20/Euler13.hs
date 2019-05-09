main = do
    let stringToInt = read :: String -> Integer
    numbers <- fmap (map stringToInt . lines) $ readFile "Euler13Numbers.txt"
    print $ take 10 $ show $ sum $ numbers
