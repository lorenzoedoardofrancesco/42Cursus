#!/bin/sh

if [ ! -d "/var/lib/mysql/mysql" ]; then
	chown -R mysql:mysql /var/lib/mysql
	mysql_install_db --basedir=/usr --user=mysql --datadir=/var/lib/mysql
fi

if [ ! -d "/var/lib/mysql/${DATABASE_NAME}" ]; then

/usr/bin/mysqld --user=mysql --bootstrap <<EOF
USE mysql;
FLUSH PRIVILEGES;
DELETE FROM mysql.user WHERE User='';
DROP DATABASE test;
DELETE FROM mysql.db WHERE Db='test';
DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost', '127.0.0.1', '::1');
ALTER USER 'root'@'localhost' IDENTIFIED BY '${DATABASE_ROOT_PW}';
CREATE DATABASE ${DATABASE_NAME} CHARACTER SET utf8 COLLATE utf8_general_ci;
CREATE USER '${DATABASE_USER}'@'%' IDENTIFIED by '${DATABASE_PW}';
GRANT ALL PRIVILEGES ON ${DATABASE_NAME}.* TO '${DATABASE_USER}'@'%';
FLUSH PRIVILEGES;
EOF

fi
