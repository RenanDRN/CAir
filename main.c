#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodo {
    int nVoo;
    char companhia[20];
    char destino[80];
    int nPortao;
    time_t horaPrevista; //dá pra usar também uma struct com hora e minuto, ver o que prefere
    time_t horaDecolagem; //dá pra usar também uma struct com hora e minuto, ver o que prefere
    char status[15];
    struct nodo *prox;
} *ptr

void incluirVoo(ptr *lista) {

}

void excluirVoo(ptr *lista) {
    
}

void alterarStatus(ptr *lista) {
    
}

void alterarDetalhes(ptr *lista){
    
}

void exibirLista(ptr *lista) {
    
}

int main()
{
    

    return 0;
}