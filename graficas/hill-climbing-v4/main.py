import pandas as pd
import matplotlib.pyplot as plt

def generate_varianza(vector, mean, n):
    sumatoria = 0
    for i in range(n):
        sumatoria += (vector[i] - mean)**2
    return sumatoria / (n - 1)

def generate_desviacion_estandar(varianza):
    return varianza**(1/2)

# Nombres de los archivos CSV
archivos_csv = ['datos_hillclimbing_v2_1.csv', 'datos_hillclimbing_v2_2.csv', 'datos_hillclimbing_v2_3.csv', 
                'datos_hillclimbing_v2_4.csv', 'datos_hillclimbing_v2_5.csv']

# Leer todos los archivos CSV y combinarlos
dfs = [pd.read_csv(archivo) for archivo in archivos_csv]
df_combinado = pd.concat(dfs)

# Calcular los promedios
promedios = df_combinado.groupby('Archivo').mean()

promedios['Promedio de tiempo en segundos'] = promedios['Promedio de tiempo en segundos'].round(2)

promedios['Promedio de cantidad cajas'] = promedios['Promedio de cantidad cajas'].astype(int)

# Mostrar los promedios
print(promedios)

# Sin ordenar
plt.figure(figsize=(10, 6))
promedios['Promedio de tiempo en segundos'].plot(kind='bar', color='skyblue')
plt.title('Promedio de Tiempo en Segundos por Archivo')
plt.xlabel('Archivo')
plt.ylabel('Tiempo en Segundos')
plt.xticks(rotation=45)
plt.grid(axis='y', alpha=0.75)
plt.show()

# Gráfico de barras para 'Promedio de cantidad cajas'
plt.figure(figsize=(10, 6))
promedios['Promedio de cantidad cajas'].plot(kind='bar', color='salmon')
plt.title('Promedio de Cantidad de Cajas por Archivo')
plt.xlabel('Archivo')
plt.ylabel('Cantidad de Cajas')
plt.xticks(rotation=45)
plt.grid(axis='y', alpha=0.75)
plt.show()

# Ordenar los promedios de tiempo
promedios_tiempo_ordenado = promedios.sort_values(by='Promedio de tiempo en segundos')

# Ordenar los promedios de cantidad de cajas
promedios_cajas_ordenado = promedios.sort_values(by='Promedio de cantidad cajas')

# Gráfico de barras para 'Promedio de tiempo en segundos' ordenado
plt.figure(figsize=(10, 6))
promedios_tiempo_ordenado['Promedio de tiempo en segundos'].plot(kind='bar', color='skyblue')
plt.title('Promedio de Tiempo en Segundos por Archivo (Ordenado)')
plt.xlabel('Archivo')
plt.ylabel('Tiempo en Segundos')
plt.xticks(rotation=45)
plt.grid(axis='y', alpha=0.75)
plt.show()

# Gráfico de barras para 'Promedio de cantidad cajas' ordenado
plt.figure(figsize=(10, 6))
promedios_cajas_ordenado['Promedio de cantidad cajas'].plot(kind='bar', color='salmon')
plt.title('Promedio de Cantidad de Cajas por Archivo (Ordenado)')
plt.xlabel('Archivo')
plt.ylabel('Cantidad de Cajas')
plt.xticks(rotation=45)
plt.grid(axis='y', alpha=0.75)
plt.show()

promedios_ordenados = promedios.sort_values('Promedio de tiempo en segundos', ascending=False)

print(promedios_ordenados)

nombre_archivo_csv = "promedios.csv"
promedios_ordenados.to_csv('promedios.csv')

# leer el archivos promdios.csv
df_promedios = pd.read_csv(nombre_archivo_csv)
lenght_file = len(df_promedios)
# el promedio de tiempo lo quiero acotado con 2 decimales
time_mean = df_promedios['Promedio de tiempo en segundos'].mean().round(2)
cajas_mean = df_promedios['Promedio de cantidad cajas'].mean().astype(int)


##################### PROMEDIOS #####################
print("El promedio de tiempo en segundos es: ", time_mean)
print("El promedio de cajas es: ", cajas_mean)

##################### TIEMPO #####################
varianza = generate_varianza(df_promedios['Promedio de tiempo en segundos'], time_mean, lenght_file)
varianza = varianza.round(2)

print("La varianza del tiempo es: ", varianza)

desviacion_estandar = generate_desviacion_estandar(varianza)
desviacion_estandar = desviacion_estandar.round(2)

print("La desviación estándar del tiempo es: ", desviacion_estandar)

##################### CAJAS #####################
varianza = generate_varianza(df_promedios['Promedio de cantidad cajas'], cajas_mean, lenght_file)
varianza = varianza.round(2)

print("La varianza de las cajas es: ", varianza)

desviacion_estandar = generate_desviacion_estandar(varianza).round(2)

print("La desviación estándar de las cajas es: ", desviacion_estandar)