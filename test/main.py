# Ejemplo de Simulated Annealing
import math, random, numpy as np


def costeFuncion(x):
    # Se realiza el coste seg[un la operacion propuesta
    v = 0
    v = x**3 - 60*x**2 + 900*x + 100
    return v    

# recibe un array de valores binarios y devuelve el valor decimal
def binarioADecimal(arr_binario):
    v = 0
    cont = 0
    for i in range(len(arr_binario)-1,-1,-1):
        if arr_binario[i] == 1:    
            v = v + float(2)**(float(cont))
        cont = cont + 1
    return v

temp = 1000
temp_final = 10

# Configurados en binarios de 5 digitos
sol = [0,0,0,0,0]

while temp > temp_final:
    
    # Busqueda aleatoria
    valor_encontrado = False
    
    # Generar un array del tamaño de la solución y a la vez una copia del array inicial
    mejorVecino = np.array(sol)
    
    # Generamos una variable entera para almacenar el costo de la solución
    costo_Actual = 0
    
    # Copiamos el vecino actual para ir modificandolo
    Copiavecino = np.array(sol)
    
    for i in range(0, len(sol)):
        
        if Copiavecino[i] == 1:
            Copiavecino[i] = 0
        else:
            Copiavecino[i] = 1
        
        # Comparamos el costo de la solución actual con el costo de la solución vecina
        costo_Vecino = 0
        
        