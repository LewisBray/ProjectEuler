// We solve this problem via combinatorics, there are probably other ways (that
// Project Euler expected you to use) however I'm going to abuse my maths
// background.  Let R and D represent moving right and down respectively.  Then
// in an n x n grid, #(R) + #(D) = 2n and #(R) = #(R) <=> #(R) = #(D) = n, where
// #(x) is the number of moves in direction x.  If we simply find how many ways
// to distribute the R movements in a 2n-length array, then the D directions
// fill out the remainder of the places in the array, thus the number of
// different paths is the number of ways to choose n placements of R from 2n
// many places.

#include <iostream>
#include <numeric>
#include <cstdint>

// Create a simple struct for use in the choose function implementation
struct Fraction
{
    std::uint64_t numerator = 1;
    std::uint64_t denominator = 1;
};

// To avoid arithmetic overflow in the choose function implementation, we write
// this operator overload for our function struct.  When multiplying two
// Fractions together we simply check for any common multiples between the
// numerators and denominators in each fraction before multiplication.  This
// keeps the numbers as small as possible before multiplication.
static constexpr Fraction& operator*=(Fraction& lhs, Fraction&& rhs) noexcept
{
    const std::uint64_t gcd1 = std::gcd(lhs.numerator, rhs.denominator);
    lhs.numerator /= gcd1;
    rhs.denominator /= gcd1;

    const std::uint64_t gcd2 = std::gcd(lhs.denominator, rhs.numerator);
    lhs.denominator /= gcd2;
    rhs.numerator /= gcd2;

    lhs.numerator *= rhs.numerator;
    lhs.denominator *= rhs.denominator;

    return lhs;
}

// Function implementation uses the summation formula from 1 to k where each
// term is given by (n + 1 - i) / i.  The helper function above helps prevent
// any arithmetic overflow we could encounter with larger numbers.
static constexpr std::uint64_t choose(const unsigned n, const unsigned k) noexcept
{
    Fraction result;
    for (unsigned i = 1; i <= k; ++i)
        result *= Fraction{ n + 1 - i, i };
    
    return result.numerator / result.denominator;
}

int main()
{
    constexpr std::uint64_t routes = choose(40, 20);
    std::cout << routes << std::endl;

    return 0;
}
