a = int(input("Number>>> "))

fac = 1

if a == 0:
    fac = fac * a

else:
    for i in range(1, a+1, 1):
        fac = fac * i

print(fac)
