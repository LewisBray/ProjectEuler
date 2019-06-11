main = print $ (sum $ map numOfLetters1To999 [1..999]) + numOfLettersInOneThousand

numOfLetters1To19 :: Int -> Int
numOfLetters1To19 n
    | n == 1    = 3
    | n == 2    = 3
    | n == 3    = 5
    | n == 4    = 4
    | n == 5    = 4
    | n == 6    = 3
    | n == 7    = 5
    | n == 8    = 5
    | n == 9    = 4
    | n == 10   = 3
    | n == 11   = 6
    | n == 12   = 6
    | n == 13   = 8
    | n == 14   = 8
    | n == 15   = 7
    | n == 16   = 7
    | n == 17   = 9
    | n == 18   = 8
    | n == 19   = 8
    | otherwise = error "Invalid argument passed to numOfLetters1To19"

numOfLettersFromSecondDigit :: Int -> Int
numOfLettersFromSecondDigit n
    | n' == 1   = 3 -- Only valid when n' == 10
    | n' == 2   = 6
    | n' == 3   = 6
    | n' == 4   = 5
    | n' == 5   = 5
    | n' == 6   = 5
    | n' == 7   = 7
    | n' == 8   = 6
    | n' == 9   = 6
    | otherwise = error "Invalid argument passed to numOfLettersFromSecondDigit"
    where n' = div n 10

numOfLettersFromThirdDigit :: Int -> Int
numOfLettersFromThirdDigit n = numOfLetters1To19 (div n 100) + numOfLettersInHundred;

numOfLetters1To99 :: Int -> Int
numOfLetters1To99 n
    | n `mod` 10 == 0    = numOfLettersFromSecondDigit n
    | n >= 20 && n < 100 = (numOfLettersFromSecondDigit n) +
                           (numOfLetters1To19 (n `mod` 10))
    | otherwise          = numOfLetters1To19 n

numOfLettersInHundred :: Int
numOfLettersInHundred = 7

numOfLettersInAnd :: Int
numOfLettersInAnd = 3

numOfLetters1To999 :: Int -> Int
numOfLetters1To999 n =
    if (n >= 100)
        then if (n `mod` 100 /= 0)
                 then numOfLettersFromThirdDigit n +
                      numOfLettersInAnd + numOfLetters1To99 (n `mod` 100)
                 else numOfLettersFromThirdDigit n
        else numOfLetters1To99 n

numOfLettersInOneThousand :: Int
numOfLettersInOneThousand = 11
