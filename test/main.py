import math, random

def costeFuncion(x):
    return x**3 - 60*x**2 + 900*x + 100

def binarioADecimal(arr_binario):
    v = 0
    for i, bit in enumerate(reversed(arr_binario)):
        v += bit * (2 ** i)
    return v

def probabilidadAceptacion(costoVecino, costoActual, temp):
    if costoVecino < costoActual:
        return 1
    else:
        return math.exp(-((costoVecino - costoActual) / temp))

temp = 1000
temp_final = 10

# Configuración inicial aleatoria
sol = [random.randint(0, 1) for _ in range(5)]
mejor_vecino = sol[:]
costo_actual = costeFuncion(binarioADecimal(mejor_vecino))
print("Costo actual:", costo_actual)

while temp > temp_final:
    costo_actual = costeFuncion(binarioADecimal(sol))
    mejor_vecino = sol[:]
    
    for i in range(len(sol)):
        vecino = sol[:]
        vecino[i] = 1 - vecino[i]  # Cambia 0 a 1 o 1 a 0
        costo_vecino = costeFuncion(binarioADecimal(vecino))
        
        if (costo_vecino < costo_actual or
                probabilidadAceptacion(costo_vecino, costo_actual, temp) > random.random()):
            mejor_vecino = vecino[:]
            costo_actual = costo_vecino
    
    sol = mejor_vecino[:]
    temp *= 0.9  # Enfriamiento gradual

print("Solucion:", sol)
print("Valor decimal:", binarioADecimal(sol))