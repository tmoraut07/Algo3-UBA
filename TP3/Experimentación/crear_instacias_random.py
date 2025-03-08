import random

c = int(input("Cantidad de casos de test\n"))
nombre = input("Nombre de archivo\n")

with open(f"./{nombre}.txt", "w") as archivo:
    lineas = [f"{c}\n"]

    n_usado = set()
    for i in range(c):

        while True:
            N = random.randint(1, 10000)
            if N not in n_usado:
                n_usado.add(N)
                break

        M = N * 10

        k = random.randint(1, 5)
        s = random.randint(1, N)

        t = random.randint(1, N)
        while t==s:
            t = random.randint(1, N)


        lineas.append("{} {} {} {} {}\n".format(N,M,k,s,t))

        combinaciones_hechas = set()

        for calle in range(M):
            desde = random.randint(1, N)
            hasta = random.randint(1, N)

            while (desde, hasta) in combinaciones_hechas or desde == hasta:
                desde = random.randint(1, N)
                hasta = random.randint(1, N)
            
            combinaciones_hechas.add((desde, hasta))

            longitud = random.randint(1, 1000)
            linea = "{} {} {}\n".format(desde, hasta, longitud)
            lineas.append(linea)

        # Creo array de combinanciones hechas
        combinaciones_hechas = set()
        for i in range(N + 1):
            combinaciones_hechas.add((i,))

        for nuevas_calles in range(k):
            desde = random.randint(1, N)
            hasta = random.randint(1, N)

            while (desde, hasta) in combinaciones_hechas or (hasta, desde) in combinaciones_hechas or desde == hasta:
                desde = random.randint(1, N)
                hasta = random.randint(1, N)

            combinaciones_hechas.add((desde, hasta))
            combinaciones_hechas.add((hasta, desde))

            longitud = random.randint(1, 1000)
            linea = "{} {} {}\n".format(desde, hasta, longitud)
            lineas.append(linea)

    archivo.writelines(lineas)