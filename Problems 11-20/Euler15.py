# See Euler15.cpp for an explanation of the solution

def factorial(n):
    if n == 1:
        return 1
    else:
        return n * factorial(n - 1)

def choose(n, k):
    return factorial(n) // (factorial(k) * factorial(n - k))

routes = choose(40, 20)
print(routes)
