FROM alpine:3.19

RUN apk add --no-cache bash mysql-client wget unzip php83 php83-fpm php83-mysqli \
    php83-json php83-curl php83-dom php83-exif php83-fileinfo php83-mbstring \
    php83-openssl php83-xml php83-zip php83-redis php83-phar php83-gd \
    php83-iconv php83-intl php83-common musl php83-tokenizer php83-ctype && \
    ln -s /usr/bin/php83 /usr/bin/php && \
    sed -i "s|listen = 127.0.0.1:9000|listen = 0.0.0.0:9000|g" /etc/php83/php-fpm.d/www.conf && \
    sed -i "s|;listen.owner = nobody|listen.owner = nobody|g" /etc/php83/php-fpm.d/www.conf && \
    sed -i "s|;listen.group = nobody|listen.group = nobody|g" /etc/php83/php-fpm.d/www.conf && \
    wget -O /usr/local/bin/wp https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
    chmod +x /usr/local/bin/wp

WORKDIR /var/www/html

RUN if [ ! -f index.php ]; then \
    wget https://wordpress.org/latest.tar.gz && \
    tar -xzvf latest.tar.gz && \
    mv wordpress/* . && \
    rm -r wordpress latest.tar.gz; \
    fi

COPY conf/wpconfig.sh /wpconfig.sh

RUN chmod +x /wpconfig.sh

ENTRYPOINT ["/wpconfig.sh"]
