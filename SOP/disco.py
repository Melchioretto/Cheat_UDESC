from email.policy import strict
import numpy as np

lista = open("arq.txt","r",encoding = 'UTF-8')
inicial=[]
numero=[]
tipo=[]
usado=[]
indexlist=[] # utilizei para marcar posição do bloco inicial
aux = 1
flag = 0
for linha in lista:
    read = linha.split()
    inicial.append(int(read[0]))
    numero.append(int(read[1]))
    tipo.append(str(read[2]))
    usado.append(0)
indexlist = inicial
inicial = sorted(inicial)
for n in range(len(inicial)):
    indexlist = np.array(indexlist)# aqui eu estou fazendo com que possa ser buscado com o valor que está salvo no array
    atual = np.where(indexlist == inicial[n])#aqui é a sequencia
    atual = int(atual[0])
    # print("atual")
    # print(indexlist[atual], numero[atual], tipo[atual], usado[atual])
    if usado[atual] == 1:#usando isso pq o pop() tava zoado
        continue
    aux = inicial[n] + numero[atual]#aux é o iniciial + blocos
    aux2 = numero[atual]#aux2 guarda o numero de blocos 

    for i in range(len(inicial)):

        atual2 = np.where(indexlist == inicial[i])
        atual2 = int(atual2[0])
        if (aux) == inicial[i] and tipo[atual] == tipo[atual2] and (aux + numero[atual2]) < 65: 
                atual2 = np.where(indexlist == inicial[i])
                atual2 = int(atual2[0])
                aux = inicial[i] + numero[atual2]
                aux2 += numero[atual2]
                usado[atual2] = 1
        if inicial[i] <= aux and inicial[i] >= inicial[n] and tipo[atual] == tipo[atual2] and (aux2 + numero[atual2]) < 65 and tipo[atual] =="r":
                atual2 = np.where(indexlist == inicial[i])
                atual2 = int(atual2[0])
                aux3 = aux - inicial[i]
                aux = inicial[i] + numero[atual2]
                aux2 += (numero[atual2])
                aux2 -= (aux3)
                usado[atual2] = 1
    print(inicial[n], aux2, tipo[atual])

           
lista.close()