import numpy as np
from scipy.optimize import dual_annealing

# Definir la función objetivo: función de Rosenbrock
def objetivo(x):
    return sum(100.0*(x[1:]-x[:-1]**2.0)**2.0 + (1-x[:-1])**2.0)

# Límites para cada dimensión
lw = [-5, -5]  # límite inferior
up = [5, 5]    # límite superior

# Ejecutar dual_annealing para minimizar la función objetivo
resultado = dual_annealing(objetivo, bounds=list(zip(lw, up)))

# Imprimir el resultado de la optimización
print("Coordenadas del mínimo: ", resultado.x)
print("Valor de la función objetivo en el mínimo: ", resultado.fun)
