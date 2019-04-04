def triangles(max_side_length):
    for a in range(1, max_side_length + 1):
        for b in range(a + 1, max_side_length + 1):
            for c in range(b + 1, max_side_length + 1):
                yield (a, b, c)

def right_triangles(max_side_length):
    for triangle in triangles(max_side_length):
        if triangle[0]**2 + triangle[1]**2 == triangle[2]**2:
            yield triangle

def solution_triangles(max_side_length):
    for triangle in right_triangles(max_side_length):
        if triangle[0] + triangle[1] + triangle[2] == 1000:
            yield triangle

solution_triangle = list(solution_triangles(1000))[0]
product = solution_triangle[0] * solution_triangle[1] * solution_triangle[2]
print(product)
