#include <iostream>

static constexpr int addMultiplesOf3And5(const int upTo) noexcept
{
    int total = 0;
    for (int i = 0; i < upTo; ++i)
        if (i % 3 == 0 || i % 5 == 0)
            total += i;
    
    return total;
};

int main()
{
    constexpr int total = addMultiplesOf3And5(1000);
    std::cout << total << std::endl;

    return 0;
}
