import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("./resultados_min_heap.csv")
df2 = pd.read_csv("./resultados_fib_heap.csv")

fig, ax = plt.subplots()

ax.scatter(df['n'], df['tiempo'], color='lightcoral', label='Min Heap')
ax.plot(df['n'], df['tiempo'], color='lightcoral')
ax.scatter(df2['n'], df2['tiempo'], color='royalblue', label='Fibonacci Heap')
ax.plot(df2['n'], df2['tiempo'], color='royalblue')

plt.xlabel("Tamaño de la entrada (n)")
plt.ylabel("Tiempo (ms)")

ax.legend()
ax.grid(True)

plt.show()
