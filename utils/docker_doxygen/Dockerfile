FROM alpine:3.10
RUN apk add --no-cache doxygen graphviz py3-pip
RUN pip3 install --no-cache-dir doxypypy
COPY py_filter /usr/local/bin/
WORKDIR /gomoku_prj
VOLUME [ "/gomoku_prj" ]
ENTRYPOINT [ "doxygen" ]