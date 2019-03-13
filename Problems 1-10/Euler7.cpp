#include <iostream>

static constexpr int bitsNeededToRepresent(const int num) noexcept
{
    for (int i = 31; i >= 0; --i)
        if ((0x1 << i) & num)
            return i + 1;

    return 0;
}

static constexpr int bitsNeededToRepresent(const int64_t num) noexcept
{
    const int numBitsNeededForTop32bits =
        bitsNeededToRepresent(static_cast<int>(num >> 32));

    const bool top32bitsUsed = (numBitsNeededForTop32bits != 0);
    if (top32bitsUsed)
        return numBitsNeededForTop32bits + 32;
    else
        return bitsNeededToRepresent(static_cast<int>(num));
}

static constexpr int64_t floorOfSqrt(const int64_t num) noexcept
{
    constexpr auto ceil = [](const double num) noexcept {
        const int floor = static_cast<int>(num);
        return (floor == num) ? floor : floor + 1;
    };

    int x = (1 << ceil(bitsNeededToRepresent(num) / 2.0));
    while (true)
    {
        const int64_t y = (x + num / x) / 2;
        if (y >= x)
            return x;
        else
            x = y;
    }
}

// For an explanation of this function and the helper functions
// that make it up, check out the C++ solution to problem 3
static constexpr bool isPrime(const int64_t num) noexcept
{
    if (num == 1)
        return false;

    const int64_t sqrtNum = floorOfSqrt(num);
    for (int64_t i = 2; i <= sqrtNum; ++i)
        if (num % i == 0)
            return false;

    return true;
}

static constexpr int64_t nthPrime(const int n) noexcept
{
    int primeCount = 0;
    int64_t number = 1;
    while (primeCount < n)
    {
        ++number;
        if (isPrime(number))
            ++primeCount;
    }

    return number;
}

int main()
{
    constexpr int64_t prime10001 = nthPrime(10001);
    std::cout << prime10001 << std::endl;

    return 0;
}
