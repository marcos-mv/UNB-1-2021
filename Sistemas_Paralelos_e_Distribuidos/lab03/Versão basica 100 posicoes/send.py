#!/usr/bin/env python
import pika
import json

connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
channel = connection.channel()

channel.queue_declare(queue='hello')
channel.queue_declare(queue='world')

def callback(ch, method, properties, body):
    vetorVolta = json.loads(body)
    print(" [x] Recebi o vetor do servidor")

    print( "Minimo: %r" % vetorVolta[0],"Máximo: %r" % vetorVolta[1])

    channel.close()
    

vetor = []
tamanho = 10000000
i = 0

while len(vetor) != tamanho: 
    n = (i - tamanho/2) ** 2
    n = n ** (1/2)
    vetor.append(n)
    i += 1

channel.basic_publish(exchange='', routing_key='hello', body=json.dumps(vetor))
print(" [x] Enviei o vetor")

channel.basic_consume(queue='world', on_message_callback=callback, auto_ack=True)



channel.start_consuming()
