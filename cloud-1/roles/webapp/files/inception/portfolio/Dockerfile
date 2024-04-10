FROM alpine:3.19

RUN apk add --no-cache nginx

RUN mkdir -p /var/www/html && \
	printf "server {\n\
	listen 80;\n\
	root /var/www/html;\n\
	location / {\n\
	try_files \$uri \$uri/ /index.html;\n\
	}\n\
	}" > /etc/nginx/http.d/default.conf

COPY conf/ /var/www/html

EXPOSE 80

CMD ["nginx", "-g", "daemon off;"]