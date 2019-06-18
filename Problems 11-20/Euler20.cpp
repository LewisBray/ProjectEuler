#include <algorithm>
#include <iostream>
#include <array>

// struct for representing integers beyond the range of 32-/64-bit ints
template <std::size_t MaxDigits>
struct LargeInteger
{
    int numOfDigits = 0;
    std::array<int, MaxDigits> digits = std::array<int, MaxDigits>{};
};

template <std::size_t MaxDigits>
static constexpr bool operator<(
    const LargeInteger<MaxDigits>& lhs, const LargeInteger<MaxDigits>& rhs) noexcept
{
    return lhs.numOfDigits < rhs.numOfDigits;
}

static constexpr int exponentiate(const int base, const int power) noexcept
{
    if (power <= 0)
        return 1;
    else
        return base * exponentiate(base, power - 1);
}

static constexpr int numberOfDigits(const int n) noexcept
{
    for (int power = 9; power >= 0; --power)
        if (n / exponentiate(10, power) != 0)
            return power + 1;

    return 1;
}

template <std::size_t MaxDigits>
static constexpr std::array<int, MaxDigits> convertToDigits(
    const int n, const int numOfDigits) noexcept
{
    auto digits = std::array<int, MaxDigits>{};
    for (int i = 0; i < numOfDigits; ++i)
        digits[i] = (n / exponentiate(10, i)) % 10;

    return digits;
}

template <std::size_t MaxDigits>
static constexpr LargeInteger<MaxDigits> toLargeInteger(const int n) noexcept
{
    const int numOfDigits = numberOfDigits(n);
    return { numOfDigits, convertToDigits<MaxDigits>(n, numOfDigits) };
}

template <std::size_t MaxDigits>
static constexpr LargeInteger<MaxDigits> operator+(
    const LargeInteger<MaxDigits>& lhs, const LargeInteger<MaxDigits>& rhs) noexcept
{
    const auto& [smallest, largest] = std::minmax(lhs, rhs);

    int carry = 0;
    LargeInteger<MaxDigits> sum{ largest.numOfDigits, {} };
    for (int i = 0; i < largest.numOfDigits; ++i)
    {
        const int temp = (i < smallest.numOfDigits) ?
            smallest.digits[i] + largest.digits[i] + carry :
            largest.digits[i] + carry;

        const int digit = temp % 10;
        carry = temp / 10;

        sum.digits[i] = digit;
    }

    if (carry != 0)
        sum.digits[sum.numOfDigits++] = carry;

    return sum;
}

// This operator overload is a bit of a cheat as it is only implemented for when
// scalar is a 1 or 2 digit number.  The product is calculated using the
// standard 'pen and paper' method people emply to do this by hand.
template <std::size_t MaxDigits>
static constexpr LargeInteger<MaxDigits> operator*(
    const LargeInteger<MaxDigits>& lhs, const int scalar) noexcept
{
    const LargeInteger<2> rhs = toLargeInteger<2>(scalar);
    std::array<LargeInteger<MaxDigits>, 2> summands = {
        LargeInteger<MaxDigits>{ lhs.numOfDigits, {} },
        LargeInteger<MaxDigits>{ lhs.numOfDigits + 1, {} }
    };

    for (int i = 0; i < rhs.numOfDigits; ++i)
    {
        int carry = 0;
        for (int j = 0; j < lhs.numOfDigits; ++j)
        {
            const int temp = lhs.digits[j] * rhs.digits[i] + carry;
            const int digit = temp % 10;
            carry = temp / 10;

            if (i == 1)
                summands[i].digits[j + 1] = digit;
            else
                summands[i].digits[j] = digit;
        }

        if (carry != 0)
            summands[i].digits[summands[i].numOfDigits++] = carry;
    }

    if (rhs.numOfDigits == 1)
        return summands[0];
    else
        return summands[0] + summands[1];
}

template <std::size_t MaxDigits>
static constexpr LargeInteger<MaxDigits> factorial(const int n) noexcept
{
    LargeInteger<MaxDigits> result{ 3, { 0, 0, 1 } };
    for (int i = n - 1; i > 1; --i)
        result = result * i;

    return result;
}

template <std::size_t MaxDigits>
static constexpr int sum(const LargeInteger<MaxDigits>& largeInteger) noexcept
{
    int total = 0;
    for (int i = 0; i < largeInteger.numOfDigits; ++i)
        total += largeInteger.digits[i];

    return total;
}

// The number of digits to represent a number n is going to be given by
// floor(log10(n)) + 1.  Since we are dealing with a factorial,
//      log10(n!) = log10(1) + ... + log10(n)
//                < floor(log10(1)) + 1 + ... + floor(log10(n)) + 1
//                = numOfDigits(1) + ... + numOfDigits(n)
// and so we can add up the sum of the all of the numbers up to and including
// no to get an upper bound on the number of digits that we need.
static constexpr std::size_t digitsToRepresentFactorialOf(const int n) noexcept
{
    std::size_t total = 0;
    for (int i = 1; i <= n; ++i)
        total += static_cast<std::size_t>(numberOfDigits(i));
    
    return total + 1;
}

int main()
{
    constexpr std::size_t MaxDigits = digitsToRepresentFactorialOf(100);
    constexpr int sumOfDigits = sum(factorial<MaxDigits>(100));
    std::cout << sumOfDigits << std::endl;

    return 0;
}
