// Grupo: Daniel Carlier e João Victor Cerqueira
// Disciplina: Inf-1019

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int d = 0;                      // Variável global d, para debug

typedef struct {
    unsigned int addr;          // Endereço para memória física
    int referenciada;           // Campo para identificar se foi referenciada recentemente -> Dura 100 segundos
    int modificada;             // Campo para identificar se memória foi modificada
    int momentoAcesso;          // Campo para guardar o último momento de acesso
    int nAcessosRecentes;       // Campo para guardar quantas vezes a página foi acessada recentemente

}TabelaDePaginas;

// Função que converte a entrada no endereço desejado conforme o tamanho de cada página
unsigned int pegaEndereco(unsigned int addr, int tamPagina){
    if( tamPagina == 8 ){           // Determina o tamanho da página e o offset
            addr = addr >> 13;
        }
        else{
            if ( tamPagina == 16 ){ // 16 Kb de tamanho de página
                addr = addr >> 14;
            }
            else{
                addr = addr >> 15;  // 32 Kb de tamanho de página
            }
        }
}

// Função que inicializa a tabela de páginas
void inicializaTabela(TabelaDePaginas Tabela[], int tamTabela){
    int i;
    for(i=0; i < tamTabela; i++){
        Tabela[i].addr = 1;
        Tabela[i].referenciada = 0;
        Tabela[i].modificada = 0;
        Tabela[i].momentoAcesso = -1;
        Tabela[i].nAcessosRecentes = 0;
    }
}

// Função para imprimir em caso de debug
void printDebug(char *c){
    if(d == 1)
        puts(c);
}

// Função para resetar o bit Referenciada após um tempo. No caso, 60 segundos
void resetPagReferenciada(TabelaDePaginas *Tabela, int tamTabela){
    int i;
    for(i=0; i < tamTabela; i++){
        Tabela[i].referenciada = 0;
    }
}

// Confere se passaram 60 segundos
int confereTempo(int tempo){
    int i;
    for( i=1; i < 1000001; i++){
        if(tempo < (i*60))
            return 1;
        if(tempo = (i*60)) 
            return 0;
    }
}

// Função para encontrar a página menos utilizada recentemente
int encontraOPT(TabelaDePaginas *Tabela,unsigned int* optAddr,int qtdFuturas,int tamTabela){   // Precisa só da atual e das 70 futuras pra ver se vai encontrar
    int temp[tamTabela];
    int i,j,k,flag,pos,max;
    if(qtdFuturas == 71){ 	// não tem mais nenhuma futura porque é o ultimo log,então retorna 0 mesmo
	return 0;
    }
    for(j = 0; j < tamTabela; ++j){
      temp[j] = -1;            
      for(k = qtdFuturas; k < 71; ++k){  // as posições 'do futuro' estão nos indices qtdFuturas a 70 no vetor
        if(Tabela[j].addr == optAddr[k]){	// se encontrou na tabela o endereço futuro da posição k marca temp[] na posição dele
          temp[j] = k;
          break;
        }
      }
    }
    for(j = 0; j < tamTabela; ++j){ // retorna a primeira não acessada no futuro(tem temp marcada como -1)
                if(temp[j] == -1){
                    pos = j;
                    flag = 1;
                    break;
                }
            }
     if(flag ==0){	//  se todas são acessadas no futuro pega a mais distante
                max = temp[0];
                pos = 0;
                
                for(j = 1; j < tamTabela; ++j){
                    if(temp[j] > max){
                        max = temp[j];
                        pos = j;
                    }
                }                
            }
   return pos;
}

// Função para encontrar a página menos utilizada recentemente
int encontraLRU(TabelaDePaginas *Tabela, int tamTabela){
    int i, menosUsada;
    menosUsada = 100;	
    for(i=0; i<tamTabela; i++){
        if(Tabela[i].nAcessosRecentes < menosUsada){
            menosUsada = Tabela[i].nAcessosRecentes;
            return i;
        }
    }
}

