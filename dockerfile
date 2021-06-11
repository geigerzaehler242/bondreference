FROM ubuntu:groovy

RUN apt-get update && \
	apt-get install -y build-essential git cmake autoconf libtool pkg-config 
WORKDIR /submission

COPY CMakeLists.txt main.cpp sample_input.json bond.* ./

RUN cmake . && make

CMD ["./sde-test-solution", "sample_input.json", "output_file.json"]
