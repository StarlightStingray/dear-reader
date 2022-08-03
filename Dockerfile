FROM drogonframework/drogon:latest
RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y libboost-all-dev
COPY . .
COPY config.json build/config.json
ADD static/ build/
WORKDIR build
RUN cmake ..
RUN make
CMD ["./dear-reader"]