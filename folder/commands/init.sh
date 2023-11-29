#!/bin/bash

# Listar el contenido del directorio
ls -la /app/src/numeric/dual-annealing/

# Ejecutar cmake
cmake ..

# Compilar e instalar
make
make install

# Configurar la variable de entorno LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/f2/app/dual-annealing/build:$LD_LIBRARY_PATH

# Listar el contenido del directorio de compilación
ls -la /f2/app/dual-annealing/build/

# Copiar la biblioteca compartida y actualizar ldconfig
cp /f2/app/dual-annealing/build/libdual_annealing.so /usr/local/lib/ 
ldconfig

# Verificar símbolos en la biblioteca compartida
# nm -D /usr/local/lib/libdual_annealing.so | grep thread_local_workspace

# Crear directorio para binarios personalizados
mkdir -p ~/bin

# Crear un script gpp y darle permisos de ejecución
echo '#!/bin/bash' > ~/gpp
echo '/usr/bin/g++ "$@" -ldual_annealing' >> ~/gpp
chmod +x ~/gpp

# Mover gpp al directorio bin
mv ~/gpp ~/bin/

# Agregar el directorio bin al PATH y configurar alias para g++
export PATH=~/bin:$PATH
echo 'alias g++="~/bin/gpp"' >> ~/.bashrc 
source ~/.bashrc

#cd /app/src/numeric/dual-annealing/examples