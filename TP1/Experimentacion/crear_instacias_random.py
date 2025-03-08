# generador creado por chat gpt para generar numeros aleatorios en cantidad par tal que por cada par n1,n2 se cumpla que n1 < n2

import numpy as np
import os

if not os.path.exists("./inputs"):
    os.makedirs("./inputs")


np.random.seed(1337)

for power in range(16, 27):
    n = 2 ** power
    f = open("./inputs/input_" + str(n), "w")

    # Generar una lista aleatoria de números y mezclarlos
    input = np.arange(2 * n)
    np.random.shuffle(input)

    # Tomar cada par de números consecutivos como un par ordenado
    for i in range(0, 2 * n, 2):
        n1, n2 = input[i], input[i+1]
        if n1 > n2:
            n1, n2 = n2, n1
        f.write(str(n1) + " " + str(n2) + "\n")
        
    f.close()
