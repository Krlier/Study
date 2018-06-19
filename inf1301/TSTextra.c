#include    "Lista.h"
#include	"tabuleiro.h"
#include	"cartas.h"
#include	"extra.h"
#include	"Generico.h"


static const char CRIA_SEQUENCIA_EXTRA       	 [ ] = "=criaseqextra"  	   ;
static const char TESTA_ENTRADA_EXTRA        	 [ ] = "=testaentradaextra"    ;
static const char TESTA_SAIDA_EXTRA	        	 [ ] = "=testasaidaextra"  	   ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar lista
*
*  $ED Descrição da função
*     Cria-se o extra e após testa-se a entrada e saída de cartas.
*
*     Comandos disponíveis:
*     =criaseqextra                 CondRetEsp
*     =testaentradaextra            inxLista  string  CondRetEsp
*     =testasaidaextra              inxLista  string  CondretPonteiro
*
***********************************************************************/


TST_tpCondRet TST_EfetuarComando( char * ComandoTeste ){

	LIS_tppLista pLista, pl;
	Carta *carta;

	if ( strcmp( ComandoTeste , CRIA_SEQUENCIA_EXTRA ) == 0 ){

		pl = cria_sequencia_extra();		

		if (pl == NULL){
			return TST_CondRetMemoria;
		}

		return TST_CondRetOK;
	}

	carta = (Carta*) malloc (sizeof (Carta));
	pLista = LIS_CriarLista (LIS_ExcluirValor);
	pl = LIS_CriarLista (LIS_ExcluirValor);
	LIS_InserirElementoApos (pLista, pl);


	carta->numero = 10 ;
	strcpy (carta->naipe, "Ouros") ;
	strcpy (carta->cor, "Vermelho") ;

	else if ( strcmp( ComandoTeste , TESTA_ENTRADA_EXTRA ) == 0 ){


	}

	else if ( strcmp( ComandoTeste , TESTA_SAIDA_EXTRA ) == 0 ){


	}
}