# Feito com amor por Bruno e Marcos
# PSPD - Fernando

#!/usr/bin/env python
# lista queues sudo rabbitmqctl list_queues
# delete queues sudo rabbitmqctl delete_queue <nomeDaQueue>

import pika
import json
import subprocess

connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
channel = connection.channel()

channel.queue_declare(queue='hello')
channel.queue_declare(queue='world')

#laço que cria daemos que recebem os vetores segmentados

for z in range(10):
      bashCmd = ["python3", "task.py"]
      process = subprocess.Popen(bashCmd, stdout=subprocess.PIPE)

#função que recebe os dados do servidor com os valores de máximo e mínimo

def callback(ch, method, properties, body):
    vetorVolta = json.loads(body)
    print(" [x] Recebi o vetor do servidor")

    print( " O MAXIMO: %r" % vetorVolta[1],"O MINIMO: %r" % vetorVolta[0])

    channel.close()

#tamanho = tamanho do vetor
#qtdNumVetor = indica o numero de pacotes enviados  

tamanho = 1000000000
qtdNumVetor = 100000

#processos = numero de processos daemons abertos
#divisão = recebe o tamanho completo do vetor e divide pelo numero de processos abertos

processos = 10
divisao = tamanho/processos

tamanhoInicial = 0
tamanhoFinal = divisao-1
i = 0

#laço que envia os vetores segmentados, enquanto o contador for diferente do número de processos(workers)
while i != processos: 

    #info é o vetor que envia as informações para o worker realizar a operação o body envia as infomações 
    #info [0] indica o inicio do vetor segmentado
    #info [1] indica o fim do vetor segmentado
    #info [2] indica a quantidade de pacotes de cada vetor segmentados
    #info [3] indica o tamanho total do vetor completo
    info = [ tamanhoInicial, tamanhoFinal, qtdNumVetor, tamanho ]

    #estabelece o canal de comunicação com sua fila para o worker[i]
    channel.basic_publish(exchange='', routing_key='task_queue', body=json.dumps(info))
    print(" [x] Enviei a informação %r" % info)

    #incrementa os dados da proxima info para o envio para o proximo worker
    tamanhoInicial = tamanhoFinal+1
    tamanhoFinal = tamanhoFinal+divisao
    i+=1

channel.basic_consume(queue='world', on_message_callback=callback, auto_ack=True)

channel.start_consuming()
