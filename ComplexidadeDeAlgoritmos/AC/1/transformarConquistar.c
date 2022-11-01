// No pior caso, temos que a complexidade deste algoritmo será de O(n*log(n)).
// A complexidade, neste caso, está na necessidade da utilização de um algoritmo para
// ordenar o vetor de entrada, neste caso o QuickSort que é de complexidade O(n*log(n)).
// Além do algoritmo de ordenação, há também um laço para iterar sobre o vetor ordenado
// e encontrar o número que mais se repete.

// Seja um vetor V com n números inteiros. Projete um algoritmo usando Força Bruta e outro
// usando a estratégia de Transformar e Conquistar para retornar o número que aparece mais vezes
// em V. Em caso de empate, o algoritmo pode devolver qualquer um dos números empatados. Ao
// final, analise a complexidade de pior caso de ambos os algoritmos em função de n.
#include <stdio.h>

void quickSort1(int v[], int ini, int fim)
{
    int i = ini;
    int j = fim;
    int pivo = v[(ini + fim) / 2]; // Pivo e o elemento central

    do
    {
        while (v[i] < pivo && i < fim)
            i++;
        while (pivo < v[j] && j > ini)
            j--;
        if (i <= j)
        {
            int aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            i++;
            j--;
        }
    } while (i <= j);

    if (ini < j)
        quickSort1(v, ini, j);
    if (i < fim)
        quickSort1(v, i, fim);
}

void quickSort(int v[], int tam)
{
    quickSort1(v, 0, tam - 1);
}

int main(void)
{
    int V[10] = {-1, 2, -1, -1, 2, 4, 3, 3, 3, 3};
    int arrSize = 10;
    int biggestCount = 0;
    int biggestCountNumber;
    int count = 0;

    quickSort(V, arrSize);

    int pivot = V[0];
    for (int i = 0; i < arrSize; i++)
    {
        if (pivot != V[i])
        {
            count = 0;
            pivot = V[i];
        }
        count++;
        if (count > biggestCount)
        {
            biggestCount = count;
            biggestCountNumber = pivot;
        }
    }

    printf("O numero %i aparece %i vezes, sendo o que mais aparece\n", biggestCountNumber, biggestCount);

    return 0;
}