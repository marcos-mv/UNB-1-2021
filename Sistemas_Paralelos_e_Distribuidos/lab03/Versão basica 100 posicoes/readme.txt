Versão básica do projeto solução para um vetor de 100 posições
a versão final com o relatorio completo está na pasta Versão final 1 Bilhao.

É necessário a biblioteca pika para a correta execução dos programas e o RabbitMQ instalado.
Para instalar bastar possuir Docker na máquina e executar esse comando:

docker run -it --rm --name rabbitmq -p 5672:5672 -p 15672:15672 rabbitmq:3.9-management

e o módulo pika:

python -m pip install pika --upgrade

Para executar projeto, em um terminal rode o comando:

python3 receive.py

e em outro terminal

python3 send.py
