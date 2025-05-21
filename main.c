#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    printf("Digite a hora prevista de chegada (formato HH:MM): \n");
    scanf("%d:%d", &hora, &minuto);
    voo->horaDecolagem = obterDataHorainicio();
    voo->horaDecolagem->tm_hour = hora;
    voo->horaDecolagem->tm_min = minuto;

    printf("Digite o nome da companhia: \n");
    scanf("%19s", voo->companhia);

    printf("Digite o status do voo: \n");
    scanf("%14s", voo->status);

    voo->prox = NULL;
    if (inicio == NULL)
    {
        inicio = voo; // Se a lista estiver vazia, o novo voo é o primeiro
    }
    else
    {
        Voo *atual = inicio;
        while (atual->prox != NULL)
        {
            atual = atual->prox; // Percorre até o final da lista
        }
        atual->prox = voo; // Adiciona o novo voo ao final da lista
    }
    qtdVoo++;
}

// void excluirVoo(Voo *lista)
// {
//     if (inicio != NULL)
//     {
//         Paciente *aux = inicio;
//         inicio = inicio->prox;
//         printf("Paciente %s atendido com sucesso!", aux->nome);
//         free(aux);
//         if (inicio == NULL)
//             fim = NULL;
//     }
// }

void alterarDetalhes(Voo *lista)
{
    int opcao = 0;
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
        // alterar status
        break;
    case 2:
        // alterar hrDecolagem
        break;

    case 3:
        // alterar portao
        break;
    case 4:
        // alterar destino
        break;
    case 0:
        opcao = 0;
        break;
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

void reorganizarVoo()
{
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
        switch (opcao)
        {
        case 1:
            system("cls || clear");
            incluirVoo();
            break;

        case 2:

            break;

        case 3:

            break;

        case 0:
            opcao = 0;
            break;
        }
    }
    return 0;
}
