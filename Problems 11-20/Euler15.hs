-- See Euler15.cpp for an explanation of the solution

main = print $ 40 `choose` 20

choose :: (Integral a) => a -> a -> a
choose n k = round $ foldl f 1.0 [1..k]
    where n' = fromIntegral n
          f = (\a i -> let i' = fromIntegral i in a * (n' + 1 - i') / i')
