import sys

term = int(input("Enter the term of the Fibonacci series that you want: ")) - 2

a = 0
b = 1
c = 0

if term == 1:
    print(0)
    sys.exit()
elif term < 1:
    print("Invalid number")
    sys.exit()   

print(0)
print(1)

for i in range(0, term, 1):
    c = a + b
    a = b
    b = c
    print(c)
