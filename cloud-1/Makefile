deploy:
	ansible-playbook main.yml

provision-ec2:
	ansible-playbook main.yml --tags "aws"

setup-user:
	ansible-playbook main.yml --tags "user_setup"

deploy-docker:
	ansible-playbook main.yml --tags "docker"

deploy-webapp:
	ansible-playbook main.yml --tag webapp

start-all:
	ansible-playbook main.yml --tag webapp -e "cmd=start"

restart-all:
	ansible-playbook main.yml --tag webapp -e "cmd=restart"

stop-all:
	ansible-playbook main.yml --tag webapp -e "cmd=stop"

reset:
	ansible-playbook main.yml --tag webapp -e "cmd=reset"

.PHONY: deploy provision-ec2 setup-user deploy-docker deploy-webapp start-all restart-all stop-all reset