#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define EVER ;;
#define PARAMETROS IPC_CREAT | S_IRUSR | S_IWUSR

int main (void){
    int pid;
    if( (pid = fork()) == 0 ){      // Executa o Escalonador
        execl("./Escalonador", "Escalonador", NULL);
        puts("Interpretador não conseguiu executar o Escalonador");
        exit(127);                  // Termina o programa se execv falhar
    }
    
    //Programa do Interpretador

    int segmento1, segmento2, segmento3, segmento4, segmento5, tipo = -1, inicio, duracao, prioridade;        //Tipo do processo, 0:Real Time - 1:Prioridade - 2:Round-Robin
    int *p2, *p3, *p4;
    char linha[10], nomeProcesso[2], nomeInicio[2];
    char *p1, *p5;
    FILE *arquivo;

    segmento1 = shmget (2011, 5*sizeof(char), PARAMETROS); //Cria memória compartilhada com chave 2011
    segmento2 = shmget (2012, sizeof(int), PARAMETROS);    //Cria memória compartilhada com chave 2012
    segmento3 = shmget (2013, sizeof(int), PARAMETROS);    //Cria memória compartilhada com chave 2013
    segmento4 = shmget (2014, sizeof(int), PARAMETROS);    //Cria memória compartilhada com chave 2014
    segmento5 = shmget (2015, 5*sizeof(char), PARAMETROS);    //Cria memória compartilhada com chave 2015

    //Inicia as memórias compartilhadas

    p1 = (char *)shmat (segmento1, 0, 0);   //Memória compartilhada para nomeProcesso  
    p2 = (int *)shmat(segmento2, 0, 0);     //Memória compartilhada para tipo
    p3 = (int *)shmat(segmento3, 0, 0);     //Memória compartilhada para início / prioridade
    p4 = (int *)shmat(segmento4, 0, 0);     //Memória compartilhada para duração
    p5 = (char *)shmat(segmento5, 0, 0);     //Memória compartilhada no caso de um processo que é inicializado após outro

    arquivo = fopen("exec.txt", "r");       //Abre o arquivo exec.txt
    if(!arquivo){
        puts("Erro ao abrir o arquivo exec.txt");
        return -1;
    }

    for(EVER){                          //Loop do Interpretador
        if( (fgets(linha, 11, arquivo)) == NULL) //Lê uma linha do arquivo ou encerra o programa
            return 0;

        if(linha[4] == 'P'){               //Processo é do tipo Prioridade
            tipo = 1;
            sscanf(linha, "Run %s PR=%i", nomeProcesso, &prioridade);
            *p3 = prioridade;         //Escreve a prioridade na memória
        }
        else{                              //Processo é do tipo Real Time
            if(linha[4] == 'I'){
                tipo = 0;
                sscanf(linha, "Run %s I=%i D=%i", nomeProcesso, &inicio, &duracao);
                if(inicio == 0){           //Processo Real Time só começa após outro terminar
                    sscanf(linha,"Run %s I=%s D=%i", nomeProcesso, nomeInicio, &duracao);
                    strcpy(p5, nomeInicio);
                    *p3 = -1;
                }
                else{
                    if((inicio+duracao) > 60){
                        printf("O processo %s tem o tempo de inicio + duração maior do que 1 minuto \n", nomeProcesso);
                        exit(-1);
                    }
                    *p3 = inicio;               //Escreve o início na memória
                }
                *p4 = duracao;               //Escreve a duração na memória
            }
            else{                          //Processo é do tipo Round-Robin
                tipo = 2;
                sscanf(linha, "Run %s", nomeProcesso);
            }
        }
        strcpy(p1, nomeProcesso);           //Escreve o nome do processo na memória
        *p2 = tipo;                          //Escreve o tipo na memória

        sleep(1);
    }
    return 0;
} 