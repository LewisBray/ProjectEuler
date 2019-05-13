def load_numbers_grid(filename):
    with open(filename, "r") as num_file:
        return [list(map(lambda c: int(c), line.split())) for line in num_file]

def column_product(row, col, numbers):
    product = 1
    for i in range(0, 4):
        product *= numbers[row + i][col]
    
    return product

def row_product(row, col, numbers):
    product = 1
    for i in range(0, 4):
        product *= numbers[row][col + i]
    
    return product

def left_diagonal_product(row, col, numbers):
    product = 1
    for i in range(0, 4):
        product *= numbers[row + i][col - i]
    
    return product

def right_diagonal_product(row, col, numbers):
    product = 1
    for i in range(0, 4):
        product *= numbers[row + i][col + i]

    return product
    
numbers = load_numbers_grid("Euler11Numbers.txt")

largest = 0
height = len(numbers)
width = len(numbers[0])
for row in range(0, width):
    for col in range(0, height):
        if row <= height - 4:
            largest = max(column_product(row, col, numbers), largest)
        
        if col <= width - 4:
            largest = max(row_product(row, col, numbers), largest)

        if row <= height - 4 and col >= 3:
            largest = max(left_diagonal_product(row, col, numbers), largest)

        if row <= height - 4 and col <= width - 4:
            largest = max(right_diagonal_product(row, col, numbers), largest)

print(largest)
