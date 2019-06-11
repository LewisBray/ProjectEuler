#include <iostream>
#include <array>

constexpr int numOfLetters1To19(const int n) noexcept
{
    switch (n)
    {
        case 1:  return 3;
        case 2:  return 3;
        case 3:  return 5;
        case 4:  return 4;
        case 5:  return 4;
        case 6:  return 3;
        case 7:  return 5;
        case 8:  return 5;
        case 9:  return 4;
        case 10: return 3;
        case 11: return 6;
        case 12: return 6;
        case 13: return 8;
        case 14: return 8;
        case 15: return 7;
        case 16: return 7;
        case 17: return 9;
        case 18: return 8;
        case 19: return 8;
        default: return 0;
    }
}

static constexpr int numOfLetters1To99(const int n) noexcept
{
    constexpr auto numLettersFromSecondDigit = [](const int num)
    {
        switch (num / 10)
        {
            case 1:  return 3;  // Only valid when num == 10
            case 2:  return 6;
            case 3:  return 6;
            case 4:  return 5;
            case 5:  return 5;
            case 6:  return 5;
            case 7:  return 7;
            case 8:  return 6;
            case 9:  return 6;
            default: return 0;
        }
    };

    if (n % 10 == 0)
        return numLettersFromSecondDigit(n);
    else if (n >= 20 && n < 100)
        return numLettersFromSecondDigit(n) + numOfLetters1To19(n % 10);
    else
        return numOfLetters1To19(n);
}

static constexpr int numOfLetters1To999(const int n) noexcept
{
    if (n < 0 || n >= 1000)
        return 0;
    
    if (n >= 100)
    {
        constexpr int numOfLettersInHundred = 7;
        const int lettersFromThirdDigit =
            numOfLetters1To19(n / 100) + numOfLettersInHundred;
        
        if (n % 100 != 0)
            return lettersFromThirdDigit + 3 + numOfLetters1To99(n % 100);
        else
            return lettersFromThirdDigit;
    }
    else
        return numOfLetters1To99(n);
}

static constexpr int sumNumOfLetters(const int from, const int to) noexcept
{
    int sum = 0;
    for (int i = from; i <= to; ++i)
        sum += numOfLetters1To999(i);
    
    return sum;
}

int main()
{
    constexpr int numLettersInOneThousand = 3 + 8;
    const int total = sumNumOfLetters(1, 999) + numLettersInOneThousand;
    std::cout << total << std::endl;

    return 0;
}