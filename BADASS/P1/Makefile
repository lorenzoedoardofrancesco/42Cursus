CONTAINER_NAME=frrouting-badass

all: build run modify commit

build:
	docker pull quay.io/frrouting/frr:9.1.0
	docker pull alpine

run:
	docker run -d --name frr quay.io/frrouting/frr:9.1.0 /usr/lib/frr/docker-start

modify:
	docker exec frr sh -c 'touch /etc/frr/vtysh.conf && sed -i "s/bgpd=no/bgpd=yes/; s/ospfd=no/ospfd=yes/; s/isisd=no/isisd=yes/" /etc/frr/daemons'

stop:
	docker stop frr

commit: stop
	docker commit $(shell docker ps -aqf "name=frr") $(CONTAINER_NAME)

clean:
	docker rm $(CONTAINER_NAME)

fclean: clean
	docker system prune -af

re: fclean all
