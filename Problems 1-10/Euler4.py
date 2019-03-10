def three_digit_numbers():
    for num in range(100, 1000):
        yield num

def is_palindrome(num):
    num_as_str = str(num)
    str_len = len(num_as_str)
    	
    for i in range(0, str_len):
        if num_as_str[i] != num_as_str[str_len - 1 - i]:
            return False
    
    return True

def three_digit_number_product_palindromes():
    for x in three_digit_numbers():
        for y in three_digit_numbers():
            product = x * y
            if is_palindrome(product):
                yield product

largest = max(three_digit_number_product_palindromes())
print(largest)
