FROM ubuntu:latest


RUN apt-get update && apt-get install -y \
    bash \
    g++ \
    gcc \
    flex \
    bison \
    python2-dev \
    make \
    build-essential

RUN apt install -y \
    python-is-python3

RUN apt install -y \
    python3-pip

RUN apt install libeigen3-dev -y

RUN apt update
RUN apt upgrade -y

# Mantener el contenedor en ejecución
CMD ["tail", "-f", "/dev/null"]

