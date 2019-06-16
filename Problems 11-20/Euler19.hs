main = print $ length $ filter (== 1) $ map correspondingWeekday dates
    where dates = [ Date 1 month year | month <- [3..14], year <- [1901..2000] ]

data Date = Date Int Int Int

correspondingWeekday :: Date -> Int
correspondingWeekday (Date day month year) =
    (day + (div (13 * (month + 1)) 5) + yearOfCentury +
    (div yearOfCentury 4) + (div century 4) + 5 * century) `mod` 7
    where yearOfCentury = year `mod` 100
          century = div year 100
