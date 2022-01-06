from math import prod, sqrt

lista = [1,1,1,1,1,1,1,1,1]         #sequencia finita
tamanho = len(lista)        #tamanho da lista

numero = 23                 # é igual ao intervalo de [0 a numero] que vai ser considerado para encontrar os primos
aux = 0
aux1 = 0
primos = []                     

while numero > 1:           #função que verifica se o numero dentro do intervalo é primo e se for adiciona na lista de primos
    aux = sqrt(numero)
    aux = int(aux)
    aux1 = 0
    while aux >= 2:
        if numero%aux == 0:
            aux1 += 1
        if aux == 2:
            if aux1 == 0:
                primos.append(numero)
        aux -= 1
    numero -=1

primos.append(3)
primos.append(2)

primos = primos[::-1]   #inverto a lista 

print(lista)            #printo a sequencia
print(primos)           #printo os primos

s = []                  # s é a lista que vai armazenar os valores de cada potenciação

for primos, lista in zip(primos,lista):     #Esta função retorna uma lista de tuplas, onde a i-ésima tupla contém o i-ésimo elemento de cada um dos argumentos.
    s.append(primos**lista)                 #realizar a operação entre os valores da lista de primos e lista

print(s)

produto = prod(s)       #produto é o natural que codifica a sequencia da lista passada

print(produto)


