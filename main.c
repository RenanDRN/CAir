#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

typedef struct Voo
{
    int nVoo;
    char companhia[40];
    char destino[80];
    int nPortao;
    struct tm *horaEmbarque;
    char status[30];
    struct Voo *prox;
} Voo;

// Inicializa os prototipos das funções para poderem ser usadas antes de serem definidas

Voo *obterVoo();
void exibirVoo(Voo *);

// inicializa a lista encadeada de voos inicio como vazia
Voo *inicio = NULL;

/// @brief
///  Função para obter a data e hora atual, alocando memória para a estrutura tm
/// @return Data e Hora atual
struct tm *obterDataHorainicio()
{
    time_t agora = time(NULL);
    struct tm *dataHorainicio = malloc(sizeof(struct tm)); // Aloca memória para a estrutura
    *dataHorainicio = *localtime(&agora);                  // Copia os dados de localtime para a nova estrutura
    return dataHorainicio;
}

/// @brief
///  Função auxiliar para ordenar os voos em ordem de chegada de embarque
/// @return
void ordenaVoo(Voo *voo)
{
    // Remove o voo da lista, se já estiver nela
    if (inicio == voo)
    {
        inicio = voo->prox;
    }
    else
    {
        Voo *anterior = inicio;
        while (anterior && anterior->prox != voo)
        {
            anterior = anterior->prox;
        }
        if (anterior && anterior->prox == voo)
        {
            anterior->prox = voo->prox;
        }
    }
    voo->prox = NULL;

    // Caso especial: lista vazia ou voo deve ser o primeiro
    if (inicio == NULL ||
        voo->horaEmbarque->tm_hour < inicio->horaEmbarque->tm_hour ||
        (voo->horaEmbarque->tm_hour == inicio->horaEmbarque->tm_hour &&
         voo->horaEmbarque->tm_min < inicio->horaEmbarque->tm_min))
    {
        voo->prox = inicio;
        inicio = voo;
        return;
    }

    // Busca a posição correta para inserir o voo
    Voo *atual = inicio;

    if (atual == NULL)
    {
        voo->prox = inicio;
        inicio = voo;
        return;
    }

    while (atual->prox != NULL)
    {
        int h1 = atual->prox->horaEmbarque->tm_hour;
        int m1 = atual->prox->horaEmbarque->tm_min;
        int h2 = voo->horaEmbarque->tm_hour;
        int m2 = voo->horaEmbarque->tm_min;

        if (h1 > h2 || (h1 == h2 && m1 >= m2))
        {
            break;
        }
        atual = atual->prox;
    }

    // Insere o voo na posição encontrada
    voo->prox = atual->prox;
    atual->prox = voo;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/// @brief
///  Função auxiliar para incluir um novo voo na lista de voos ja ordenado por ordem de embarque.
void incluirVoo()
{
    // Inicializacao da lista de voos com input do usuario
    Voo *voo = malloc(sizeof(Voo));
    if (voo == NULL)
    {
        printf("Erro ao alocar memória para o voo.\n");
    }

    int idValido = 0;
    while (!idValido) {
        printf("\033[1;36mDigite o ID do voo: \033[0m\n");
        scanf("%d", &voo->nVoo);
        limparBuffer();

        // Verifica se já existe um voo com esse ID
        Voo *atual = inicio;
        idValido = 1;
        while (atual != NULL) {
            if (atual->nVoo == voo->nVoo) {
                system("cls || clear");
                printf("Voo %d ja existente!\n", voo->nVoo);
                idValido = 0;
                break;
            }
            atual = atual->prox;
        }
    }

    printf("\n\033[1;36mDigite o destino: \033[0m\n");
    gets(voo->destino);
    /*fgets(voo->destino, sizeof(voo->destino), stdin);
    voo->destino[strcspn(voo->destino, "\n")] = '\0';*/

    printf("\n\033[1;36mDigite o numero do portao: \033[0m\n");
    scanf("%d", &voo->nPortao);
    limparBuffer();

    int hora, minuto;
    printf("\n\033[1;36mDigite o horario de embarque (formato HH:MM): \033[0m\n");
    scanf("%d:%d", &hora, &minuto);
    limparBuffer();
    voo->horaEmbarque = obterDataHorainicio();
    voo->horaEmbarque->tm_hour = hora;
    voo->horaEmbarque->tm_min = minuto;

    printf("\n\033[1;36mDigite o nome da companhia: \033[0m\n");
    gets(voo->companhia);
    /*fgets(voo->companhia, sizeof(voo->companhia), stdin);
    voo->companhia[strcspn(voo->companhia, "\n")] = '\0';*/

    printf("\n\033[1;36mIndique o status do voo: \033[0m\n");
	printf("\033[1;36m 1 -\033[0m \033[1;0mPREVISTO\033[0m\n");
	printf("\033[1;36m 2 -\033[0m \033[1;34mEM SOLO\033[0m\n");
	printf("\033[1;36m 3 -\033[0m \033[1;32mEMBARQUE\033[0m\n");
	printf("\033[1;36m 4 -\033[0m \033[1;33mATRASADO\033[0m\n");
	printf("\033[1;36m 5 -\033[0m \033[1;35mDECOLADO\033[0m\n");
	printf("\033[1;36m 6 -\033[0m \033[1;31mCANCELADO\033[0m\n");

	int opcao = -1;
	scanf("%d", &opcao);
    limparBuffer();

	switch (opcao)
	{
	case 1:
		strcpy(voo->status, "PREVISTO");
		opcao = 0;
		break;

	case 2:
		strcpy(voo->status, "EM SOLO");
		opcao = 0;
		break;

	case 3:
		strcpy(voo->status, "EMBARQUE");
		opcao = 0;
		break;

	case 4:
		strcpy(voo->status, "ATRASADO");
		opcao = 0;
		break;

	case 5:
		strcpy(voo->status, "DECOLADO");
		opcao = 0;
		break;

	case 6:
		strcpy(voo->status, "CANCELADO");
		opcao = 0;
		break;

	case 0:
		opcao = 0;
		break;

	default:
		break;
	}

    voo->prox = NULL;
    // Se a lista estiver vazia, o novo voo é o primeiro. Caso contrário, insere na posição correta
    if (inicio == NULL)
        inicio = voo;
    else
        ordenaVoo(voo);
    limparBuffer();
}

/// @brief
/// Função para obter um voo específico pelo ID.
/// @return voo específico ou NULL se não encontrado.
Voo *obterVoo()
{
    int idVoo;
    exibirPainel();
    printf("\033[1;36mDigite o ID do voo: \033[0m");
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
    // printf("Voo com ID %d nao encontrado.\n", idVoo);
    return NULL;
}

/// @brief
/// Função para alterar os detalhes de um voo específico.
void alterarDetalhes()
{
    Voo *voo = obterVoo();
    int opcao = -1;
    while (opcao != 0)
    {
        system("cls || clear");

        printf("|--------------------------------------- \033[1;32m### Alterar Voo ###\033[0m -----------------------------------------------------|\n");
        exibirVoo(voo);
        printf("|-----------------------------------------------------------------------------------------------------------------|\n");

        printf("\n \033[1;36m0 - Voltar para menu anterior\n");
        printf(" 1 - Alterar Status\n");
        printf(" 2 - Alterar Horario de Embarque\n");
        printf(" 3 - Alterar Numero do portao\n");
        printf(" 4 - Alterar Destino\n");
        printf(" 5 - Alterar Companhia\033[0m\n");
        printf(" \033[1;33mDigite a opcao desejada:  \033[0m");
        scanf("%d", &opcao);
        limparBuffer();
        switch (opcao)
        {
        case 1:
            system("cls || clear");
            printf("\033[1;36mIndique o status do voo: \033[0m\n");
            printf("\033[1;36m 1 -\033[0m \033[1;0mPREVISTO\033[0m\n");
            printf("\033[1;36m 2 -\033[0m \033[1;34mEM SOLO\033[0m\n");
            printf("\033[1;36m 3 -\033[0m \033[1;32mEMBARQUE\033[0m\n");
            printf("\033[1;36m 4 -\033[0m \033[1;33mATRASADO\033[0m\n");
            printf("\033[1;36m 5 -\033[0m \033[1;35mDECOLADO\033[0m\n");
            printf("\033[1;36m 6 -\033[0m \033[1;31mCANCELADO\033[0m\n");
        
            int opcao = -1;
            scanf("%d", &opcao);
            limparBuffer();
        
            switch (opcao)
            {
            case 1:
                strcpy(voo->status, "PREVISTO");
                opcao = 0;
                break;
        
            case 2:
                strcpy(voo->status, "EM SOLO");
                opcao = 0;
                break;
        
            case 3:
                strcpy(voo->status, "EMBARQUE");
                opcao = 0;
                break;
        
            case 4:
                strcpy(voo->status, "ATRASADO");
                opcao = 0;
                break;
        
            case 5:
                strcpy(voo->status, "DECOLADO");
                opcao = 0;
                break;
        
            case 6:
                strcpy(voo->status, "CANCELADO");
                opcao = 0;
                break;
        
            case 0:
                opcao = 0;
                break;
        
            default:
                break;
            }
            opcao = 0;
            break;

        case 2:
            system("cls || clear");
            printf("\033[1;36mDigite a nova hora prevista de Embarque (formato HH:MM): \033[0m\n");
            int hora, minuto;
            scanf("%d:%d", &hora, &minuto);
            limparBuffer();
            voo->horaEmbarque->tm_hour = hora;
            voo->horaEmbarque->tm_min = minuto;
            ordenaVoo(voo);
            opcao = 0;
            break;

        case 3:
            system("cls || clear");
            printf("\033[1;36mDigite o novo numero do portao: \033[0m");
            scanf("%d", &voo->nPortao);
            limparBuffer();
            opcao = 0;
            break;

        case 4:
            system("cls || clear");
            printf("\033[1;36mDigite o novo destino: \033[0m");
            gets(voo->destino);
            /*fgets(voo->destino, sizeof(voo->destino), stdin);
            voo->destino[strcspn(voo->destino, "\n")] = '\0';*/
            opcao = 0;
            break;

        case 5:
            system("cls || clear");
            printf("\033[1;36mDigite a nova companhia: \033[0m");
            gets(voo->companhia);
            /*fgets(voo->companhia, sizeof(voo->companhia), stdin);
            voo->companhia[strcspn(voo->companhia, "\n")] = '\0';*/
            opcao = 0;
            break;

        case 0:
            opcao = 0;
            break;
        default:
            break;
        }
    }
}

/// @brief
/// Função para exibir na tela do usuário detalhes de um voo.
/// @param voo Voo especifico a ser exibido
void exibirVoo(Voo *voo)
{
    if (voo == NULL)
    {
        printf("\033[1;33mVoo nao encontrado.\033[0m\n");
        return;
    }

    // Determina cor do status
    char *corStatus;
    if (strcmp(voo->status, "PREVISTO") == 0)
        corStatus = "\033[1;0m"; // padrão
    else if (strcmp(voo->status, "EM SOLO") == 0)
        corStatus = "\033[1;34m"; // azul
    else if (strcmp(voo->status, "EMBARQUE") == 0)
        corStatus = "\033[1;32m"; // verde
    else if (strcmp(voo->status, "ATRASADO") == 0)
        corStatus = "\033[1;33m"; // amarelo
    else if (strcmp(voo->status, "DECOLADO") == 0)
        corStatus = "\033[1;35m"; // magenta
    else if (strcmp(voo->status, "CANCELADO") == 0)
        corStatus = "\033[1;31m"; // vermelho
    else
        corStatus = "\033[0m"; // fallback padrão

    printf("| \033[1;0m%5d\033[0m | \033[1;0m%02dh%02dm\033[0m   | \033[1;0m%-26s\033[0m | \033[1;0m%-30s\033[0m | \033[1;0m%6d\033[0m | %s%-21s\033[0m |\n",
        voo->nVoo,
        voo->horaEmbarque->tm_hour,
        voo->horaEmbarque->tm_min,
        voo->destino,
        voo->companhia,
        voo->nPortao,
        corStatus, voo->status);
}

/// @brief
/// Função para excluir um voo específico da lista de voos.
void excluirVoo()
{
    Voo *voo = obterVoo();
    if (voo == NULL)
    {
        printf("\033[1;33mVoo nao encontrado.\033[0m\n");
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

    free(voo->horaEmbarque);
    free(voo);
    printf("\033[1;33mVoo excluido com sucesso.\033[0m\n");
}

/// @brief
/// Função responsavel por exibir todos as informações do voos programados no painel.
void exibirPainel()
{
    if (inicio == NULL)
        printf("\033[1;33m#### Nao ha voos programados ####\033[0m\n");
    else
    {
        Voo *atual = inicio;
        printf("\n|------------------------------------------ \033[1;32mPAINEL DE VOOS | CAir\033[0m ------------------------------------------------|\n");
        printf("|  \033[1;33mVOO\033[0m  | \033[1;33mHorario\033[0m  |          \033[1;33mDestino\033[0m           |               \033[1;33mCIA\033[0m              | \033[1;33mPortao\033[0m |          \033[1;33mStatus\033[0m       |\n");
        printf("|-----------------------------------------------------------------------------------------------------------------|\n");
        while (atual != NULL)
        {
            exibirVoo(atual);
            printf("|-----------------------------------------------------------------------------------------------------------------|\n");
            atual = atual->prox;
        }
    }
}

/// @brief
///  Metodo principal do programa, que exibe o menu de opções e permite ao usuário interagir com o sistema de voos.
int main(void)
{
    int opcao = -1;
    printf("\033[1;36m## Bem-vindo ao Painel de Voos CAir! ##\033[0m\n");
    while (opcao != 0)
    {
        system("cls || clear");
        exibirPainel();

        printf("\n-------------- \033[1;36mMenu de Opcoes\033[0m --------------\n");
        printf(" \033[1;36m0 - Encerrar Painel\n");
        printf(" 1 - Incluir Voo\n");
        printf(" 2 - Alterar Voo\n");
        printf(" 3 - Excluir Voo\033[0m\n");
        printf(" \033[1;33mDigite a opcao desejada:  \033[0m");
        scanf("%d", &opcao);
        limparBuffer();
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
            printf("\033[1;33mObrigado por voar conosco!\033[0m\n\n");
            break;
        }
    }
    return 0;
}