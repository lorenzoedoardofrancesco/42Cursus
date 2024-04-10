FROM alpine:3.19

RUN apk add --no-cache redis \
	&& sed -i "s|# bind 127.0.0.1|bind 127.0.0.1|g" /etc/redis.conf \
	&& sed -i "s|# maxmemory <bytes>|maxmemory 64mb|g" /etc/redis.conf \
	&& sed -i "s|# maxmemory-policy noeviction|maxmemory-policy allkeys-lru|g" /etc/redis.conf

CMD ["redis-server", "--protected-mode", "no"]
