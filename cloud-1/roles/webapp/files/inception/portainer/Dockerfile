FROM alpine:3.19

RUN apk --no-cache add wget tar \
    && wget https://github.com/portainer/portainer/releases/download/2.19.4/portainer-2.19.4-linux-amd64.tar.gz \
    && tar xvzf portainer-2.19.4-linux-amd64.tar.gz \
    && rm portainer-2.19.4-linux-amd64.tar.gz

CMD ["/portainer/portainer"]
