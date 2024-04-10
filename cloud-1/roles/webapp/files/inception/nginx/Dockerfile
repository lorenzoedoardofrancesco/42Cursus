FROM alpine:3.19

RUN apk add --no-cache nginx openssl

RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
	-keyout /etc/ssl/private/lsimanic.42.fr.key \
	-out /etc/ssl/certs/lsimanic.42.fr.crt \
	-subj "/C=FR/ST=Ile-de-France/L=Paris/O=Ecole42/CN=lsimanic.42.fr"

COPY conf/nginx.conf etc/nginx/nginx.conf

EXPOSE 443

CMD ["nginx", "-g", "daemon off;"]
