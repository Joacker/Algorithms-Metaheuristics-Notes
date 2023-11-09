FROM python:3.8.10
COPY . /test
WORKDIR /test
RUN pip install -r requirements.txt

RUN apt update && \
    apt upgrade -y && \
    apt install -y cmake build-essential openssh-server libeigen3-dev g++-7 && \
    update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-7 10

RUN echo 'export CXX=/usr/bin/g++-7' >> /root/.bashrc && \
    echo 'export CXXFLAGS="-std=c++17"' >> /root/.bashrc && \
    echo 'alias g++="g++-7 -std=c++17"' >> /root/.bashrc

CMD tail -f /dev/null

