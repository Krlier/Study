// Adapte o algoritmo de Seleção de Atividades visto em sala de aula para que ele retorne a
// quantidade de recursos necessário para realizar todas as atividades definidas e, para cada
// recurso, que atividades estão associadas a ele.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ATIVIDADE
{
    char nome[20];
    int horaIni, horaFim;
};

int main(void)
{
    int arrSize = 8;
    struct ATIVIDADE ativ[8];

    // A hora inicial e final das atividades foram retiradas do slide da aula.
    strcpy(ativ[0].nome, "Atividade0");
    ativ[0].horaIni = 9;
    ativ[0].horaFim = 12;

    strcpy(ativ[1].nome, "Atividade1");
    ativ[1].horaIni = 11;
    ativ[1].horaFim = 13;

    strcpy(ativ[2].nome, "Atividade2");
    ativ[2].horaIni = 8;
    ativ[2].horaFim = 14;

    strcpy(ativ[3].nome, "Atividade3");
    ativ[3].horaIni = 12;
    ativ[3].horaFim = 15;

    strcpy(ativ[4].nome, "Atividade4");
    ativ[4].horaIni = 11;
    ativ[4].horaFim = 16;

    strcpy(ativ[5].nome, "Atividade5");
    ativ[5].horaIni = 13;
    ativ[5].horaFim = 17;

    strcpy(ativ[6].nome, "Atividade6");
    ativ[6].horaIni = 14;
    ativ[6].horaFim = 18;

    strcpy(ativ[7].nome, "Atividade7");
    ativ[7].horaIni = 16;
    ativ[7].horaFim = 19;

    int timeResourcesForAllActivity = 0;
    for (int i = 0; i < arrSize; i++)
    {
        timeResourcesForAllActivity += ativ[i].horaFim - ativ[i].horaIni;
    }

    printf("O total de recursos de tempo necessário para realizar todas as atividades definidas é de: %i horas\n", timeResourcesForAllActivity);

    return 0;
}