## dockerfile for using linux's valgrind for memory debugging
FROM debian:latest

RUN apt-get update \
    && apt-get -y install gcc g++ make cmake valgrind


COPY . usr/src/animal
WORKDIR usr/src/animal
RUN CMAKE_BUILD_TYPE=RelWithDebInfo    \
    && cmake . && make
CMD tests ["valgrind", "usr/src/animal/animal_tests"]
CMD animal ["valgrind", "usr/src/animal/animal"]