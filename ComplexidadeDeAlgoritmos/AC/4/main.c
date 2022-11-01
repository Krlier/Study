#include <stdio.h>
#include <stdlib.h>
#define n 100

// Considere um problema com as seguintes características:
// Entrada: uma palavra P com 3 caracteres e um texto T com n caracteres;
// Saída: SIM se alguma permutação da palavra P aparece no texto T e NÃO, caso contrário.
// Projete um algoritmo O(n) para resolver este problema.

// Possíveis permutações do vetor P (para 3 caracteres):
// 0,1,2
// 1,2,0
// 2,1,0
// 1,0,2
// 2,0,1
// 0,2,1

int main(void)
{
    char P[3], T[n];

    printf("Insira a palavra P de 3 caracteres:\n");
    scanf("%s", P);

    printf("Insira o texto T de n=%i caracteres:\n", n);
    scanf("%s", T);

    // Percorre todo o vetor T procurando uma possível permutação da palavra P
    for (int i = 0; i < n; i++)
    {
        // Verifica se chegou ao final do vetor T. Caso sim, termine
        if (i == (n - 2))
        {
            break;
        }

        if (T[i] == P[0] && T[i + 1] == P[1] && T[i + 2] == P[2])
        {
            printf("SIM");
            return 0;
        }
        else
        {
            if (T[i] == P[1] && T[i + 1] == P[2] && T[i + 2] == P[0])
            {
                printf("SIM");
                return 0;
            }
            else
            {
                if (T[i] == P[2] && T[i + 1] == P[1] && T[i + 2] == P[0])
                {
                    printf("SIM");
                    return 0;
                }
                else
                {
                    if (T[i] == P[1] && T[i + 1] == P[0] && T[i + 2] == P[2])
                    {
                        printf("SIM");
                        return 0;
                    }
                    else
                    {
                        if (T[i] == P[2] && T[i + 1] == P[0] && T[i + 2] == P[1])
                        {
                            printf("SIM");
                            return 0;
                        }
                        else
                        {
                            if (T[i] == P[0] && T[i + 1] == P[2] && T[i + 2] == P[1])
                            {
                                printf("SIM");
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }

    printf("NÃO");
    return 0;
}