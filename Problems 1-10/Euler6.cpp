#include <iostream>

// Recursion fine for the small powers we are dealing with.
static constexpr int pow(const int base, const int exponent) noexcept
{
    if (exponent < 1)
        return 1;
    else
        return base * pow(base, exponent - 1);
}

// Using the formulae for the sum of the natural numbers n(n + 1)/2 and
// for the sum of the squares n(2n + 1)(n + 1)/6, with a little algebra
// we can derive the formula for the square of the sum minus the sum of
// the squares to be n^4/4 + n^3/2 - n^2/4 - n/6 which prevents us from
// performing any looping.
static constexpr int squareOfSumMinusSumOfSquares(const int n) noexcept
{
    const double first = pow(n, 4) / 4.0;
    const double second = pow(n, 3) / 6.0;
    const double third = pow(n, 2) / 4.0;
    const double fourth = n / 6.0;

    return first + second - third - fourth;
}

int main()
{
    constexpr int answer = squareOfSumMinusSumOfSquares(100);
    std::cout << answer << std::endl;

    return 0;
}
