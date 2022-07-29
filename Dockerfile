FROM drogonframework/drogon:latest
COPY . .
WORKDIR build
RUN cmake ..
RUN make
CMD ["./dear-reader"]