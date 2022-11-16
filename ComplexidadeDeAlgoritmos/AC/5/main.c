// Seja V um vetor com n números inteiros (positivos e negativos). Projete um algoritmo para
// calcular a maior subsequência de V. A maior subsequência é a sequência cuja soma possui o
// maior valor. Por exemplo, se V = {-2, 11, -4, 13,-5, 2}, a subsequência que possui o maior valor
// é a {11, -4, 13}, cuja soma é 20. Para V = {1, -3, 4, -2, -1, 6} a maior subsequência é { 4, -2, -1,
// 6 }, cuja soma é 7. Se todos os elementos forem negativos, a maior subsequência possui zero
// elementos e sua soma é 0. Ao final, analise a complexidade de pior caso do algoritmo proposto
// em função de n.

// A complexidade do algoritmo abaixo é O(n2), dado que existem dois laços aninhados
// que devem repetir n vezes cada.

#include <stdio.h>

int main(void)
{
    int V[6] = {-2, 11, -4, 13, -5, 2};
    // int V[6] = {1, -3, 4, -2, -1, 6};
    int arrSize = 6;
    int accumulatedTotalSum = 0;
    int currentSum = 0;
    int lastEntryIndex = 0;

    for (int i = 0; i < arrSize; i++)
    {
        currentSum += V[i];

        if (currentSum > accumulatedTotalSum)
        {
            accumulatedTotalSum = currentSum;
            if (lastEntryIndex != 0)
            {
                for (int j = lastEntryIndex + 1; j < (arrSize - i); j++)
                {
                    printf("%i ", V[j]);
                }
            }
            lastEntryIndex = i;
            printf("%i ", V[i]);
        }

        if (currentSum < 0)
        {
            currentSum = 0;
        }
    }

    return 0;
}
