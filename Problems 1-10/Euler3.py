import math

def factors(num):
    sqrt_num = int(math.sqrt(num))
    for x in range(1, sqrt_num + 1):
        if num % x == 0:
            yield x
            if x != sqrt_num:
                yield num / x

def is_prime(num):
    if (num == 1):
        return False
	
    for factor in factors(num):
        if factor != 1 and factor != num:
            return False
	
    return True

def prime_factors(num):
    for factor in factors(num):
        if is_prime(factor):
            yield factor

largest = max(prime_factors(600851475143))
print(largest)
