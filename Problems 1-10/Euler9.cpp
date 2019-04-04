#include <iostream>

// Doing this with a triple loop easily breaks the constexpr loop limit for
// compilers and so we generate the pythagorean triplets a different way.
// If for a triplet (a, b, c) we define m < n <= 2 such that a = n^2 - m^2,
// b = 2nm and c = n^2 + m^2 we find that a^2 + b^2 = c^2 holds and so we
// can generate Pythagorean triplets with 2 variables rather than 3.  We
// can go further since we know that we only care about triplets such that
// a + b + c <= 1000 <=> n^2 + nm <= 500 => n^2 + m^2 < 500 => n^2 < 500
// => n < 22 which is far below the constexpr limit loop for compilers.
// We could go further and limit m to [1, sqrt(n^2 - 1)] however this would
// involve putting in a constexpr sqrt function integers since the one in
// cmath is not constexpr and this is already optimised enough.
constexpr int findSolution() noexcept
{
    for (int n = 2; n < 22; ++n)
        for (int m = 1; m < n; ++m)
        {
            const int a = n * n - m * m;
            const int b = 2 * m * n;
            const int c = n * n + m * m;

            if (a + b + c == 1000)
                return a * b * c;
        }
    
    return 0;
}

int main()
{
    constexpr int product = findSolution();
    std::cout << product << std::endl;

    return 0;
}