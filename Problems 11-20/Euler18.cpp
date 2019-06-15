#include <iostream>
#include <utility>
#include <array>

static constexpr int bitsNeededToRepresent(const int num) noexcept
{
    for (int i = 31; i >= 0; --i)
        if ((0x1 << i) & num)
            return i + 1;
    
    return 0;
}

// Check Euler3.cpp for an explanation of this function
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

// Each number in the triangle is represented by a node which holds some additional info
struct Node
{
    constexpr Node(const int val = 0) noexcept
        : value{ val }
        , maxValueTotal{ val }
    {}

    using Coordinates = std::pair<std::size_t, std::size_t>;
    static constexpr Coordinates NullCoordinates = { 0xFFFFFFFFu, 0xFFFFFFFFu };
    
    int value = 0;
    int maxValueTotal = 0;

    // Coordinates of nodes below this one
    Coordinates left = NullCoordinates;
    Coordinates right = NullCoordinates;
};

template <std::size_t Size> static constexpr int
findMaxPathSum(const std::array<int, Size>& numbers) noexcept
{
    constexpr auto triangleNumber = [](const int n) noexcept {
        return (n * n + n) / 2;
    };

    constexpr auto triangleNumberInverse = [](const int n) noexcept {
        return (floorOfSqrt(8 * n + 1) - 1) / 2;
    };

    constexpr int Rows = triangleNumberInverse(Size);

    std::array<std::array<Node, Rows>, Rows> triangle;
    for (std::size_t row = 0, x = 1; row < Rows; ++x, ++row)
    {
        const int offsetIntoNumbers = triangleNumber(x) - x;
        for (std::size_t col = 0; col < x; ++col)
        {
            Node& node = triangle[row][col];

            const int value = numbers[offsetIntoNumbers + col];
            node.value = value;
            node.maxValueTotal = value;

            if (row != row - 1) // Connect this node to nodes beneath it
            {
                node.left.first = row + 1;
                node.left.second = col;
                node.right.first = row + 1;
                node.right.second = col + 1;
            }
        }
    }

    const auto findMaxPathNode = [&triangle](const Node& node) {
        const Node& leftSubNode = triangle[node.left.first][node.left.second];
        const Node& rightSubNode = triangle[node.right.first][node.right.second];

        if (leftSubNode.maxValueTotal > rightSubNode.maxValueTotal)
            return leftSubNode;
        else
            return rightSubNode;
    };

    for (int row = Rows - 2; row >= 0; --row)
    {
        for (int col = 0; col <= row; ++col)
        {
            Node& node = triangle[row][col];
            const Node maxValuePathNode = findMaxPathNode(node);
            node.maxValueTotal = node.value + maxValuePathNode.maxValueTotal;
        }
    }

    return triangle[0][0].maxValueTotal;
}

int main()
{
    static constexpr std::array numbers = {
        75,
        95, 64,
        17, 47, 82,
        18, 35, 87, 10,
        20, 04, 82, 47, 65,
        19, 01, 23, 75, 03, 34,
        88, 02, 77, 73, 07, 63, 67,
        99, 65, 04, 28, 06, 16, 70, 92,
        41, 41, 26, 56, 83, 40, 80, 70, 33,
        41, 48, 72, 33, 47, 32, 37, 16, 94, 29,
        53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14,
        70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57,
        91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48,
        63, 66, 04, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31,
        04, 62, 98, 27, 23,  9, 70, 98, 73, 93, 38, 53, 60, 04, 23
    };

    constexpr int maxPathSum = findMaxPathSum(numbers);

    std::cout << maxPathSum << std::endl;

    return 0;
}
