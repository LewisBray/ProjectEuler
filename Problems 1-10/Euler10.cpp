// This takes a stupid number of steps to compute, got it compiling using clang
// and -fconstexpr-steps=1000000000.  An optimisation would be to not add any
// even numbers after 2 in 'twoToLimit' in 'sumPrimes' as no even number is
// going to be prime after 2.  For an explanation of the implementation of
// 'isPrime', look at Euler3.cpp.

#include <iostream>
#include <cstdint>
#include <array>

static constexpr int bitsNeededToRepresent(const int num) noexcept
{
    for (int i = 31; i >= 0; --i)   // Start at highest bit and work down
        if ((0x1 << i) & num)       // First bit set is the highest...
            return i + 1;           // ...needed to represent num
    
    return 0;
}

static constexpr int floorOfSqrt(const int num) noexcept
{
    constexpr auto ceil = [](const double num) noexcept {
        const int floor = static_cast<int>(num);
        return (floor == num) ? floor : floor + 1;
    };

    int x = (1 << ceil(bitsNeededToRepresent(num) / 2.0));
    while (true)
    {
        const int y = (x + num / x) / 2;
        if (y >= x)
            return x;
        else
            x = y;
    }
}

static constexpr bool isPrime(const int num) noexcept
{
    if (num == 1)
        return false;
    
    const int sqrtNum = floorOfSqrt(num);
    for (int i = 2; i <= sqrtNum; ++i)
        if (num % i == 0)
            return false;
    
    return true;
}

// This is an implementation of the Sieve of Eratosthenes, since we can't deal
// with std::vectors due to memory allocation not being available in compile
// time compilations we simply mark numbers as '-1' if they have been sieved
// out.  this is a function template as size of array used in implementation
// needs to be known at compile time.
template <int UpTo>
static constexpr std::uint64_t sumPrimes() noexcept
{
    constexpr int NumsToCheck = UpTo - 2;

    std::array<int, NumsToCheck> twoToLimit{};
    for (int i = 2; i < UpTo; ++i)
        twoToLimit[i - 2] = i;
    
    std::uint64_t sum = 0;
    for (int i = 0; i < NumsToCheck; ++i)
    {
        const int number = twoToLimit[i];
        if (number == -1 || !isPrime(number))
            continue;
        
        sum += number;

        for (int j = i + number; j < NumsToCheck; j += number)
            twoToLimit[j] = -1;
    }
    
    return sum;
}

int main()
{
    constexpr std::uint64_t total = sumPrimes<2000000>();
    std::cout << total << std::endl;

    return 0;
}
