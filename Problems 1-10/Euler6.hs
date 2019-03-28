main = print $ squareOfSum [1..100] - sumOfSquares [1..100]
    where squareOfSum = (^2) . sum
          sumOfSquares = sum . map (^2)