// Função para encontrar uma página que não foi utilizada recentemente
// Ordem de preferência, 0 sendo a mais alta e 4 a mais baixa
// 0 -> Não referenciada, Não modificada
// 1 -> Não referenciada, Modificada
// 2 -> Referenciada, Não Modificada
// 3 -> Referenciada, Modificada
int encontraNRU(TabelaDePaginas *Tabela, int tamTabela){
    int i, cat1, cat2, cat3;
    cat1 = -1; cat2 = -1; cat3 = -1;
    for(i=0; i<tamTabela; i++){
        if(Tabela[i].referenciada == 0 && Tabela[i].modificada == 0){
            return i;
        }
        else{
            if((Tabela[i].referenciada == 0) && (Tabela[i].modificada != 0) && (cat1 == -1)){  // se não ja encontrou uma pagina desse tipo mais "antiga" que ela
                cat1=i;
            }
            else{
                if((Tabela[i].referenciada == 1) && (Tabela[i].modificada == 0) && (cat2 == -1) ){ // se não ja encontrou uma pagina desse tipo mais "antiga" que ela
                    cat2=i;
		}
                else{
                    if((Tabela[i].referenciada == 1) && (Tabela[i].modificada != 0) && (cat3 == -1)){ // se não ja encontrou uma pagina desse tipo mais "antiga" que ela
                        cat3=i;
		    }
                }
            }
        }
     }
    if(cat1 != -1) // se tem alguem na categoria cat1 retorna ela
        return cat1;
    else if(cat2 != -1) // se tem alguem na categoria cat2 retorna ela
        return cat2;
    else  			// se não tem ninguem,retorna a primeira da categoria cat3 mesmo
    return cat3;
}


