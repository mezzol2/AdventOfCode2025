import time

def main():
    start_time = time.perf_counter()
    total1 = 0
    total2 = 0
    file = open("input.txt","r")
    for line in file:
        line = line.strip()
        #convert string to a list of digits
        digits = [int(digit) for digit in line]
        #get the largest battery
        total1 += max_battery(digits)
        total2 += max_battery12(digits)
    
    end_time = time.perf_counter()

    print(f"Part 1: {total1}")
    print(f"Part 2: {total2}")
    print(f"Time: {end_time-start_time}")

def max_battery(digits:list) -> int:
    front = 1
    front_index = 0
    for i in range(len(digits)-1):
        if digits[i] == 9:
            front = 9
            front_index = i
            break
        elif digits[i] > front:
            front = digits[i]
            front_index = i
    
    back = 1
    for j in range(front_index+1,len(digits)):
        if digits[j] == 9:
            back = 9
            break
        elif digits[j] > back:
            back = digits[j]
    
    return front*10 + back

def max_battery12(digits:list) -> int:
    max_dig = list()
    k = 0
    for j in range(12):
            #make a new spot in the list
        max_dig.append(1)
        for i in range(k+1,len(digits)-j):
            if digits[i] == 9:
                max_dig[j] = 9
                k = i
                break
            elif digits[i] > max_dig[j]:
                max_dig[j] = digits[i]
                k = i
                
    max_str = "".join(map(str,max_dig))
    
    return int(max_str)

main()