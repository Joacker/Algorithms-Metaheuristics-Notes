FROM python:3.8.10
COPY . /test
WORKDIR /test

# Install dependencies
RUN pip install -r requirements.txt && \
    apt update && \
    apt upgrade -y && \
    apt install -y cmake build-essential openssh-server libeigen3-dev g++-8

# Set g++-8 as the default C++ compiler
RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-8 10 && \
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 10 && \
    update-alternatives --install /usr/bin/cc cc /usr/bin/gcc 30 && \
    update-alternatives --set cc /usr/bin/gcc && \
    update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++ 30 && \
    update-alternatives --set c++ /usr/bin/g++

# Set CXX and CXXFLAGS environment variables
ENV CXX=/usr/bin/g++-8
ENV CXXFLAGS="-std=c++17"

CMD tail -f /dev/null

