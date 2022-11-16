// Seja um vetor V com n números inteiros. Projete um algoritmo usando Força Bruta e outro
// usando a estratégia de Transformar e Conquistar para retornar o número que aparece mais vezes
// em V. Em caso de empate, o algoritmo pode devolver qualquer um dos números empatados. Ao
// final, analise a complexidade de pior caso de ambos os algoritmos em função de n.

// No pior caso, temos que o algoritmo abaixo será de complexidade O(n2) visto que
// foi necessário aninhar dois laços para se alcançar o resultado esperado. Ambos
// os laços iteram sobre o número total de elementos do vetor de tamanho "n".

#include <stdio.h>

int main(void)
{
    int V[5] = {-1, -1, 3, -1, 5};
    int arrSize = 5;
    int mostRepeatingNumber;
    int largestCount = 0;

    for (int i = 0; i < arrSize; i++)
    {
        int count = 1;
        for (int j = 0; j < arrSize; j++)
        {
            if (i == j)
            {
                continue;
            }

            if (V[i] == V[j])
            {
                count++;
            }
        }
        if (count > largestCount)
        {
            largestCount = count;
            mostRepeatingNumber = V[i];
        }
    }

    printf("O numero que mais repete eh o: %i\n", mostRepeatingNumber);
    printf("O %i foi repetido %i vezes\n", mostRepeatingNumber, largestCount);
    return 0;
}