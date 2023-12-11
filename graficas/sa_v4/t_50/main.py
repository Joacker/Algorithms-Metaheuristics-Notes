import pandas as pd
import matplotlib.pyplot as plt

# Nombres de los archivos CSV
archivos_csv = ['resultadosSAv3_25_v1_1.csv', 'resultadosSAv3_25_v1_2.csv', 'resultadosSAv3_25_v1_3.csv', 
                'resultadosSAv3_25_v1_4.csv', 'resultadosSAv3_25_v1_5.csv']

# Leer todos los archivos CSV y combinarlos
dfs = [pd.read_csv(archivo) for archivo in archivos_csv]
df_combinado = pd.concat(dfs)

# Calcular los promedios
promedios = df_combinado.groupby('Archivo').mean()

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