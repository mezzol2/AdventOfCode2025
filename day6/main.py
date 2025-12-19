import time

def read_file() -> list:
    table = list()

    with open("input.txt","r") as file:
        first = True
        for line in file:
            data = line.strip().split()
            i = 0
            for element in data:
                if first:
                    table.append(list())
                if element not in ["+","*"]:
                    table[i].append(int(element))
                else:
                    table[i].append(element)
                i += 1

            first = False

    return table

def part1_func(table:list) -> int:
    total = 0
    
    for column in table:
        if column[-1] == "*":
            product = 1
            for element in column:
                if element != "*":
                    product *= element
            total += product
        else:
            for element in column:
                if element != "+":
                    total += element
    
    return total

def part2_func(table:list) -> list:
    pass

def main():
    start_time = time.perf_counter()

    table = read_file()
    part1 = part1_func(table)

    end_time = time.perf_counter()

    print(f"Part 1: {part1}")
    # print(f"Part 2: {part2}")
    print(f"Solution time: {end_time-start_time}")



main()