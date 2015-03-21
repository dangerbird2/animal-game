FROM debian:latest

RUN apt-get update \
    && apt-get -y install gcc g++ make cmake


COPY . usr/src/animal
WORKDIR usr/src/animal
RUN CMAKE_BUILD_TYPE=RelWithDebInfo    \
    && cmake . && make
CMD tests ["usr/src/animal/animal_tests"]
CMD animal ["usr/src/animal/animal"]