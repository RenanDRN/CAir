#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct Voo
{
    int nVoo;
    char companhia[20];
    char destino[80];
    int nPortao;
    struct tm *horaDecolagem; // dá pra usar também uma struct com hora e minuto, ver o que prefere
    char status[15];
    struct Voo *prox;
} Voo;

Voo *inicio = NULL;
int qtdVoo = 1;

struct tm *obterDataHorainicio()
{
    time_t agora = time(NULL);
    struct tm *dataHorainicio = malloc(sizeof(struct tm)); // Aloca memória para a estrutura
    *dataHorainicio = *localtime(&agora);                  // Copia os dados de localtime para a nova estrutura
    return dataHorainicio;
}

void ordenaVoo(Voo voo)
{
    Voo *novo = malloc(sizeof(Voo));
    *novo = voo;
    novo->prox = NULL;

    // Se a lista estiver vazia ou o novo voo deve ser o primeiro
    if (inicio == NULL ||
        (voo.horaDecolagem->tm_hour < inicio->horaDecolagem->tm_hour) ||
        (voo.horaDecolagem->tm_hour == inicio->horaDecolagem->tm_hour && voo.horaDecolagem->tm_min < inicio->horaDecolagem->tm_min))
    {
        novo->prox = inicio;
        inicio = novo;
        return;
    }

    Voo *atual = inicio;
    while (atual->prox != NULL &&
           (atual->prox->horaDecolagem->tm_hour < voo.horaDecolagem->tm_hour ||
            (atual->prox->horaDecolagem->tm_hour == voo.horaDecolagem->tm_hour &&
             atual->prox->horaDecolagem->tm_min < voo.horaDecolagem->tm_min)))
    {
        atual = atual->prox;
    }

    novo->prox = atual->prox;
    atual->prox = novo;
}

void incluirVoo()
{
    Voo *voo = malloc(sizeof(Voo));
    if (voo == NULL)
    {
        printf("Erro ao alocar memória para o voo.\n");
    }

    voo->nVoo = qtdVoo;
    printf("Digite o destino do voo: \n");
    scanf("%79s", voo->destino);

    printf("Digite o numero do portao: \n");
    scanf("%d", &voo->nPortao);

    int hora, minuto;
    printf("Digite o horario de embarque (formato HH:MM): \n");
    scanf("%d:%d", &hora, &minuto);
    voo->horaDecolagem = obterDataHorainicio();
    voo->horaDecolagem->tm_hour = hora;
    voo->horaDecolagem->tm_min = minuto;

    printf("Digite o nome da companhia: \n");
    scanf("%19s", voo->companhia);

    printf("Digite o status do voo: \n");
    scanf("%14s", voo->status);

    voo->prox = NULL;
    // Se a lista estiver vazia, o novo voo é o primeiro
    if (inicio == NULL)
        inicio = voo;
    else
    {
        ordenaVoo(*voo);
        // Voo *atual = inicio;
        // while (atual->prox != NULL)
        // {
        //     atual = atual->prox; // Percorre até o final da lista
        // }
        // atual->prox = voo; // Adiciona o novo voo ao final da lista
    }
    qtdVoo++;
}

Voo *obterVoo()
{
    int idVoo;
    printf("Digite o ID do voo: ");
    scanf("%d", &idVoo);

    Voo *atual = inicio;
    while (atual != NULL)
    {
        if (atual->nVoo == idVoo)
        {
            return atual;
        }
        atual = atual->prox;
    }
    // Se o voo não for encontrado, exibe uma mensagem
    printf("Voo com ID %d nao encontrado.\n", idVoo);
    return NULL;
}

void alterarDetalhes()
{
    Voo *voo = obterVoo();

    int opcao = -1;
    while (opcao != 0)
    {
        system("cls || clear");
        printf("### Alterar Voo ###\n");
        printf(" 0 - Voltar para menu anterior\n");
        printf(" 1 - Alterar Status\n");
        printf(" 2 - Alterar Horario de Decolagem\n");
        printf(" 3 - Alterar Numero do portao\n");
        printf(" 4 - Alterar Destino\n");
        printf(" Digite a opcao desejada:  ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            printf("Digite o novo status: ");
            scanf("%14s", voo->status);
            break;
        case 2:
            printf("Digite a nova hora prevista de chegada (formato HH:MM): \n");
            int hora, minuto;
            scanf("%d:%d", &hora, &minuto);
            voo->horaDecolagem->tm_hour = hora;
            voo->horaDecolagem->tm_min = minuto;
            // implementar a lógica para ordenar os voos por hora de decolagem
            ordenaVoo(*voo);
            break;

        case 3:
            printf("Digite o novo numero do portao: ");
            scanf("%d", &voo->nPortao);
            break;
        case 4:
            printf("Digite o novo destino: ");
            scanf("%79s", voo->destino);
            break;
        case 0:
            opcao = 0;
            break;
        default:
            break;
        }
    }
}

void exibirVoos()
{
    if (inicio == NULL)
        printf("#### Nao ha voos programados ####\n");
    else
    {
        Voo *atual = inicio;
        printf("\n|------------------------- Painel de Voos CAir --------------------------|\n");
        printf("|  VOO  | Horario  |      Destino       |   CIA   | Portao |   Status    |\n");
        printf("|------------------------------------------------------------------------|\n");
        while (atual != NULL)
        {
            printf("| %5d | %02dh%02dm   | %-18s | %-7s | %6d | %-11s |\n",
                   atual->nVoo,
                   atual->horaDecolagem->tm_hour,
                   atual->horaDecolagem->tm_min,
                   atual->destino,
                   atual->companhia,
                   atual->nPortao,
                   atual->status);
            printf("|------------------------------------------------------------------------|\n");

            atual = atual->prox;
        }
    }
}

void excluirVoo()
{
    Voo *voo = obterVoo();
    if (voo == NULL)
    {
        printf("Voo nao encontrado.\n");
        return;
    }

    if (inicio == voo)
    {
        inicio = voo->prox;
    }
    else
    {
        // Caso o voo a ser removido esteja no meio ou no final da lista
        Voo *anterior = inicio;
        while (anterior->prox != voo)
        {
            anterior = anterior->prox;
        }
        anterior->prox = voo->prox;
    }

    free(voo->horaDecolagem);
    free(voo);
    printf("Voo excluido com sucesso.\n");
}

int main(int argc, char const *argv[])
{
    int opcao = -1;
    printf("## Bem-vindo ao Painel de Voos CAir! ##\n");
    while (opcao != 0)
    {
        system("cls || clear");
        exibirVoos();

        printf("\n-------------- Menu de Opcoes --------------\n");
        printf(" 0 - Encerrar Painel\n");
        printf(" 1 - Incluir Voo\n");
        printf(" 2 - Alterar Voo\n");
        printf(" 3 - Excluir Voo\n");
        printf(" Digite a opcao desejada:  ");
        scanf("%d", &opcao);
        system("cls || clear");
        switch (opcao)
        {
        case 1:
            incluirVoo();
            break;
        case 2:
        {
            alterarDetalhes();
            break;
        }
        break;
        case 3:
            excluirVoo();
            break;

        case 0:
            opcao = 0;
            break;
        }
    }
    return 0;
}
