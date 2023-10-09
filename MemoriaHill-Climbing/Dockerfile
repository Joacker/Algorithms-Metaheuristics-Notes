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

# Mantener el contenedor en ejecución
CMD ["tail", "-f", "/dev/null"]

