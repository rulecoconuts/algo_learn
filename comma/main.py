with open('input.txt', 'r') as input, open('output.txt', 'w') as output:
    lines = input.readlines()
    lines = [line.replace("\n", "").strip() for line in lines]
    output.write(", ".join(lines))