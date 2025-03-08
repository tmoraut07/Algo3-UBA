import os

if not os.path.exists("./inputs"):
    os.makedirs("./inputs")

for power in range(16, 27):
    n = 2 ** power
    if n % 2 == 1:
        n += 1
    f = open("./inputs/input_" + str(n), "w")
    input = range(0, n)
    for num in input:
        f.write(str(num) + " ")
    f.close()
