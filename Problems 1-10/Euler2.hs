main = print $ sum $ takeWhile (< 4000000) (filter even fibonaccis)
    where fibonaccis = 0 : 1 : zipWith (+) fibonaccis (tail fibonaccis)
