def calcular_diferencia_promedio(archivo1, archivo2):
    tiempos1 = []
    tiempos2 = []

    # Leer los tiempos del archivo 1
    with open(archivo1, 'r') as file1:
        for linea in file1:
            tiempo = int(linea.strip())
            tiempos1.append(tiempo)

    # Leer los tiempos del archivo 2
    with open(archivo2, 'r') as file2:
        for linea in file2:
            tiempo = int(linea.strip())
            tiempos2.append(tiempo)

    # Calcular la diferencia para cada instancia
    diferencias = [t2 - t1 for t1, t2 in zip(tiempos1, tiempos2)]

    # Calcular el promedio de las diferencias
    promedio_diferencias = sum(diferencias) / len(diferencias)

    return promedio_diferencias

# Ruta de los archivos de tiempo
archivo1 = 'resultados_min_heap.txt'
archivo2 = 'resultados_fib_heap.txt'

# Calcular la diferencia promedio
diferencia_promedio = calcular_diferencia_promedio(archivo1, archivo2)

print("La diferencia promedio es:", diferencia_promedio, "milisegundos")
