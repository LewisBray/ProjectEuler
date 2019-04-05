import math

def factors(num):
    sqrt_num = int(math.sqrt(num))
    for x in range(1, sqrt_num + 1):
        if num % x == 0:
            yield x
            if x != sqrt_num:
                yield num / x

def is_prime(num):
    if num == 1:
        return False
	
    for factor in factors(num):
        if factor != 1 and factor != num:
            return False
	
    return True

def sum_of_primes(up_to):
    total, number = 0, 1
    while number < up_to:
        if is_prime(number):
            total += number
        number += 1

    return total

total = sum_of_primes(2000000)
print(total)
