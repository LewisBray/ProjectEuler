def square_numbers(limit):
	for num in range(limit):
		yield num ** 2

sum_of_squares = sum(square_numbers(101))
square_of_sum = sum(x for x in range(101)) ** 2

answer = square_of_sum - sum_of_squares
print(answer)
