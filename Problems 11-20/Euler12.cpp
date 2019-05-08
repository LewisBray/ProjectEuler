// Managed to compile this with clang 6.0.0 with C++17 and compiler
// flag -fconstexpr-steps=100000000, could probably require less
// steps but I didn't work out a more accurate limit.

#include <iostream>

static constexpr int bitsNeededToRepresent(const int num) noexcept
{
    for (int i = 31; i >= 0; --i)
        if ((0x1 << i) & num)
            return i + 1;
    
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

static constexpr int numberOfDivisors(const int num) noexcept
{
    int numberOfDivisors = 2;           // 1 and num both divide num
    
    const int root = floorOfSqrt(num);
    if (num % root == 0)                // We don't check root in loop
        ++numberOfDivisors;

    for (int i = 2; i < root; ++i)
        if (num % i == 0)
            numberOfDivisors += 2;

    return numberOfDivisors;
}

static constexpr int triangleNumber(const int n) noexcept
{
    return (n * (n + 1)) / 2;
}

static constexpr int highlyDivisibleTriangleNumber() noexcept
{
    for (int i = 1; ; ++i)
        if (numberOfDivisors(triangleNumber(i)) > 500)
            return triangleNumber(i);
    
    return 0;
}

int main()
{
    constexpr int answer = highlyDivisibleTriangleNumber();
    std::cout << answer << std::endl;
    
    return 0;
}
