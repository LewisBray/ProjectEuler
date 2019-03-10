#include <iostream>

static constexpr int sumEvenFibonacci(const int notExceeding) noexcept
{
    int total = 0;
    int current = 1, previous = 0;
    while (current <= notExceeding)
    {
        if (current % 2 == 0)
            total += current;

        const int temp = current;
        current += previous;
        previous = temp;
    }

    return total;
}

int main()
{
    constexpr int total = sumEvenFibonacci(4000000);
    std::cout << total << std::endl;

    return 0;
}
