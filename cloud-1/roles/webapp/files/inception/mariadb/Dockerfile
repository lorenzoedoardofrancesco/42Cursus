FROM alpine:3.19

ARG DATABASE_NAME \
	DATABASE_USER \
	DATABASE_PW \
	DATABASE_ROOT_PW

RUN apk add --no-cache mariadb mariadb-client

RUN mkdir /var/run/mysqld && \
    chmod 777 /var/run/mysqld && \
    { \
      echo '[mysqld]'; \
      echo 'skip-host-cache'; \
      echo 'skip-name-resolve'; \
      echo 'bind-address=0.0.0.0'; \
    } > /etc/my.cnf.d/docker.cnf && \
    sed -i 's|skip-networking|skip-networking=0|g' /etc/my.cnf.d/mariadb-server.cnf

COPY conf/create_db.sh /create_db.sh

RUN sh /create_db.sh

USER mysql

CMD ["/usr/bin/mysqld", "--skip-log-error"]
