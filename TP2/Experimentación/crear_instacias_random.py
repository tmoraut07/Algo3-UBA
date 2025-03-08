import numpy as np
import os

if not os.path.exists("./inputs"):
    os.makedirs("./inputs")

np.random.seed(1337)

def generate_input_file(filename, c):
    f = open(filename, "w")
    f.write(str(c) + "\n")

    for _ in range(c):
        N = np.random.randint(2, 1001)
        R = np.random.randint(1, 10001)
        W = np.random.randint(1, N)
        U = np.random.randint(1, 11)
        V = np.random.randint(U, 11)

        f.write(str(N) + " " + str(R) + " " + str(W) + " " + str(U) + " " + str(V) + "\n")

        office_positions = []
        for _ in range(N):
            x = np.random.randint(0, 1000)
            y = np.random.randint(0, 1000)
            office_positions.append((x, y))
            f.write(str(x) + " " + str(y) + "\n")

    f.close()

cases_per_file = 100

for power in range(16, 27):
    n = 2 ** power
    filename = "./inputs/input_" + str(n)

    generate_input_file(filename, cases_per_file)