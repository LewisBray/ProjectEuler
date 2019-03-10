#include <iostream>
#include <array>

// Using recursion here as I don't get to use it much and the powers involved
// in this problem (max 7) aren't really going to cause any performance problems.
static constexpr int pow(const int base, const int exponent) noexcept
{
    if (exponent < 1)
        return 1;
    else
        return base * pow(base, exponent - 1);
};

// This function is only really applicable to this application.  We are cheating
// a bit here as we know the maximum number of digits possible when you multiply
// two 3-digit numbers together is 6.
static constexpr bool isPalindrome(const int num) noexcept
{
    // We get to use std::array here as it plays nice with constexpr
    constexpr auto convertToDigits = [](const int num) noexcept {        
        std::array<int, 6> digits{ 0, 0, 0, 0, 0, 0 };
        for (int i = 0; i < digits.size(); ++i)
            digits[i] = num / pow(10, i) - (num / pow(10, i + 1)) * 10;

        return digits;
    };

    const std::array<int, 6> digits = convertToDigits(num);

    // Some digits we are dealing with will have 5 digits and so we need
    // to find the actual number of digits as we can't just assume 6
    constexpr auto numOfDigits = [](const std::array<int, 6>& digits) noexcept {
        for (int i = digits.size() - 1; i >= 0; --i)
            if (digits[i] != 0)
                return i + 1;
        
        return 0;
    };
    
    const int numDigits = numOfDigits(digits);
    
    const int midway = numDigits / 2;
    for (int i = 0; i < midway; ++i)            // Finally check if palindrome
        if (digits[i] != digits[numDigits - 1 - i])
            return false;
    
    return true;
}

// Couldn't really generalise this function, it just finds the answer we want.
static constexpr int findLargestPalindrome() noexcept
{
    int largest = 0;
    for (int i = 100; i < 1000; ++i)
    {
        for (int j = i; j < 1000; ++j)
        {
            const int product = i * j;
            if (product > largest && isPalindrome(product))
                largest = product;
        }
    }
    
    return largest;
}

int main()
{
    constexpr int largest = findLargestPalindrome();
    std::cout << largest << std::endl;

    return 0;
}