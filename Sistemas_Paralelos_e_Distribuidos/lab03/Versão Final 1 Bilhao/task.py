# Feito com amor por Bruno e Marcos
# PSPD - Fernando

#!/usr/bin/env python
import pika
import json
import time

connection = pika.BlockingConnection(
    pika.ConnectionParameters(host='localhost'))
channel = connection.channel()

channel.queue_declare(queue='task_queue', durable=True)
channel.queue_declare(queue='hello')

#função callback que recebe o vetor de infomação sobre o vetor segmentado
def callback(ch, method, properties, body):

    #info é o corpo da "struct" enviada pelo send
    info = json.loads(body)

    print(" [x] Recebi a infomação %r" % info )
    
    #dados da "struct" 
    tamanhoInicial = info[0]
    tamanhoFinal = info[1]
    tamanhoTotal = (tamanhoFinal - tamanhoInicial)+1
    qtdNumVetor = info[2]
    #vetor preenche com zeros um vetor do tamanho qtdNumVetor
    vetor = [0]*qtdNumVetor
    tamanho = info[3]

    tamanhoDivisao = (tamanho)/2
    k = 0
    j = tamanhoInicial

    #laço que preeenche os vetores segmentados com seus valores e o organiza do menor para o maior
    while k != tamanhoTotal: 

        i = 0
        while i != qtdNumVetor:
            n = (j - tamanhoDivisao ) ** 2
            n = n ** (1/2)
            vetor[i] = n
            i += 1
            j += 1
            k += 1
        vetor.sort()
        vetorPequeno = [ vetor[0], vetor[-1] ]
        #envia o vetor com as informações de máximo e mínimo de cada vetor segmentado para a fila hello para o receive trabalhar.
        channel.basic_publish(exchange='', routing_key='hello', body=json.dumps(vetorPequeno))
    #    print(vetor)
    #    print(" [x] Enviei %r pacotes " % k)
    
    #toda vez que um daemon worker terminar seus calculos ele envia uma string 'acabou' que informa o fim do envio de informações para a fila hello.
    print(" [x] Enviei todos os pacotes!")
    channel.basic_publish(exchange='', routing_key='hello', body=json.dumps('acabou'))
    ch.basic_ack(delivery_tag=method.delivery_tag)

    channel.close()

print(' [*] Waiting for messages. To exit press CTRL+C')


channel.basic_qos(prefetch_count=1)
#realiza o binding 
channel.basic_consume(queue='task_queue', on_message_callback=callback)
#começa a consumir o dados da fila
channel.start_consuming()