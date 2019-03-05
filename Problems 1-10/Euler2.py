def fibonacci(limit):
    current, previous = 0, 1
    while current <= limit:
        yield current
        current, previous = current + previous, current

def even_fibonacci(limit):
    for fib in fibonacci(limit):
        if fib % 2 == 0:
            yield fib

total = sum(x for x in even_fibonacci(4000000))
print(total)