int main(int argc, char* argv[]){
    
    unsigned int addr;
    unsigned int optAddr[71];
    int tamPagina, tamMemoria;
    int tamTabela, i, j, tempo, endVazio, contaPF, contaPE, encontrou, posicaoLRU, posicaoNRU, posicaoOPT, tempoFifo, posicaoFIFO,a;
    char tipo;
    char algoritmo[10], nomeArquivo[20],debug[10] ,optTipo[71];
    FILE *arquivo;
    TabelaDePaginas *Tabela;
    tempo = 0;                                                  // Inicializa tempo com 0.
    endVazio = 0;                                               // Guarda a posição do próximo endereço da tabela que esteja vazio. -1 se cheio.
    encontrou = 0;                                              // Verifica se a página foi encontrada (PAGE HIT)
    contaPE = 0;                                                // Inicializa o contador de páginas ecritas
    contaPF = 0;                                                // Inicializa o contador de falta de páginas (PAGE FAULT)
    
    if(argc <= 4){                                              // HELP
        puts("Simulador de Tabela de Páginas");
        puts("Grupo: Daniel Carlier e João Victor Cerqueira \n");
        puts("Para executar o simulador, utilize essa estrutura:");
        puts("./simulador algoritmo arquivo.log 8 16 \n");
        puts("Para utilizar o simulador em Debug:");
        puts("./simulador algoritmo arquivo.log 8 16 debug \n");
        puts("Exemplo de Utilização:");
        puts("./simulador NRU simulador.log 8 16");
        exit(0);
    }


    if(argc == 6)
        strcpy(debug, argv[5]);
    strcpy(algoritmo, argv[1]);
    strcpy(nomeArquivo, argv[2]);
    tamPagina = atoi(argv[3]);
    tamMemoria = atoi(argv[4]);

    tamTabela = (tamMemoria * 1000 ) / tamPagina;                               // Encontra o tamanho do vetor para a Tabela de Páginas
    Tabela = (TabelaDePaginas*) malloc((tamTabela+1) * sizeof(TabelaDePaginas));    // Aloca o vetor para a Tabela de Páginas
    inicializaTabela(Tabela, tamTabela);                                        // Inicializa a tabela.

    // Prints para inicialização:
    puts("Executando o simulador...");
    printf("Arquivo de entrada: %s \n", argv[2]);
    printf("Tamanho da Memória Fisica: %iMB \n", tamMemoria);
    printf("Tamanho das páginas: %iKB \n", tamPagina);
    printf("Alg de substituição: %s \n", argv[1]);

    arquivo = fopen(nomeArquivo, "r");                          // Abre o arquivo .log
    if( arquivo == NULL){                                       // Trata o errro de abertura do arquivo.
        printf("Erro ao abrir o arquivo %s \n", nomeArquivo);
        exit(-1);
    }

    if( strcmp(debug,"debug") == 0 ){                            // Verifica se o programa está em modo debug.
        d = 1;
        sleep(2);                                                // Aguarda 2 segundos para que a informação seja vista pelo usuário

    }


    //-------------------------------------------------------------------------------------------------------------------------------------------------------------//


    //  Trecho do código para o algoritmo Ótimo //


    //-------------------------------------------------------------------------------------------------------------------------------------------------------------//



    if(strcmp(algoritmo,"OPT")==0){                                         // Algoritmo desejado é o Optimo, vai ler 70 iniciais e depois sempre que ler atualiza a lista
	    for(i=1;i<71;i++){				                                        // lendo as 70 iniciais e deixando a posição 0 vazia,pois o vetor vai ser 'puxado' abaixo
 	        if( fscanf(arquivo, "%x %c", &optAddr[i], &optTipo[i]) != EOF){
		        optAddr[i] = pegaEndereco(optAddr[i], tamPagina);                   // Pega o endereço correto
	        }
	    }
	 
        while( fscanf(arquivo, "%x %c", &addr, &tipo) != EOF ){             // Leu uma nova, vai atualizar o vetor das futuras com essa no final(mais antiga, a mais 'nova' ja esta no vetor opt
            printDebug("Leu um endereço do arquivo");

            if(confereTempo(tempo) == 0){                                       // Limpa as páginas referenciadas após 60 segundos.
                resetPagReferenciada(Tabela, tamTabela);
            }
	        for(i=0; i<70; i++){	                                                // Anda com as já lidas e a nova entrará no fim
                optAddr[i] = optAddr[i+1];
                strcpy(&optTipo[i],&optTipo[i+1]);
            }
	        optTipo[70] = tipo ; 
	        optAddr[70] = addr;
            optAddr[70] = pegaEndereco(optAddr[70], tamPagina);
	        addr = optAddr[0];
	        tipo = optTipo[0];
	        for(i=0; i < tamTabela; i++){                           // Percorre a tabela
                if( addr == Tabela[i].addr ){                       // Verifica se a página está na tabela
                printDebug("Page Hit!");
                Tabela[i].momentoAcesso = tempo;                // Pega o momento de acesso
                Tabela[i].referenciada = 1;                     // Marca a página como referenciada
                Tabela[i].nAcessosRecentes++;                   // Soma 1 ao número de acessos recentes
                Tabela[i].modificada = 0;
                if(tipo == 'W'){
                    Tabela[i].modificada = 1;                   // Marca a página como sendo modificada
		        }
                encontrou = 1;                                  // Verifica se a página desejada foi encontrada
                break;
                }
            }
            if(encontrou != 1){                                     // Não foi PAGE HIT
                if(endVazio != -1){                                 // Page Fault! Mas ainda existem páginas vazias na tabela de paginação.
                    printDebug("Page Fault! Página não está na memória, mas ainda tem espaço na Tabela!");
                    Tabela[endVazio].addr = addr;                   // Adiciona o endereço
                    Tabela[endVazio].momentoAcesso = tempo;         // Adiciona o momento em que foi acessada
                    Tabela[endVazio].referenciada = 1;              // Marca que a página foi referencidada
                    Tabela[endVazio].nAcessosRecentes = 1;          // Soma 1 ao número de acessos recentes
                    Tabela[endVazio].modificada = 0;
                    if(tipo == 'W')		
                        Tabela[endVazio].modificada = 1;            // Marca a página como sendo modificada
                    endVazio++;                                     // Adiciona 1 ao endVazio
                    if((endVazio+1) == tamTabela)                   // Verifica se acabaram os endereços livres
                        endVazio = -1;
                    contaPF++;                                      // Adiciona 1 ao número de Page Faults
                }   
                else{                                                           // Page Fault! Mas todas as posições na Tabela estão preenchidas então ve o futuro
		            printDebug("Page Fault! Alguma página será substituída (OPT)");
		            posicaoOPT = encontraOPT(Tabela,optAddr,1,tamTabela);       // Pega a posição da página a ser substituída ao passar a atual e as futuras,alem de a partir de qual numero o vetor futuras ta começando
                    if(Tabela[posicaoOPT].modificada == 1){                     // Página foi modificada, deve ser escrita na memória
                        printDebug("Página Escrita na memória");
                        contaPE++;                                              // Adiciona 1 ao número de páginas escritas
                    }
                    Tabela[posicaoOPT].addr = addr;                             // Insere na posição os valores da nova página
                    Tabela[posicaoOPT].momentoAcesso = tempo;
                    Tabela[posicaoOPT].referenciada = 1;
                    Tabela[posicaoOPT].nAcessosRecentes = 1;
                    Tabela[posicaoOPT].modificada = 0;
                    if(tipo == 'W')
                        Tabela[posicaoOPT].modificada = 1;
                    contaPF++;                                                  // Adiciona 1 ao número de page faults
	            }
            }
	        encontrou = 0;
        }  
        // Fim do while, faltam as 70 páginas que ainda estão no vetor opt
        for(j=1;j<71;j++){                                        // começa em 1 e vai até 71 porque quando sai do while() ja trabalhou com a 0 atual e ainda tem as 70 ultimas mas estão nas posições 1 a 71 do vetor
	        addr = optAddr[j];
            tipo = optTipo[j];
	        for(i=0; i < tamTabela; i++){                               // Percorre a tabela
                if( addr == Tabela[i].addr ){                       // Verifica se a página está na tabela
                    printDebug("Page Hit!");
                    Tabela[i].momentoAcesso = tempo;                // Pega o momento de acesso
                    Tabela[i].referenciada = 1;                     // Marca a página como referenciada
                    Tabela[i].nAcessosRecentes++;                   // Soma 1 ao número de acessos recentes
                    Tabela[i].modificada = 0;
                    if(tipo == 'W'){
                        Tabela[i].modificada = 1;                   // Marca a página como sendo modificada
		            }
                    encontrou = 1;                                  // Verifica se a página desejada foi encontrada
                    break;
                }
            }
            if(encontrou != 1){                                     // Não foi PAGE HIT
                if(endVazio != -1){                                 // Page Fault! Mas ainda existem páginas vazias na tabela de paginação.
                    printDebug("Page Fault! Página não está na memória, mas ainda tem espaço na Tabela!");
                    Tabela[endVazio].addr = addr;                   // Adiciona o endereço
                    Tabela[endVazio].momentoAcesso = tempo;         // Adiciona o momento em que foi acessada
                    Tabela[endVazio].referenciada = 1;              // Marca que a página foi referencidada
                    Tabela[endVazio].nAcessosRecentes = 1;          // Soma 1 ao número de acessos recentes
                    Tabela[endVazio].modificada = 0;
                    if(tipo == 'W')		
                        Tabela[endVazio].modificada = 1;            // Marca a página como sendo modificada
                    endVazio++;                                     // Adiciona 1 ao endVazio
                    if((endVazio+1) == tamTabela)                   // Verifica se acabaram os endereços livres
                        endVazio = -1;
                    contaPF++;                                      // Adiciona 1 ao número de Page Faults
                }   
                else{                                                   // Page Fault! Mas todas as posições na Tabela estão preenchidas então ve o futuro
		            printDebug("Page Fault! Alguma página será substituída (OPT)");
		            posicaoOPT = encontraOPT(Tabela,optAddr,j+1,tamTabela);     // Pega a posição da página a ser substituída, nesse caso tem menos futuras então o vetor começara de j+1 pq addr atual é j
                    if(Tabela[posicaoOPT].modificada == 1){         // Página foi modificada, deve ser escrita na memória
                        printDebug("Página Escrita na memória");
                        contaPE++;                                  // Adiciona 1 ao número de páginas escritas
                    }
                    Tabela[posicaoOPT].addr = addr;                 // Insere na posição os valores da nova página
                    Tabela[posicaoOPT].momentoAcesso = tempo;
                    Tabela[posicaoOPT].referenciada = 1;
                    Tabela[posicaoOPT].nAcessosRecentes = 1;
                    Tabela[posicaoOPT].modificada = 0;
                    if(tipo == 'W')
                        Tabela[posicaoOPT].modificada = 1;
                    contaPF++;                                      // Adiciona 1 ao número de page faults
	            }
            }
	        encontrou = 0;
        }
    }

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------//


    //  Trecho do código para os outros algoritmos //


    //-------------------------------------------------------------------------------------------------------------------------------------------------------------//


    

    else{
        while( fscanf(arquivo, "%x %c", &addr, &tipo) != EOF ){    // Enquanto houver linhas no arquivo, faça:

            printDebug("Leu um endereço do arquivo");

            if(confereTempo(tempo) == 0){                           // Limpa as páginas referenciadas após 60 segundos.
                resetPagReferenciada(Tabela, tamTabela);
            }


            addr = pegaEndereco(addr, tamPagina);                   // Pega o endereço correto

            for(i=0; i < tamTabela; i++){                           // Percorre a tabela
                if( addr == Tabela[i].addr ){                       // Verifica se a página está na tabela
                    printDebug("Page Hit!");
                    Tabela[i].momentoAcesso = tempo;                // Pega o momento de acesso
                    Tabela[i].referenciada = 1;                     // Marca a página como referenciada
                    Tabela[i].nAcessosRecentes++;                   // Soma 1 ao número de acessos recentes
                    Tabela[i].modificada = 0;
                    if(tipo == 'W'){
                        Tabela[i].modificada = 1;                   // Marca a página como sendo modificada
                    }
                    encontrou = 1;                                  // Verifica se a página desejada foi encontrada
                    break;
                }
            }
            if(encontrou != 1){                                     // Não foi PAGE HIT
                if(endVazio != -1){                                 // Page Fault! Mas ainda existem páginas vazias na tabela de paginação.
                    printDebug("Page Fault! Página não está na memória, mas ainda tem espaço na Tabela!");
                    Tabela[endVazio].addr = addr;                   // Adiciona o endereço
                    Tabela[endVazio].momentoAcesso = tempo;         // Adiciona o momento em que foi acessada
                    Tabela[endVazio].referenciada = 1;              // Marca que a página foi referencidada
                    Tabela[endVazio].nAcessosRecentes = 1;          // Soma 1 ao número de acessos recentes
                    Tabela[endVazio].modificada = 0;
                    if(tipo == 'W')		
                        Tabela[endVazio].modificada = 1;            // Marca a página como sendo modificada
                    endVazio++;                                     // Adiciona 1 ao endVazio
                    if((endVazio+1) == tamTabela)                   // Verifica se acabaram os endereços livres
                        endVazio = -1;
                    contaPF++;                                      // Adiciona 1 ao número de Page Faults
                }   
                else{                                                   // Page Fault! Mas todas as posições na Tabela estão preenchidas
                    if(strcmp(algoritmo,"LRU")==0){                     // O algoritmo desejado é o Least Recently Used
                        printDebug("Page Fault! Alguma página será substituída (LRU)");
                        posicaoLRU = encontraLRU(Tabela, tamTabela);    // Pega a posição da página a ser substituída
                        if(Tabela[posicaoLRU].modificada == 1){         // Página foi modificada, deve ser escrita na memória
                            printDebug("Página Escrita na memória");
                            contaPE++;                                  // Adiciona 1 ao número de páginas escritas
                        }
                        Tabela[posicaoLRU].addr = addr;                 // Insere na posição os valores da nova página
                        Tabela[posicaoLRU].momentoAcesso = tempo;
                        Tabela[posicaoLRU].referenciada = 1;
                        Tabela[posicaoLRU].nAcessosRecentes = 1;
                        Tabela[posicaoLRU].modificada = 0;
                        if(tipo == 'W')
                            Tabela[posicaoLRU].modificada = 1;
                        contaPF++;                                      // Adiciona 1 ao número de page faults
                    }
                    if(strcmp(algoritmo,"NRU")==0){                     // O algoritmo desejado é o Not Recently Used
                        printDebug("Page Fault! Alguma página será substituída (NRU)");
                        posicaoNRU = encontraNRU(Tabela, tamTabela);
                        if(Tabela[posicaoNRU].modificada == 1){
                            printDebug("Página Escrita na memória");
                            contaPE++;                    
                        }
                        Tabela[posicaoNRU].addr = addr;                 // Insere na posição os valores da nova página
                        Tabela[posicaoNRU].momentoAcesso = tempo;
                        Tabela[posicaoNRU].referenciada = 1;
                        Tabela[posicaoNRU].nAcessosRecentes = 1;
                        Tabela[posicaoNRU].modificada = 0;
                        if(tipo == 'W')
                            Tabela[posicaoNRU].modificada = 1;
                        contaPF++;                                      // Adiciona 1 ao número de page faults
                    }
                    if(strcmp(algoritmo,"NOV")==0){                     // Nosso novo algoritmo --> FIFO
                        printDebug("Page Fault! Alguma página será substituída (NOV)");
                        tempoFifo = 0;
                        posicaoFIFO = 0;
                        for(i=0; i<tamTabela; i++){                     // É possível saber qual página entrou primeiro a partir do seu momento de acesso
                            if(Tabela[i].momentoAcesso < tempoFifo){
                                tempoFifo = Tabela[i].momentoAcesso;
                                posicaoFIFO = i;
                            }
                        }
                        if(Tabela[posicaoFIFO].modificada == 1){        // Verifica se a página foi modificada
                            printDebug("Página Escrita na memória");
                            contaPE++;                    
                        }
                        Tabela[posicaoFIFO].addr = addr;                // Substitui a página
                        Tabela[posicaoFIFO].momentoAcesso = tempo;
                        Tabela[posicaoFIFO].referenciada = 1;
                        Tabela[posicaoFIFO].nAcessosRecentes = 1;
                        Tabela[posicaoFIFO].modificada = 0;
                        if(tipo == 'W')
                            Tabela[posicaoFIFO].modificada = 1;
                        contaPF++;
                    }
                    
                    if( (strcmp(algoritmo,"LRU") != 0) && (strcmp(algoritmo,"NRU") != 0) && (strcmp(algoritmo,"OPT") != 0) && (strcmp(algoritmo,"NOV") != 0) ){
                        printf("\nAlgoritmo: %s não encontrado! \n \n", algoritmo);
                        exit(-1);
                    }
                }
            }
            encontrou = 0;                                          // Reseta a variável para a próxima iteração
        }
    }
   
    // Fim da execução

    // Imprime Resultados:

    printf("Número de Faltas de Páginas: %i \n", contaPF);
    printf("Número de Páginas Escritas: %i \n", contaPE);
    free(Tabela);
    fclose(arquivo);
 
    return 0;
}
