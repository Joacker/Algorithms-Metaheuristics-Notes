FROM python:3.8.10
COPY . /test
WORKDIR /test
RUN pip install -r requirements.txt


RUN apt update && apt upgrade -y && apt install -y cmake build-essential openssh-server libeigen3-dev

CMD tail -f /dev/null

