/*------------------------------------------------------------------------------*/
/*-------------------------------- MODULO EMBARALHAMENTO------------------------*/
/*------------------------------------------------------------------------------*/

/* AUTOR: JORGE PUMAR DODSWORTH*/
/* PROPÓSITO: GERENCIAR UM BARALHO GENERICO*/

#include "embaralhamento.h"

/***********************************************************************
 *
 *  $FC Função: embaralhar
 *
 *  $ED Descrição da função
 *       Essa função embaralha as cartas e devolve uma seed que representa
 *       esse embaralhamento específico.
 *
 *  $EP Parâmetros
 *     $P pLista - Cabeça de lista de listas que contém o elemento
 *                 corrente apontando para a lista que pretende
 *                 avaliar a carta.
 *        seed - Corresponde a um número único para cada jogo criado diferente.
 *
 *
 *  $FV Valor retornado
 *     (seed) -> Saída da seed do jogo
 *     (0) -> Falha no embaralhamento
 *
 ***********************************************************************/
unsigned int embaralhar (LIS_tppLista pLista, unsigned int seed) {
  int i, n;
  LIS_tpCondRet ret;
  void* p;
  Carta* carta, *pc;
  unsigned int valor_seed = seed;
  time_t t;

#ifdef _DEBUG
  CNT_CONTAR( "EMB_Embaralhar_A" ) ;
  assert( pLista != NULL ) ;
  assert( valor_seed >= 0) ;
#endif

  /* Testa se a lista que representa as cartas a serem embaralhadas
     tem menos de 52 cartas */
  IrInicioLista (pLista);
  ret = LIS_AvancarElementoCorrente (pLista, 51);
  if (ret != LIS_CondRetOK) {
#ifdef _DEBUG
    CNT_CONTAR( "EMB_Embaralhar_B" ) ;
#endif
    return 0;
  }

#ifdef _DEBUG
  CNT_CONTAR( "EMB_Embaralhar_C" ) ;
#endif

  ret = LIS_AvancarElementoCorrente (pLista, 1);
  if (ret != LIS_CondRetFimLista) {
#ifdef _DEBUG
    CNT_CONTAR( "EMB_Embaralhar_D" ) ;
#endif
    return 0;
  }

#ifdef _DEBUG
  CNT_CONTAR( "EMB_Embaralhar_E" ) ;
#endif

  srand ((unsigned) time(&t));

  /* Seeding the rand function */
  if (valor_seed == 0) {
#ifdef _DEBUG
    CNT_CONTAR( "EMB_Embaralhar_F" ) ;
#endif
    valor_seed = rand() % 500000 + 1;
    printf ("O seed desse jogo e %u \n", valor_seed);
  }

#ifdef _DEBUG
  CNT_CONTAR( "EMB_Embaralhar_G" ) ;
#endif

  srand (valor_seed);

  for (i=52; i>0; i--) {
#ifdef _DEBUG
    CNT_CONTAR( "EMB_Embaralhar_H" ) ;
#endif

    /* Ir para o comeco da lista com o elemento corrente */
    IrInicioLista (pLista);

    /* Andar n elementos na lista */
    n = rand() % i;
    ret = LIS_AvancarElementoCorrente (pLista, n);

    if (ret == (LIS_CondRetFimLista || LIS_CondRetListaVazia)) {
#ifdef _DEBUG
      CNT_CONTAR( "EMB_Embaralhar_I" ) ;
#endif
      return 0;
    }

#ifdef _DEBUG
    CNT_CONTAR( "EMB_Embaralhar_J" ) ;
#endif

    /* Obter valor do elemento e exclui-lo da lista */
    p = LIS_ObterValor (pLista);
    if (p == NULL) {
#ifdef _DEBUG
      CNT_CONTAR( "EMB_Embaralhar_K" ) ;
#endif
      return 0;
    }

#ifdef _DEBUG
    CNT_CONTAR( "EMB_Embaralhar_L" ) ;
#endif

    pc = (Carta*) p;
    carta = (Carta*) malloc (sizeof (Carta));
    carta->numero = pc->numero;
    strcpy (carta->naipe, pc->naipe);
    strcpy (carta->cor, pc->cor);
    ret = LIS_ExcluirElemento (pLista);

    if (ret == LIS_CondRetListaVazia) {
#ifdef _DEBUG
      CNT_CONTAR( "EMB_Embaralhar_M" ) ;
#endif
      return 0;
    }

#ifdef _DEBUG
    CNT_CONTAR( "EMB_Embaralhar_N" ) ;
#endif

    /* Inserir valor obtido em novo elemento no final da lista */
    IrFinalLista (pLista);
    p = (void*) carta;
    ret = LIS_InserirElementoApos (pLista, p);

    if (ret == LIS_CondRetFaltouMemoria) {
#ifdef _DEBUG
      CNT_CONTAR( "EMB_Embaralhar_O" ) ;
#endif
      return 0;
    }

#ifdef _DEBUG
    CNT_CONTAR( "EMB_Embaralhar_P" ) ;
#endif
  }

#ifdef _DEBUG
  CNT_CONTAR( "EMB_Embaralhar_Q" ) ;
#endif

  return valor_seed;
}
