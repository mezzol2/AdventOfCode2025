import time

def main():
    start_time = time.perf_counter()
    total = 0
    file = open("input.txt","r")
    for line in file:
        line = line.strip()
        #convert string to a list of digits
        digits = [int(digit) for digit in line]
        #get the largest battery
        total += max_battery(digits)
    
    end_time = time.perf_counter()

    print(f"Part 1: {total}")
    #print(f"Part 2: {sum2}")
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
    for j in range(k+1,len(digits)):
        if digits[j] == 9:
            back = 9
            break
        elif digits[j] > back:
            back = digits[j]
    
    return front*10 + back

main()