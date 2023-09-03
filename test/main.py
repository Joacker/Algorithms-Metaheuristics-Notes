# Ejemplo de Simulated Annealing
import math, random, numpy as np

temp = 1000
temp_final = 10

sol = [0,0,0,0,0]

mejorVecino = np.array(sol)

print("Solución inicial: ", mejorVecino)

# while temp > temp_final:
    
#     # Busqueda aleatoria
#     valor_encontrado = False
    
#     # Generar una solución vecina del mismo tamaño que la solución actual
#     mejorVecino = np.array(sol)