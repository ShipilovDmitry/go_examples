FROM golang:1.22-alpine

WORKDIR /app

RUN apk add g++ vim make cmake
COPY . ./

RUN cmake -Bbuild . && cmake --build build \
    && cp build/go_bridge/libgo_bridge.a /app/go_main/libs \
    && cp build/sources/libtrack-filter.a /app/go_main/libs

RUN cd go_main && go build main.go \
    && ./main

CMD [ "sh" ]
