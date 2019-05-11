def collatz_sequence(num):
    while num != 1:
        yield num
        if num % 2 == 0:
            num = num // 2
        else:
            num = 3 * num + 1
    
    yield 1

# Cache previously calculated lengths to speed things up
# Add a dummy first element so n-th element can be indexed with n
cached_sequence_lengths = []
cached_sequence_lengths.append(0)

def collatz_sequence_length(num):
    length = 0
    for term in collatz_sequence(num):
        if term < len(cached_sequence_lengths):
            length += cached_sequence_lengths[term]
            return length
        else:
            length += 1
    
    return length

longest = 1
for num in range(1, 1000000):
    cached_sequence_lengths.append(collatz_sequence_length(num))
    if cached_sequence_lengths[num] > cached_sequence_lengths[longest]:
        longest = num

print(longest)
