// Projete um algoritmo da ordem de O(n log n) para remover todos os elementos duplicados de
// um vetor de inteiros não ordenado V.

#include <stdio.h>
#define EMPTY -1000

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
    int V[5] = {-2, 1, 3, 1, 3};
    int arrayWithoutDuplicates[5] = {EMPTY};
    int arrSize = 5;
    int lastAddedNumber;
    int nextEmptyPositionOnArray = 1;

    // Ordena o vetor
    quickSort(V, arrSize);

    // O primeiro elemento do vetor sempre vai ser único, adiciona
    arrayWithoutDuplicates[0] = V[0];
    lastAddedNumber = V[0];

    // Percorre todo o vetor e só adiciona os números que são diferentes do último adicionado
    for (int i = 0; i < arrSize; i++)
    {
        if (V[i] != lastAddedNumber)
        {
            arrayWithoutDuplicates[nextEmptyPositionOnArray] = V[i];
            lastAddedNumber = V[i];
            nextEmptyPositionOnArray++;
        }
    }

    printf("Array sem elementos duplicados:\n");
    for (int i = 0; i < arrSize; i++)
    {
        printf("%i ", arrayWithoutDuplicates[i]);
    }

    return 0;
}