from decimal import Decimal, getcontext

getcontext().prec = int(input("Precision (in decimals) >>> "))

n = (int(input("nth term (>2, Bigger the n, more accurate the result): ")))

a, b = 0, 1

fib = [a, b]

for i in range(3, n + 1, 1):
    c = a + b
    fib.append(c)
    a = b
    b = c

phi = (Decimal(fib[(-1)]) / fib[(-2)])

print(phi)
