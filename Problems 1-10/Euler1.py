# Use sets to avoid duplicate values
multiples_of_3_and_5 = set(range(0, 1000, 3)) | set(range(0, 1000, 5))

total = sum(multiples_of_3_and_5)
print(total)
