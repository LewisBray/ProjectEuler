import math

# Cast in return statement is fine as result is always a whole number
def lcm(x, y):
    return int(x * y / math.gcd(x, y))

# The lowest common multiple of a set of values is given by
# lcm(value, lcm(rest_of_values)) which we define recursively
def lcmOfRange(rangeStart):
    if rangeStart <= 2:
        return lcm(2, 1)
    else:
        return lcm(rangeStart, lcmOfRange(rangeStart - 1))

smallest = lcmOfRange(20)
print(smallest)
