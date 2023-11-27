FROM ubuntu:latest

WORKDIR /app

RUN apt-get update && apt-get install -y \
    bash \
    g++ \
    gcc \
    flex \
    bison \
    python2-dev \
    make \
    build-essential \
    cmake \
    openssh-server 

RUN apt install -y \
    python-is-python3 git vim

RUN apt install -y \
    python3-pip sudo

RUN apt install libeigen3-dev -y

RUN apt update
RUN apt upgrade -y
# Configuración para usar C++17 por defecto con g++
RUN echo 'alias g++="g++ -std=c++17"' >> ~/.bashrc

COPY ./commands/*.sh .

RUN export LD_LIBRARY_PATH=/app/src/numeric/dual-annealing/build:$LD_LIBRARY_PATH

#RUN sudo cp /app/src/numeric/dual-annealing/build/libdual_annealing.so /usr/local/lib/

#RUN sudo ldconfig

# Mantener el contenedor en ejecución
CMD ["tail", "-f", "/dev/null"]