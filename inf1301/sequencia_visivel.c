/*------------------------------------------------------------------------------*/
/*---------------------- MODULO SEQUENCIA VISIVEL ------------------------------*/
/*------------------------------------------------------------------------------*/

/* AUTOR: DANIEL CARLIER*/
/* PROPÓSITO: Módulo responsável pela definição da Sequência Visível e seus
   testes de entrada e saída de elementos. */

#include "sequencia_visivel.h"


/***********************************************************************
 *
 *  $FC Função: cria_sequencia_visivel
 *
 *  $ED Descrição da função
 *       Cria as listas referentes a sequencia visivel
 *
 *  $FV Valor retornado
 *     LIS_tppLista contendo as listas referentes a sequencia visivel
 *
 ***********************************************************************/
LIS_tppLista cria_sequencia_visivel () {
  LIS_tppLista pLista, cell;
  void* p;
  int i;

#ifdef _DEBUG
  CNT_CONTAR( "CAS_CriaSequenciaVisivel_A" ) ;
#endif

  pLista = LIS_CriarLista (LIS_ExcluirValor);

  for (i=0; i<8; i++) {
#ifdef _DEBUG
    CNT_CONTAR( "CAS_CriaSequenciaVisivel_B" ) ;
#endif
    cell = LIS_CriarLista (LIS_ExcluirValor);
    p = (void*) cell;
    LIS_InserirElementoApos (pLista, p);
  }

#ifdef _DEBUG
  CNT_CONTAR( "CAS_CriaSequenciaVisivel_C" ) ;
#endif

  return pLista;
}


/***********************************************************************
 *
 *  $FC Função: testa_entrada_sequencia_visivel
 *
 *  $ED Descrição da função
 *       Testa se a entrada no sequencia visivel é válida
 *
 *  $EP Parâmetros
 *     $P pLista - Corresponde a uma cabeca de lista que representa a
 *               coluna onde se quer inserir as cartas com o elemento
 *               corrente definido para o ultimo elemento da lista.
 *       bloco - Cabeça de lista de listas que representa o possivel
 *               comeco de um bloco de cartas a ser inserido.
 *
 *  $FV Valor retornado
 *     (1) -> Entrada permitida
 *     (0) -> Entrada negada
 *
 ***********************************************************************/
int testa_entrada_sequencia_visivel (LIS_tppLista pLista, LIS_tppLista bloco) {
  int num, novo_num;
  char cor[20], nova_cor[20];

#ifdef _DEBUG
  CNT_CONTAR( "CAS_TestaEntradaSequenciaVisivel_A" ) ;
  assert( pLista != NULL ) ;
  assert( bloco != NULL);
#endif

  IrFinalLista (pLista);

  num = numero_carta (pLista);
  novo_num = numero_carta (bloco);
  strcpy (cor, cor_carta (pLista));
  strcpy (nova_cor, cor_carta (bloco));

  if ((num == novo_num + 1) && (strcmp (cor, nova_cor) != 0)) {
#ifdef _DEBUG
    CNT_CONTAR( "CAS_TestaEntradaSequenciaVisivel_B" ) ;
#endif
    return 1;
  }

#ifdef _DEBUG
  CNT_CONTAR( "CAS_TestaEntradaSequenciaVisivel_C" ) ;
#endif

  return 0;
}

/***********************************************************************
 *
 *  $FC Função: testa_saida_sequencia_visivel
 *
 *  $ED Descrição da função
 *       Testa se a retirada de uma carta, ou um bloco de cartas, é possível
 *
 *  $EP Parâmetros
 *     $P pLista - Cabeça de lista de listas que contém o elemento
 *                 corrente apontando para a lista que pretende
 *                 avaliar a carta.
 *
 *
 *  $FV Valor retornado
 *     (1) -> Saída permitida
 *     (0) -> Falha na saída
 *
 ***********************************************************************/
int testa_saida_sequencia_visivel (LIS_tppLista pLista) {
  int num, novo_num;
  char cor[20], nova_cor[20];
  LIS_tpCondRet ret;

#ifdef _DEBUG
  CNT_CONTAR( "CAS_TestaSaidaSequenciaVisivel_A" ) ;
  assert( pLista != NULL ) ;
#endif


  num = numero_carta (pLista);
  strcpy (cor, cor_carta (pLista));
  ret = LIS_AvancarElementoCorrente (pLista, 1);

  if (ret == LIS_CondRetFimLista) {
#ifdef _DEBUG
    CNT_CONTAR( "CAS_TestaSaidaSequenciaVisivel_B" ) ;
#endif
    return 1;
  }

#ifdef _DEBUG
  CNT_CONTAR( "CAS_TestaSaidaSequenciaVisivel_C" ) ;
#endif

  novo_num = numero_carta (pLista);
  strcpy (nova_cor, cor_carta (pLista));

  if ((num < novo_num) || (strcmp (cor, nova_cor) == 0)) {
#ifdef _DEBUG
    CNT_CONTAR( "CAS_TestaSaidaSequenciaVisivel_D" ) ;
#endif
    return 0;
  }

#ifdef _DEBUG
  CNT_CONTAR( "CAS_TestaSaidaSequenciaVisivel_E" ) ;
#endif

  return testa_saida_sequencia_visivel (pLista);
}
