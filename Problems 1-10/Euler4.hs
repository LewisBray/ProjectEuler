main = print $ maximum $ filter (isPalindrome . show) numbers
    where numbers = [ x * y | x <- [100..999], y <- [100..999] ]

isPalindrome :: String -> Bool
isPalindrome s = s == reverse s
