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

# funcion probabilidad de aceptacion
def probabilidadAceptacion(costoVecino, costoActual, temp):
    if costoVecino < costoActual:
        return 1
    else:
        return math.exp(-((costoVecino - costoActual)/temp))

temp = 1000
temp_final = 10

# Configurados en binarios de 5 digitos
sol = [0,0,0,0,0]
costo_Actual = costeFuncion(binarioADecimal(sol))
print("Costo actual: ", costo_Actual)
# Probabilidad de aceptacion
print("Probabilidad de aceptacion: ", probabilidadAceptacion(0, costo_Actual, temp))
# Binaio a decimal
print("Binario a decimal: ", binarioADecimal(sol))
while temp > temp_final:
    
    # Busqueda aleatoria
    valor_encontrado = False
    
    costo_Actual = costeFuncion(binarioADecimal(sol))
    
    # Copiamos la solucion de sol en mejor vecino
    mejor_vecino = sol.copy()
    
    # Copiamos el vecino actual para ir modificandolo
    copiaVecino = sol.copy()
    for i in range(len(sol)):
       # Hallamos los vecinos con una funcion que altera los bits
       # Por ejemplo los vecinos {0,0,1,0,1} serian:
       # {1,0,1,0,1} , {0,1,1,0,1} , {0,0,0,0,1} , {0,0,1,1,1} , {0,0,1,0,0}
       
       if 
        
        