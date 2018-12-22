#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

#define EVER ;;
#define TAM 10

typedef struct {
    char nome[2];
    int tipo;
    int prioridade;
    int inicio;
    int duracao;
    char nomeInicio[2];
    int pid;
}Processo;

void carrega(Processo processo, char* p1, int p2, int p3, int p4, char* p5){
    strcpy(processo.nome, p1);
    processo.tipo = p2;
    processo.inicio = p3;
    processo.duracao = p4;
    strcpy(processo.nomeInicio, p5);
}

void copia(Processo processo1, Processo processo2){ //copia(origem,destino)
    strcpy(processo2.nome, processo1.nome);
    processo2.tipo = processo1.tipo;
    processo2.inicio = processo2.inicio;
    processo2.duracao = processo2.duracao;
    strcpy(processo2.nomeInicio, processo1.nomeInicio);
}

void insereNaFila(Processo processo, Processo lista[]){
    int k, j=0, i=0;
    while(j==0){
        if( (processo.tipo < lista[i].tipo) || (processo.prioridade < lista[i].prioridade) ){
            for(k=i; k<TAM; k++)        //Abre espaço para o novo processo (chega os outros mais para trás)
                copia(lista[TAM-k-1], lista[TAM-k]);
            copia(processo, lista[i]);
            j++;                        //Processo foi inserido, apenas sai da função
        }
        i++;
    }
}

void retiraDaFila(Processo processo, Processo lista[]){
    int i;
    copia(lista[0], processo);
    for(i=1; i<TAM; i++){
        copia(lista[i], lista[i-1]);
    }
}



