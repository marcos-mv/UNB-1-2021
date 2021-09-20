# Feito com amor por Bruno e Marcos
# PSPD - Fernando

#!/usr/bin/env python
import pika, sys, os
import json

#valores teste para iniciar a comparação com os vetores max e min dos vetores segmentados calculados no worker daemon
maximo = 0
minimo = 50
vetorVolta = [ minimo, maximo ]
i = 0
acabou = 0

def main():
    connection = pika.BlockingConnection(pika.ConnectionParameters(host='localhost'))
    channel = connection.channel()

    channel.queue_declare(queue='hello')
    channel.queue_declare(queue='world')

    def callback(ch, method, properties, body):

        #vetorVolta é o vetor contendo o valor máximo e mínimo de cada vetor segmentado recebido do worker daemon task.py
        global vetorVolta
        global maximo
        global minimo
        global i
        global acabou

        vetor = json.loads(body)

        # o recebimento do 'acabou' indica do fim das operações realizadas pelos workers daemons task.py
        # se ele receber 10 vezes acabou indica que todos os processos daemons terminaram suas operações
        # logo o worker receive pode enviar os dados finais do max e min para o send.
        if vetor == ('acabou') :
            acabou += 1
            if acabou == 10:
                channel.basic_publish(exchange='', routing_key='world', body=json.dumps(vetorVolta))
                print(" [x] Mandei o valor max e min")
                acabou = 0
                minimo = 50
                maximo = 0
                i = 0
        #encontra o valor máximo e mínimo global com a leitura de todos os vetores max e min segmentados.
        #e escreve dentro de um novo vetorVolta que vai ser enviado para o send
        else:
            if i % 1000 == 0:                
                print(" [x] Estou no vetor %d" % i)
            if maximo < vetor[-1]:
                maximo = vetor[-1]
            if minimo > vetor[0]:
                minimo = vetor[0]
            vetorVolta = [ minimo, maximo ]
            i += 1
    #consume os dados da fila hello
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