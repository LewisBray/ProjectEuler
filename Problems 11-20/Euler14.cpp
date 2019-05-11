// Compiled this using clang 6.0.0 with C++17 and
// compiler flag -fconstexpr-steps=60000000.

#include <iostream>
#include <array>

static constexpr unsigned nextCollatz(const unsigned term) noexcept
{
    if (term % 2 == 0)
        return term / 2;
    else
        return 3 * term + 1;
}

static constexpr int numberWithLongestCollatzSequence() noexcept
{
    // Set up array to keep track of calculated sequence lengths
    constexpr int UpTo = 1'000'000;
    std::array<int, UpTo - 1> sequenceLengths{};
    sequenceLengths[0] = 1;     // Setting lengths for 1 and 2...
    sequenceLengths[1] = 2;     // ...keeps loop logic simpler

    int longestSequence = 2, numCachedLengths = 2;
    for (int i = 3; i < UpTo; ++i)
    {
        int sequenceLength = 0;
        for (unsigned term = i; term != 1; term = nextCollatz(term))
        {
            if (term <= numCachedLengths)   // I.e. sequence length is cached
            {
                sequenceLength += sequenceLengths[term - 1];
                break;
            }
            else
                ++sequenceLength;
        }

        sequenceLengths[i - 1] = sequenceLength;
        ++numCachedLengths;

        if (sequenceLengths[i - 1] > sequenceLengths[longestSequence - 1])
            longestSequence = i;
    }

    return longestSequence;
}

int main()
{
    constexpr int longest = numberWithLongestCollatzSequence();
    std::cout << longest << std::endl;

    return 0;
}
