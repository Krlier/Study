// Considere um vetor V com n números reais. Projete um algoritmo O(n log n) que encontra um
// par de elementos (x, y)  V tal que |x + y| é mínimo, ou seja, é o menor somatório possível em
// V.

#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
#define INFINITY 10000000

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
    int V[5] = {-2, 1, 3, 1, 5};
    int arrSize = 5;
    int minSum = INFINITY;
    int sumNumber1, sumNumber2;

    // Ordena o vetor
    quickSort(V, arrSize);

    // Soma o par dois a dois até encontrar menor soma
    for (int i = 0; i < arrSize; i++)
    {
        // Não é necessário ir ao último elemento do vetor, continue
        if (i == (arrSize - 1))
            continue;

        // Verifica se a soma do par é minima. Caso seja, substitua
        int sum = abs(V[i] + V[i + 1]);
        if (sum < minSum)
        {
            sumNumber1 = V[i];
            sumNumber2 = V[i + 1];
            minSum = sum;
        }
    }

    printf("A menor soma eh |%i + %i| = %i\n", sumNumber1, sumNumber2, abs(minSum));
    return 0;
}
