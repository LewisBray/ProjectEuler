import math

def factors(num):
    sqrt_num = int(math.sqrt(num))
    for n in range(1, sqrt_num + 1):
        if num % n == 0:
            yield n
            if n != sqrt_num:
                yield num / n

def is_prime(num):
    if num == 1:
        return False

    for factor in factors(num):
        if factor != 1 and factor != num:
            return False

    return True

def nth_prime(n):
    number, prime_count = 1, 0
    while prime_count < n:
        number += 1
        if is_prime(number):
            prime_count += 1

    return number

prime_10001 = nth_prime(10001)
print(prime_10001)
