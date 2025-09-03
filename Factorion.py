apex = int(input("Enter the apex value: "))

summ = 0

for i in range(0, apex + 1, 1):

    i1 = i
    
    while i != 0:

        x = i % 10
        
        fac = 1
 
        for j in range(1, x + 1, 1):
            fac = fac * j
                          
        summ = summ + fac
        
        i = i // 10
        
    if i1 == summ:
        print(f"{i1}")
    summ = 0
    