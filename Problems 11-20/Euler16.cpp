#include <iostream>
#include <array>

// Helper struct to hold result from exponentiation.  We won't know in advance
// how many digits we could have and can't use std::vector as it allocates 
template <int MaxDigits>
struct LargeNumber
{
    std::array<int, MaxDigits> digits;
    int numDigits = 0;
};

// If we are only exponentiating numbers between 1 and 10 (which seems
// reasonable as you can always change the exponent to match) we know that the
// answer can't have more than 'Exponent' digits since 10^Exponent will have
// 'Exponent + 1' many digits and we will be strictly less than that.  This
// function has to be a template as we use the parameters passed in to determine
// the length of the array of digits returned so the exponenet must be know at
// compile time, we also make the base a template parameter so we can statically
// assert it's in the range [1, 10) (also it reads better...).
template <int Base, int Exponent>
static constexpr LargeNumber<Exponent> exponentiate() noexcept
{
    static_assert(Base > 0 && Base < 10, "Must exponentiate a base between 1 and 9");

    std::array<int, Exponent> digits{ Base };
    int numDigits = 1;
    
    for (int i = 1; i < Exponent; ++i)
    {
        int carry = 0;
        for (int j = 0; j < numDigits; ++j)
        {
            int& digit = digits[j];

            const int product = digit * Base + carry;

            digit = product % 10;
            carry = product / 10;

            if (j == numDigits - 1 && carry != 0)
            {
                digits[j + 1] = carry;
                ++numDigits;
                break;
            }
        }
    }

    return { digits, numDigits };
}

template <int MaxDigits>
static constexpr int sum(const LargeNumber<MaxDigits>& largeNumber) noexcept
{
    int total = 0;
    for (int i = 0; i < largeNumber.numDigits; ++i)
        total += largeNumber.digits[i];
    
    return total;
}

int main()
{
    constexpr int sumOfDigits = sum(exponentiate<2, 1000>());
    std::cout << sumOfDigits << std::endl;

    return 0;
}
