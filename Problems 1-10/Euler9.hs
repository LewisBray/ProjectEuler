main = print $ (\(a, b, c) -> a * b * c) $ head triplets
    where triplets = filter (\(a, b, c) -> a + b + c == 1000) (rightTriangles 1000)

triangles :: (Integral a) => a -> [(a, a, a)]
triangles n = [ (a, b, c) | a <- [1..n], b <- [(a + 1)..n], c <- [(b + 1)..n] ]

rightTriangles :: (Integral a) => a -> [(a, a, a)]
rightTriangles = filter (\(a, b, c) -> a^2 + b^2 == c^2) . triangles
