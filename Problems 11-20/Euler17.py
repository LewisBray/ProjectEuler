num_of_letters_1_to_19 = {
    1:  3,
    2:  3,
    3:  5,
    4:  4,
    5:  4,
    6:  3,
    7:  5,
    8:  5,
    9:  4,
    10: 3,
    11: 6,
    12: 6,
    13: 8,
    14: 8,
    15: 7,
    16: 7,
    17: 9,
    18: 8,
    19: 8
}

def num_of_letters_from_second_digit(n):
    return {
        1 : 3,  # Only valid when n' == 10
        2 : 6,
        3 : 6,
        4 : 5,
        5 : 5,
        6 : 5,
        7 : 7,
        8 : 6,
        9 : 6
    }[n // 10]

def num_of_letters_from_third_digit(n):
    num_of_letters_in_hundred = 7
    return num_of_letters_1_to_19[n // 100] + num_of_letters_in_hundred

def num_of_letters_1_to_99(n):
    if n % 10 == 0:
        return num_of_letters_from_second_digit(n)
    elif n >= 20 and n < 100:
        return num_of_letters_from_second_digit(n) + num_of_letters_1_to_19[n % 10]
    else:
        return num_of_letters_1_to_19[n]

def num_of_letters_1_to_999(n):
    num_of_letters_in_and = 3
    if n >= 100:
        if n % 100 != 0:
            return num_of_letters_from_third_digit(n) \
                   + num_of_letters_in_and + num_of_letters_1_to_99(n % 100)
        else:
            return num_of_letters_from_third_digit(n)
    else:
        return num_of_letters_1_to_99(n)

num_of_letters_in_one_thousand = 11
total = num_of_letters_in_one_thousand
for n in range(1, 1000):
    total += num_of_letters_1_to_999(n)

print(total)
