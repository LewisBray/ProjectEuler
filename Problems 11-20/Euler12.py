import math

def triangle_number(n):
    return int((n / 2) * (n + 1))

def factors(num):
    sqrt_num = int(math.sqrt(num))
    for x in range(1, sqrt_num + 1):
        if num % x == 0:
            yield x
            if x != sqrt_num:
                yield num / x

num = 1
while len(list(factors(triangle_number(num)))) <= 500:
    num += 1

print(triangle_number(num))
