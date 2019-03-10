#include <iostream>
#include <numeric>

// The simple way of doing this required too many loops and I couldn't get the
// permissable number of loops by the compiler to go up high enough (at least
// on gcc).  We can take advantage of the fact that the lowest common multiple
// of a set of values is given by lcm(value, lcm(rest_of_values)) which lends
// itself to recursion very nicely.  Also, the heavy lifting can be done by
// std::lcm which was introduced in C++17 and is constexpr (which is perfect).
static constexpr int lcmOfRange(const int rangeStart) noexcept
{
    // Indulging in recursion again...
    if (rangeStart <= 2)
        return std::lcm(2, 1);
    else
        return std::lcm(rangeStart, lcmOfRange(rangeStart - 1));
}

int main()
{
    constexpr int smallest = lcmOfRange(20);
    std::cout << smallest << std::endl;

    return 0;
}
