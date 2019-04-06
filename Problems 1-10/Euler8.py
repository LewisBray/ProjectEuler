from functools import reduce

def largest_sequential_product(digits, sequence_length):
    largestProduct = 0
    for i in range(0, len(digits) - sequence_length):
        sequence = digits[i : i + sequence_length]
        product = reduce((lambda x, y: x * y), sequence)
        
        if product > largestProduct:
            largestProduct = product

    return largestProduct

with open("Euler8Number.txt", "r") as numberFile:
    number = numberFile.read().replace('\n', '')
    digits = list(map((lambda digit: int(digit)), number))
    
    largest = largest_sequential_product(digits, 13)
    print(largest)
