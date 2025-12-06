import time

def main():
    start_time = time.perf_counter()
    sum = 0
    file = open("input.txt","r")
    content = file.read().strip().split(",")
    for num_range in content:
        int_range = convert_range_to_int(num_range)
        sum += check_range(int_range)
    end_time = time.perf_counter()
    print(f"Part 1: {sum}")
    print(f"Time: {end_time-start_time}")

def convert_range_to_int(str_range:str) -> list:
    str_range = str_range.split("-")
    return [int(x) for x in str_range]

def check_range(int_range:list) -> int:
    range_sum = 0
    for x in range(int_range[0],int_range[1]+1):
        str_x = str(x)
        l = len(str_x)
        if l % 2 == 0:  #if even
            low = x%(10**(l//2))
            high = low*(10**(l//2))
            if x == high + low:
                range_sum += x
    return range_sum
        
    
main()