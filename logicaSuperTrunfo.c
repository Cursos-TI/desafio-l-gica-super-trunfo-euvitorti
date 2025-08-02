#include <stdio.h>
#include <string.h>

// Definição da estrutura Carta
typedef struct
{
    char estado[50];      // Estado da cidade
    int codigo;           // Código único da carta
    char nome[50];        // Nome da cidade
    long populacao;       // População
    double area;          // Área em km²
    double pib;           // PIB em bilhões
    int pontosTuristicos; // Número de pontos turísticos
} Carta;

void nivelNovato();
void nivelAventureiro();
void nivelMestre();
Carta cadastrarCarta();
void mostrarCarta(const Carta *c);
double densidade(const Carta *c);
int comparaAtributo(const Carta *c1, const Carta *c2, int escolha);

int main()
{
    int opcao;
    printf("=== Super Trunfo - Países ===\n");
    printf("Escolha o nível para jogar:\n");
    printf("1. Novato\n2. Aventureiro\n3. Mestre\n");
    printf("Opção: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao)
    {
    case 1:
        nivelNovato();
        break;
    case 2:
        nivelAventureiro();
        break;
    case 3:
        nivelMestre();
        break;
    default:
        printf("Opção inválida!\n");
    }
    return 0;
}

Carta cadastrarCarta()
{
    Carta c;
    printf("Estado: ");
    fgets(c.estado, sizeof(c.estado), stdin);
    c.estado[strcspn(c.estado, "\n")] = '\0';
    printf("Código (int): ");
    scanf("%d", &c.codigo);
    getchar();
    printf("Nome da cidade: ");
    fgets(c.nome, sizeof(c.nome), stdin);
    c.nome[strcspn(c.nome, "\n")] = '\0';
    printf("População: ");
    scanf("%ld", &c.populacao);
    getchar();
    printf("Área (km²): ");
    scanf("%lf", &c.area);
    getchar();
    printf("PIB (bi): ");
    scanf("%lf", &c.pib);
    getchar();
    printf("Pontos turísticos: ");
    scanf("%d", &c.pontosTuristicos);
    getchar();
    return c;
}

void mostrarCarta(const Carta *c)
{
    printf("\n--- Carta %d ---\n", c->codigo);
    printf("Estado: %s\n", c->estado);
    printf("Cidade: %s\n", c->nome);
    printf("População: %ld\n", c->populacao);
    printf("Área: %.2f km²\n", c->area);
    printf("Densidade: %.2f hab/km²\n", densidade(c));
    printf("PIB: %.2f bi\n", c->pib);
    printf("Pontos turísticos: %d\n", c->pontosTuristicos);
}

double densidade(const Carta *c)
{
    return c->area > 0 ? (double)c->populacao / c->area : 0.0;
}

// retorna  1 se c1 vence, -1 se c2 vence, 0 empate
int comparaAtributo(const Carta *c1, const Carta *c2, int escolha)
{
    double v1, v2;
    int inverso = 0; // se 1, menor vence
    switch (escolha)
    {
    case 1:
        v1 = c1->populacao;
        v2 = c2->populacao;
        break;
    case 2:
        v1 = c1->area;
        v2 = c2->area;
        break;
    case 3:
        v1 = c1->pib;
        v2 = c2->pib;
        break;
    case 4:
        v1 = c1->pontosTuristicos;
        v2 = c2->pontosTuristicos;
        break;
    case 5:
        v1 = densidade(c1);
        v2 = densidade(c2);
        inverso = 1;
        break;
    default:
        return 0;
    }
    if (v1 == v2)
        return 0;
    if (inverso)
        return v1 < v2 ? 1 : -1;
    else
        return v1 > v2 ? 1 : -1;
}

void nivelNovato()
{
    printf("\n-- Nível Novato --\n");
    printf("Cadastre a Carta 1:\n");
    Carta c1 = cadastrarCarta();
    printf("Cadastre a Carta 2:\n");
    Carta c2 = cadastrarCarta();
    mostrarCarta(&c1);
    mostrarCarta(&c2);

    // hardcode: comparar densidade (menor vence)
    printf("\nComparando Densidade (menor vence):\n");
    int res = comparaAtributo(&c1, &c2, 5);
    if (res > 0)
        printf("Vencedor: Carta %d (%s)\n", c1.codigo, c1.nome);
    else if (res < 0)
        printf("Vencedor: Carta %d (%s)\n", c2.codigo, c2.nome);
    else
        printf("Empate na densidade!\n");
}

void nivelAventureiro()
{
    printf("\n-- Nível Aventureiro --\n");
    printf("Cadastre a Carta 1:\n");
    Carta c1 = cadastrarCarta();
    printf("Cadastre a Carta 2:\n");
    Carta c2 = cadastrarCarta();
    mostrarCarta(&c1);
    mostrarCarta(&c2);

    printf("\nEscolha atributo:\n1.População\n2.Área\n3.PIB\n4.Pontos turísticos\n5.Densidade\nOpção: ");
    int esc;
    scanf("%d", &esc);

    int r = comparaAtributo(&c1, &c2, esc);
    if (r > 0)
        printf("Vencedor: %s (atributo %d)\n", c1.nome, esc);
    else if (r < 0)
        printf("Vencedor: %s (atributo %d)\n", c2.nome, esc);
    else
    {
        // desempate aninhado: se empatou no escolhido, desempata por populacao
        printf("Empate! Desempatando por população:\n");
        r = comparaAtributo(&c1, &c2, 1);
        if (r > 0)
            printf("Vencedor desempate: %s\n", c1.nome);
        else if (r < 0)
            printf("Vencedor desempate: %s\n", c2.nome);
        else
            printf("Ainda empata no desempate!\n");
    }
}

void nivelMestre()
{
    printf("\n-- Nível Mestre --\n");
    printf("Cadastre a Carta 1:\n");
    Carta c1 = cadastrarCarta();
    printf("Cadastre a Carta 2:\n");
    Carta c2 = cadastrarCarta();
    mostrarCarta(&c1);
    mostrarCarta(&c2);

    const char *atributos[] = {
        "População", "Área", "PIB", "Pontos turísticos", "Densidade"};
    int att1, att2;
    do
    {
        printf("\nEscolha 1º atributo:\n");
        for (int i = 0; i < 5; i++)
            printf("%d. %s\n", i + 1, atributos[i]);
        printf("Opção: ");
        scanf("%d", &att1);
        printf("Escolha 2º atributo (diferente do 1º): ");
        scanf("%d", &att2);
        if (att1 == att2)
            printf("Não pode escolher o mesmo. Tente de novo.\n");
    } while (att1 < 1 || att1 > 5 || att2 < 1 || att2 > 5 || att1 == att2);

    int score = 0;
    score += comparaAtributo(&c1, &c2, att1);
    score += comparaAtributo(&c1, &c2, att2);

    printf("\nResultado combinando %s e %s:\n",
           atributos[att1 - 1], atributos[att2 - 1]);
    printf("Vencedor: %s\n", score>0 ? c1.nome : (score<0 ? c2.nome : "Empate geral!"));
}