int main(void){
    
    Processo processos[TAM], processosRT[TAM], davez, chegou;     //Cria um vetor de processos (no máximo TAM por vez)
    int segmento1, segmento2, segmento3, segmento4, segmento5, pid, segundos, rodando=0;
    int ordem[TAM], i=0, j, k;
    int *p2, *p3, *p4;
    char *p1,*p5, comando[TAM];
    char ultimoProcesso[2];
    struct timeval t1, t2;

    davez.tipo = 3; //Inicia davez com tipo 3 (inexistente) -> Tipo 0: RT, Tipo 1: Prioridades, Tipo 2: RR
    davez.prioridade = 8;   //Inicia davez com prioridade maior do que existe

    segmento1 = shmget (0x2011, 5*sizeof(char), 0666);      //Cria memória compartilhada com chave 2011
    segmento2 = shmget (0x2012, sizeof(int), 0666);         //Cria memória compartilhada com chave 2012
    segmento3 = shmget (0x2013, sizeof(int), 0666);         //Cria memória compartilhada com chave 2013
    segmento4 = shmget (0x2014, sizeof(int), 0666);         //Cria memória compartilhada com chave 2014
    segmento5 = shmget (0x2015, 5*sizeof(char), 0666);      //Cria memória compartilhada com chave 2015

    p1 = (char*) shmat (segmento1, 0, 0);   //Memória compartilhada para nomeProcesso  
    p2 = (int*) shmat(segmento2, 0, 0);     //Memória compartilhada para tipo
    p3 = (int*) shmat(segmento3, 0, 0);     //Memória compartilhada para início / prioridade
    p4 = (int*) shmat(segmento4, 0, 0);     //Memória compartilhada para duração
    p5 = (char*) shmat (segmento5, 0, 0);   //Memória compartilhada para nomeProcesso

    gettimeofday (&t1, NULL);

    for(EVER){                              //Loop do Escalonador

        //Recebe os novos processos

        gettimeofday(&t2, NULL);                        //Conta o tempo até 60 segundos
        segundos = (int)t2.tv_sec - (int)t1.tv_sec;
        if(segundos >= 60)
            gettimeofday(&t1, NULL);

        if(strcmp(ultimoProcesso, p1) != 0){             //Novo processo foi lido
            carrega(chegou, p1, *p2, *p3, *p4, p5);
            strcpy(ultimoProcesso, p1);

            if( ((chegou.tipo < davez.tipo) && (chegou.tipo == 1 || chegou.tipo == 2)) || (chegou.prioridade < davez.prioridade) ){  //Processo de maior prioridade que não é Real Time
                kill(davez.pid, SIGSTOP);           //Interrompe o processo que estava executando
                insereNaFila(davez, processos);     //Insere na fila de execução o processo que estava executando
                copia(chegou, davez);               //Troca o novo davez
                if( (davez.pid=fork()) == 0 ){
                    sprintf(comando, "./%s", chegou.nome);
                    execl(comando,comando, NULL);
                }
            }

            if( ((chegou.tipo == davez.tipo) && ((chegou.tipo == 1) || chegou.tipo == 2)) || (chegou.prioridade == davez.prioridade) ){ //Processo de prioridade igual ao sendo executado -> entra na fila direto
                insereNaFila(chegou, processos);
            }

            if( chegou.tipo == 0 ){     //Processo que chegou é Real Time - É armazenado no vetor de processos Real Time
                copia(chegou, processosRT[i]);
                i++;                
            }
        }


        //Tratamendo dos processos RT

        for(j=0; j<TAM; j++){
            if( processosRT[j].inicio == segundos){     //Verifica se tem algum processo RT para começar nesse segundo

                if( (kill(davez.pid,0)) == 0 ){   //Verifica se o processo ainda estava executando,se for igual a 0, estava executando                    
                    kill(davez.pid, SIGSTOP);   //Interrompe processo que estava rodando anteriormente para dar a vez a um RT
                    insereNaFila(davez, processos);
                    rodando--;                  //Nenhum processo mais está rodando
                }

                if(processosRT[j].pid == -1){    //Processo ainda não foi iniciado
                    sprintf(comando, "./%s", processosRT[j].nome);
                    if( (processosRT[j].pid = fork()) == 0 ){   //É o processo filho
                        execl(comando,comando, NULL);
                        rodando++;  //Agora algum processo está rodando
                        retiraDaFila(davez,processosRT);
                    }                    
                }
                else{
                    kill(processosRT[j].pid, SIGCONT);      //Continua um processo RT já iniciado anteriormente
                    rodando++;      //Agora algum processo está rodando
                    retiraDaFila(davez,processosRT);
                }
            }
            if( segundos == (processosRT[j].inicio + processosRT[j].duracao) ){      //Interrompe um processo RT devido ao fim do seu tempo de duração
                kill(processosRT[j].pid, SIGSTOP);
                rodando--;  //Nenhum processo rodando
                for(k=j; k<TAM; k++){   //Verifica se, ao fim do processo RT, tem algum outro que inicia logo em seguida
                    if( strcmp(processosRT[j].nome, processosRT[k].nomeInicio) == 0 ){
                        if( processosRT[k].pid == -1 ){
                            sprintf(comando, "./%s", processosRT[k].nome);
                            if( (processosRT[k].pid = fork()) == 0 ){ //É o processo filho
                                execl(comando,comando, NULL);
                                rodando++;      //Agora algum processo está rodando
                                retiraDaFila(davez,processosRT);
                            }
                        }
                        else{
                            kill(processosRT[k].pid, SIGCONT);
                            rodando++;      //Agora algum processo está rodando
                            retiraDaFila(davez,processosRT);
                        }
                    }
                }
            }
        }

        //Tratamento dos outros processos

        if(rodando == 0){       //Não tem nenhum processo sendo executado, logo execute
            if( processos[0].pid == -1 ){   //Processo ainda não iniciou
                sprintf(comando, "./%s", processos[0].nome);
                if( (processos[0].pid = fork()) == 0 ){      //É o processo filho
                    execl(comando,comando, NULL);
                    rodando++;
                    retiraDaFila(davez,processosRT);
                }
            }
            else{       //Continua o processo caso ele já tenha sido iniciado
                kill(processos[0].pid, SIGCONT);
            }
        }


    }

    return 0;
}

// sprintf(comando, "./%s", processo[i].nome);
// execv(comando, NULL, NULL)