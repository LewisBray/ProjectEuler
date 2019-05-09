def load_numbers(filename):
    with open(filename, "r") as numbers_file:
        numbers = list()
        for line in numbers_file:
            numbers.append(int(line))
    
    return numbers

numbers = load_numbers("Euler13Numbers.txt")
answer = str(sum(numbers))[0:10]
print(answer)