#!/usr/bin/env python
import pika, sys, os
import json

def main():
    connection = pika.BlockingConnection(pika.ConnectionParameters(host='localhost'))
    channel = connection.channel()

    channel.queue_declare(queue='hello')
    channel.queue_declare(queue='world')

    def callback(ch, method, properties, body):
        print(" [x] Recebi o vetor")
        maximo = max(json.loads(body))
        minimo = min(json.loads(body))
        vetorVolta = [ minimo, maximo ]

        channel.basic_publish(exchange='', routing_key='world', body=json.dumps(vetorVolta))
        print(" [x] Mandei o valor max e min")

    channel.basic_consume(queue='hello', on_message_callback=callback, auto_ack=True)

    print(' [*] Esperando a mensagem, para sair digite CTRL+C')
    channel.start_consuming()

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('Interrompido')
        try:
            sys.exit(0)
        except SystemExit:
            os._exit(0)