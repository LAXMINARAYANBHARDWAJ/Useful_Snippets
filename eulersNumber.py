from decimal import Decimal, getcontext

getcontext().prec = int(input("Precision(decimals) >>> "))

n = int(input("n(Higher the better) >>> "))

e = (1 + Decimal(1)/n) ** n

print(e)
