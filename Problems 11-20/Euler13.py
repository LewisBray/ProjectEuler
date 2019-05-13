def load_numbers(filename):
    with open(filename, "r") as numbers_file:
        return [int(line) for line in numbers_file]

numbers = load_numbers("Euler13Numbers.txt")
answer = str(sum(numbers))[0:10]
print(answer)
