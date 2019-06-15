class Node:
    def __init__(self, value):
        self.value = value
        self.max_value_total = value
        self.left = None
        self.right = None

def load_triangle(filename):
    with open(filename) as num_file:
        triangle = [list(map(lambda x: Node(int(x)), line.split())) for line in num_file]
        
        for row in range(len(triangle) - 2, -1, -1):
            for col in range(0, len(triangle[row])):
                node = triangle[row][col]
                node.left = triangle[row + 1][col]
                node.right = triangle[row + 1][col + 1]
        
        return triangle

def find_max_path_node(node):
    if (node.left.max_value_total > node.right.max_value_total):
        return node.left
    else:
        return node.right

triangle = load_triangle("Euler18Numbers.txt")
for row in range(len(triangle) - 2, -1, -1):
    for col in range(len(triangle[row])):
        node = triangle[row][col]
        max_path_node = find_max_path_node(node)
        node.max_value_total = node.value + max_path_node.max_value_total

max_path_value = triangle[0][0].max_value_total
print(max_path_value)
