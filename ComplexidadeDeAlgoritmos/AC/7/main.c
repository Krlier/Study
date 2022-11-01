// Projete um algoritmo recursivo para gerar a decomposição de um número inteiro positivo n na
// soma de todos os seus possíveis fatores, conforme mostrado no exemplo a seguir para n = 5:

#include <stdio.h>
#define MAXFATORES 100

int fatores[MAXFATORES];
int count = 0;

void imprimeFatores(int index)
{
    // Para cada fator no vetor, imprime
    for (int i = 1; i < index; i++)
    {
        if (i + 1 == index)
            printf("%i", fatores[i]);
        else
            printf("%i + ", fatores[i]);
    }
    printf("\n");
}

void decompoe(int n, int maxVal, int index, int count)
{
    // Número não pode mais ser decomposto, imprime
    if (n == 0)
    {
        imprimeFatores(index);
        count++;
        return;
    }

    // Enquanto não chegar no menor fator, decompoe
    for (int i = maxVal; i >= 1; i--)
    {
        if (i > n)
        {
            continue;
        }
        else
        {
            fatores[index] = i;
            decompoe(n - i, i, index + 1, count);
        }
    }
}

int main()
{
    int n;
    int count = 0;

    printf("Insira um número para ser decomposto:\n");
    scanf("%i", &n);

    if (n <= 0)
    {
        printf("Número inválido. Insira um número inteiro positivo\n");
    }

    decompoe(n, n, 1, count);

    return 0;
}
