#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FRUTAS 100

typedef struct {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
} Fruta;

Fruta* frutas[MAX_FRUTAS];
int totalFrutas = 0;

int buscarFruta(int codigo) {
    for (int i = 0; i < totalFrutas; i++) {
        if (frutas[i]->codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void cadastrarFruta() {
    if (totalFrutas >= MAX_FRUTAS) {
        printf("Limite de frutas atingido.\n");
        return;
    }

    int codigo;
    printf("Digite o código da fruta: ");
    scanf("%d", &codigo);

    if (buscarFruta(codigo) != -1) {
        printf("Código já existente.\n");
        return;
    }

    Fruta* fruta = (Fruta*)malloc(sizeof(Fruta));
    fruta->codigo = codigo;

    printf("Digite o nome da fruta: ");
    scanf("%s", fruta->nome);
    printf("Digite a quantidade: ");
    scanf("%d", &fruta->quantidade);
    printf("Digite o preço: ");
    scanf("%f", &fruta->preco);

    frutas[totalFrutas++] = fruta;
    printf("Fruta cadastrada com sucesso!\n");
}

void listarFrutas() {
    if (totalFrutas == 0) {
        printf("Nenhuma fruta cadastrada.\n");
        return;
    }

    for (int i = 0; i < totalFrutas; i++) {
        printf("Código: %d, Nome: %s, Quantidade: %d, Preço: %.2f\n",
               frutas[i]->codigo, frutas[i]->nome, frutas[i]->quantidade, frutas[i]->preco);
    }
}

void buscarFrutaPorCodigo() {
    int codigo;
    printf("Digite o código da fruta: ");
    scanf("%d", &codigo);

    int indice = buscarFruta(codigo);
    if (indice != -1) {
        Fruta* fruta = frutas[indice];
        printf("Código: %d, Nome: %s, Quantidade: %d, Preço: %.2f\n",
               fruta->codigo, fruta->nome, fruta->quantidade, fruta->preco);
    } else {
        printf("Fruta não encontrada.\n");
    }
}

void alterarFruta() {
    int codigo;
    printf("Digite o código da fruta para alterar: ");
    scanf("%d", &codigo);

    int indice = buscarFruta(codigo);
    if (indice != -1) {
        printf("Digite o novo nome: ");
        scanf("%s", frutas[indice]->nome);
        printf("Digite a nova quantidade: ");
        scanf("%d", &frutas[indice]->quantidade);
        printf("Digite o novo preço: ");
        scanf("%f", &frutas[indice]->preco);
        printf("Fruta alterada com sucesso!\n");
    } else {
        printf("Fruta não encontrada.\n");
    }
}

void excluirFruta() {
    int codigo;
    printf("Digite o código da fruta para excluir: ");
    scanf("%d", &codigo);

    int indice = buscarFruta(codigo);
    if (indice != -1) {
        if (frutas[indice]->quantidade > 0) {
            printf("A fruta ainda tem estoque e não pode ser excluída.\n");
            return;
        }
        free(frutas[indice]);
        for (int i = indice; i < totalFrutas - 1; i++) {
            frutas[i] = frutas[i + 1];
        }
        totalFrutas--;
        printf("Fruta excluída com sucesso!\n");
    } else {
        printf("Fruta não encontrada.\n");
    }
}

void venderFruta() {
    int codigo, quantidade;
    printf("Digite o código da fruta: ");
    scanf("%d", &codigo);

    int indice = buscarFruta(codigo);
    if (indice != -1) {
        printf("Digite a quantidade para vender: ");
        scanf("%d", &quantidade);

        if (frutas[indice]->quantidade >= quantidade) {
            frutas[indice]->quantidade -= quantidade;
            FILE *file = fopen("vendas.txt", "a");
            fprintf(file, "Fruta: %s, Quantidade vendida: %d\n", frutas[indice]->nome, quantidade);
            fclose(file);
            printf("Venda realizada!\n");
        } else {
            printf("Quantidade insuficiente em estoque.\n");
        }
    } else {
        printf("Fruta não encontrada.\n");
    }
}

int main() {
    int opcao;

    do {
        printf("\n1. Cadastrar fruta\n2. Listar frutas\n3. Buscar fruta\n4. Alterar fruta\n5. Excluir fruta\n6. Vender fruta\n7. Sair\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarFruta();
                break;
            case 2:
                listarFrutas();
                break;
            case 3:
                buscarFrutaPorCodigo();
                break;
            case 4:
                alterarFruta();
                break;
            case 5:
                excluirFruta();
                break;
            case 6:
                venderFruta();
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 7);

    for (int i = 0; i < totalFrutas; i++) {
        free(frutas[i]);
    }

    return 0;
}
