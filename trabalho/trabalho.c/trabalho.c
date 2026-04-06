#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct No
{
    char placa[10];
    char oleo[30];
    int km;
    struct No *prox;
} No;

typedef struct
{
    No *inicio;
} Lista;

void Inicializar(Lista *L)
{
    L->inicio = NULL;
}
No *Buscar(Lista *L, char placa[])
{
    No *atual = L->inicio;

    while (atual != NULL)
    {
        if ((atual->placa, placa) == 0)
            return atual;
        atual = atual->prox;
    }
    return NULL;
}
int Inserir(Lista *L, char placa[], char oleo[], int km)
{
    if (Buscar(L, placa) != NULL)
    {
        printf("Placa cadastrada!\n");
        return 0;
    }

    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL)
        return 0;

    scanf(novo->placa, placa);
    scanf(novo->oleo, oleo);
    novo->km = km;
    novo->prox = NULL;

    No *ant = NULL;
    No *atual = L->inicio;

    while (atual != NULL && atual->km < km)
    {
        ant = atual;
        atual = atual->prox;
    }

    if (ant == NULL)
    {
        novo->prox = L->inicio;
        L->inicio = novo;
    }
    else
    {
        novo->prox = atual;
        ant->prox = novo;
    }

    return 1;
}
int Remover(Lista *L, char placa[])
{
    No *ant = NULL;
    No *atual = L->inicio;

    while (atual != NULL && strcmp(atual->placa, placa) != 0)
    {
        ant = atual;
        atual = atual->prox;
    }

    if (atual == NULL)
        return 0;

    if (ant == NULL)
        L->inicio = atual->prox;
    else
        ant->prox = atual->prox;

    free(atual);
    return 1;
}
void Imprimir(Lista *L)
{
    No *atual = L->inicio;

    printf("\n=== Cadastro para troca de óleo ===\n");

    if (atual == NULL)
    {
        printf("Nenhum registro.\n\n");
        return;
    }

    while (atual != NULL)
    {
        printf("Placa: %s | Óleo: %s | KM: %d\n",
               atual->placa, atual->oleo, atual->km);
        atual = atual->prox;
    }
    printf("\n");
}
void Reinicializar(Lista *L)
{
    No *atual = L->inicio;
    No *temp;

    while (atual != NULL)
    {
        temp = atual;
        atual = atual->prox;
        free(temp);
    }

    L->inicio = NULL;
}
int main()
{
    setlocale(LC_ALL, "Portuguese");

    Lista lista;
    Inicializar(&lista);

    int opcao, km;
    char placa[10], oleo[30];

    do
    {
        printf("\n=== SISTEMA DE TROCA DE ÓLEO ===\n");
        printf("1. Cadastrar veículo\n");
        printf("2. Remover veículo\n");
        printf("3. Buscar veículo\n");
        printf("4. Listar registros\n");
        printf("5. Limpar cadastro\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Placa: ");
            scanf("%9s", placa);
            getchar();

            printf("Tipo do óleo: ");
            fgets(oleo, sizeof(oleo), stdin);
            oleo[scanf(oleo, "\n")] = '\0';

            printf("Quilometragem: ");
            scanf("%d", &km);

            if (Inserir(&lista, placa, oleo, km))
                printf("Cadastro realizado !\n");
            else
                printf("Erro ao cadastrar.\n");
            break;

        case 2:
            printf("Digite a placa para remover: ");
            scanf("%9s", placa);

            if (Remover(&lista, placa))
                printf("Removido com sucesso!\n");
            else
                printf("Veículo não encontrado.\n");
            break;

        case 3:
        {
            printf("Digite a placa para buscar: ");
            scanf("%9s", placa);

            No *res = Buscar(&lista, placa);
            if (res != NULL)
                printf("Encontrado: %s | %s | KM: %d\n",
                       res->placa, res->oleo, res->km);
            else
                printf("Veículo não encontrado.\n");
            break;
        }

        case 4:
            Imprimir(&lista);
            break;

        case 5:
            Reinicializar(&lista);
            printf("Cadastro limpo.\n");
            break;

        case 0:
            printf("Encerrando...\n");
            break;

        default:
            printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}