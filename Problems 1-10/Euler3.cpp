// This requires some explaining.  I managed to get this compiling with
// x86-x64 gcc 8.3 with the compiler flags -fconstexpr-loop-limit=775200
// (set the number of loops allowed in a constexpr function to 775200)
// and -std=C++1z (for C++17, for lambda inside constexpr function).
// You can quickly test this by copying this code into compiler explorer
// (godbolt.org), picking gcc 8.3 and setting the stated compiler flag.

#include <iostream>

static constexpr int bitsNeededToRepresent(const int num) noexcept
{
    for (int i = 31; i >= 0; --i)   // Start at highest bit and work down
        if ((0x1 << i) & num)       // First bit set is the highest...
            return i + 1;           // ...needed to represent num
    
    return 0;
}

// floorOfSqrt requires knowing the number of bits required to represent
// a number.  Since the main number we're interested in is too big to
// fit into an int we need to know how many bits in a 64-bit int are
// needed to represent it.  However, we get compiler warnings if we try
// to bit-shift more than 32 bits and so this overload exists to check
// the top and 32-bit parts of a 64-bit int.
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

// In order to reduce the number of iterations in isPrime and
// largestPrimeFactor, we would need to know the square root of the
// numbers we're testing.  Unfortunately, std::sqrt isn't constexpr
// (as of C++17) for whatever reason and so we need our own square
// root function.  This algorithm is guaranteed to quickly converge
// (log time) to the floor of the square root which is perfect for
// our situation.
static constexpr int64_t floorOfSqrt(const int64_t num) noexcept
{
    // Need our own ceil function as std::ceil is not constexpr
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

// In our case, floorOfSqrt(600851475143) = 775146 so we know we are
// looping this many times.  This is the origin of the compiler flag
// that sets the number of loops allowed in a constexpr function to
// 775200, to give us enough room to calculate our situation.  I'm
// sure other compilers could do this too but I haven't checked.
static constexpr int64_t largestPrimeFactor(const int64_t num) noexcept
{
    int64_t largest = 1;
    const int64_t sqrtNum = floorOfSqrt(num);
    for (int64_t i = 2; i <= sqrtNum; ++i)
    {
        if (num % i != 0)
            continue;
        
        if (i > largest && isPrime(i))  // Check if i is larger first...
            largest = i;                // ...as much cheaper operation
        
        const int j = num / i;          // Since we are only going up...
        if (j > largest && isPrime(j))  // ...to sqrt, need to check...
            largest = j;                // ...divisors greater than sqrt       
    }
    
    return largest;
}

int main()
{
    constexpr int64_t largest = largestPrimeFactor(600851475143);
    std::cout << largest << std::endl;

    return 0;
}
