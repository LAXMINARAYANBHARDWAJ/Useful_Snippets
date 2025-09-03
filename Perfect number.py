import math

def is_prime(n):
    #Check primality using 6k ± 1 optimization
    if n < 2:
        return False
    if n in (2, 3):
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False
    i = 5
    w = 2
    while i * i <= n:
        if n % i == 0:
            return False
        i += w
        w = 6 - w
    return True

def perfect_numbers(limit):
    #Generate perfect numbers using Euclid–Euler theorem
    results = []
    p = 2
    while True:
        mersenne = (1 << p) - 1  # 2^p - 1
        if is_prime(mersenne):
            perfect_num = (1 << (p - 1)) * mersenne  # 2^(p-1) * (2^p - 1)
            if perfect_num > limit:
                break
            results.append(perfect_num)
        p += 1
    return results

# User input
limit = int(input("Find perfect numbers up to: "))
nums = perfect_numbers(limit)

print("\nPerfect numbers up to", limit, ":")
print(nums if nums else "None found.")
