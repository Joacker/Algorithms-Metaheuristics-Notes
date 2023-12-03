FROM python:3.8.10
COPY . /test
WORKDIR /test

# Install dependencies
RUN pip install -r requirements.txt && \
    apt update && \
    apt upgrade -y && \
    apt install -y cmake build-essential openssh-server libeigen3-dev g++-8

RUN apt install libboost-all-dev -y

# Set CXX and CXXFLAGS environment variables
ENV CXX=/usr/bin/g++-8
ENV CXXFLAGS="-std=c++17"

CMD tail -f /dev/null

