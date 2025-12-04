import time

def main():
    start_time = time.perf_counter()
    dial = 50
    count1 = 0
    count2 = 0
    file = open("input.txt","r")
    for line in file:
        line = line.strip()
        num_rotations = int(line[1:])
        if line[0] == "L":
            old_dial = dial
            dial = dial-num_rotations
        else:
            dial = dial+num_rotations
        if dial > 99:
            count2 += dial//100
        if dial < 1:
            count2 += ((old_dial-1) // 100) - ((dial-1) // 100)
        dial = dial % 100    
        if dial == 0: 
            count1 = count1 + 1
    file.close()
    end_time = time.perf_counter()
    
    print(f"Part 1: {count1}")
    print(f"Part 2: {count2}")
    print(f"Solution time: {end_time-start_time}")

main()