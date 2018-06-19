/*------------------------------------------------------------------------------*/
/*-------------------------------- MODULO TABULEIRO ----------------------------*/
/*------------------------------------------------------------------------------*/

/* AUTOR: JORGE PUMAR DODSWORTH*/
/* PROPÓSITO: MOVIMENTAÇÃO DAS CARTAS*/

#include "tabuleiro.h"

/***********************************************************************
 *
 *  $FC Função: cria_baralho
 *
 *  $ED Descrição da função
 *       Essa função inicializa o baralho.
 *
 *  $FV Valor retornado
 *     (pLista) -> Retorna o baralho criado.
 *     (NULL) ->  Erro na criação do baralho.
 *
 ***********************************************************************/

LIS_tppLista cria_baralho () {
  int i, num;
  void* p;
  Carta* carta;
  LIS_tppLista pLista;

#ifdef _DEBUG
  CNT_CONTAR( "TAB_CriaBaralho_A" ) ;
#endif

  pLista = LIS_CriarLista (LIS_ExcluirValor);

  for (i=1; i<53; i++) {
#ifdef _DEBUG
    CNT_CONTAR( "TAB_CriaBaralho_B" ) ;
#endif

    /* Inicializa a carta */
    carta = (Carta*) malloc (sizeof (Carta));

    if (carta == NULL) {
#ifdef _DEBUG
      CNT_CONTAR( "TAB_CriaBaralho_C" ) ;
#endif
      return NULL;
    }

#ifdef _DEBUG
    CNT_CONTAR( "TAB_CriaBaralho_D" ) ;
#endif

    num = i % 13;
    if (num == 0) {
#ifdef _DEBUG
      CNT_CONTAR( "TAB_CriaBaralho_E" ) ;
#endif
      num = 13;
    }

#ifdef _DEBUG
    CNT_CONTAR( "TAB_CriaBaralho_F" ) ;
#endif

    carta->numero = num;

    if (i < 14) {
#ifdef _DEBUG
      CNT_CONTAR( "TAB_CriaBaralho_G" ) ;
#endif
      strcpy (carta->naipe, "Paus");
      strcpy (carta->cor, "Preto");
    }
    else if (i < 27) {
#ifdef _DEBUG
      CNT_CONTAR( "TAB_CriaBaralho_H" ) ;
#endif
      strcpy (carta->naipe, "Ouros");
      strcpy (carta->cor, "Vermelho");
    }
    else if (i < 40) {
#ifdef _DEBUG
      CNT_CONTAR( "TAB_CriaBaralho_I" ) ;
#endif
      strcpy (carta->naipe, "Copas");
      strcpy (carta->cor, "Vermelho");
    }
    else {
#ifdef _DEBUG
      CNT_CONTAR( "TAB_CriaBaralho_J" ) ;
#endif
      strcpy (carta->naipe, "Espadas");
      strcpy (carta->cor, "Preto");
    }

#ifdef _DEBUG
    CNT_CONTAR( "TAB_CriaBaralho_K" ) ;
#endif

    /* Insere a carta em um novo no ao fim da lista */
    p = (void*) carta;
    LIS_InserirElementoApos (pLista, p);

  }

#ifdef _DEBUG
  CNT_CONTAR( "TAB_CriaBaralho_L" ) ;
#endif

  return pLista;
}

/***********************************************************************
 *
 *  $FC Função: cria_tabuleiro
 *
 *  $ED Descrição da função
 *       Essa função inicializa o tabuleiro.
 *
 *  $FV Valor retornado
 *     (pLista) -> Retorna o tabuleiro criado.
 *
 ***********************************************************************/
LIS_tppLista cria_tabuleiro (LIS_tppLista seq_ordenada,
                             LIS_tppLista seq_visivel, LIS_tppLista extra) {
  void* p;
  LIS_tppLista pLista, pl;

#ifdef _DEBUG
  CNT_CONTAR( "TAB_CriaTabuleiro_A" ) ;
  assert( seq_ordenada != NULL ) ;
  assert( seq_visivel != NULL);
  assert( extra != NULL ) ;
#endif

  pLista = LIS_CriarLista (LIS_ExcluirValor);

  /* Adiciona a sequencia ordenada ao tabuleiro */
  IrInicioLista (seq_ordenada);

  while ((p = LIS_ObterValor (seq_ordenada)) != NULL) {
#ifdef _DEBUG
    CNT_CONTAR( "TAB_CriaTabuleiro_B" ) ;
#endif
    pl = (LIS_tppLista) malloc (sizeof (LIS_tppLista));
    pl = LIS_CriarLista (LIS_ExcluirValor);
    LIS_InserirElementoApos (pLista, pl);
    LIS_ExcluirElemento (seq_ordenada);
  }

#ifdef _DEBUG
  CNT_CONTAR( "TAB_CriaTabuleiro_C" ) ;
#endif

  LIS_DestruirLista (seq_ordenada);

  /* Adiciona as colunas do extra ao tabuleiro */
  IrInicioLista (extra);

  while ((p = LIS_ObterValor (extra)) != NULL) {
#ifdef _DEBUG
    CNT_CONTAR( "TAB_CriaTabuleiro_D" ) ;
#endif
    pl = (LIS_tppLista) malloc (sizeof (LIS_tppLista));
    pl = LIS_CriarLista (LIS_ExcluirValor);
    LIS_InserirElementoApos (pLista, pl);
    LIS_ExcluirElemento (extra);
  }

#ifdef _DEBUG
  CNT_CONTAR( "TAB_CriaTabuleiro_E" ) ;
#endif

  LIS_DestruirLista (extra);

  /* Adiciona a sequencia visivel ao tabuleiro */
  IrInicioLista (seq_visivel);

  while ((p = LIS_ObterValor (seq_visivel)) != NULL) {
#ifdef _DEBUG
    CNT_CONTAR( "TAB_CriaTabuleiro_F" ) ;
#endif
    pl = (LIS_tppLista) malloc (sizeof (LIS_tppLista));
    pl = LIS_CriarLista (LIS_ExcluirValor);
    LIS_InserirElementoApos (pLista, pl);
    LIS_ExcluirElemento (seq_visivel);
  }

#ifdef _DEBUG
  CNT_CONTAR( "TAB_CriaTabuleiro_G" ) ;
#endif

  LIS_DestruirLista (seq_visivel);

  return pLista;
}

/***********************************************************************
 *
 *  $FC Função: arruma_tabuleiro
 *
 *  $ED Descrição da função
 *       Essa função arruma as cartas no tabuleiro e deleta a lísta que
 *       referencia o baralho.
 *
 *  $EP Parâmetros
 *     $P tabuleiro - Corresponde a uma cabeca de lista que representa
 *                    o tabuleiro.
 *       baralho - Cabeça de lista de listas que representa o baralho.
 *
 *  $FV Valor retornado
 *     (1) -> Tabuleiro arrumado.
 *
 ***********************************************************************/
int arruma_tabuleiro (LIS_tppLista tabuleiro, LIS_tppLista baralho) {
  int i, j, n = 7;
  void* p;
  Carta* carta, *pc;
  LIS_tppLista cell;

#ifdef _DEBUG
  CNT_CONTAR( "TAB_ArrumaTabuleiro_A" ) ;
  assert( tabuleiro != NULL ) ;
  assert( baralho != NULL);
#endif

  /* Achar a primeira coluna do cascade */
  IrInicioLista (baralho);
  IrInicioLista (tabuleiro);
  LIS_AvancarElementoCorrente (tabuleiro, 8);

  /* Colocar as cartas nas colunas do cascade */
  for (i=0; i<8; i++) {
#ifdef _DEBUG
    CNT_CONTAR( "TAB_ArrumaTabuleiro_B" ) ;
#endif
    cell = (LIS_tppLista) LIS_ObterValor (tabuleiro);

    if (i > 3) {
#ifdef _DEBUG
      CNT_CONTAR( "TAB_ArrumaTabuleiro_C" ) ;
#endif
      n = 6;
    }

#ifdef _DEBUG
    CNT_CONTAR( "TAB_ArrumaTabuleiro_D" ) ;
#endif

    for (j=0; j<n; j++) {
#ifdef _DEBUG
      CNT_CONTAR( "TAB_ArrumaTabuleiro_E" ) ;
#endif

      IrFinalLista (cell);
      p = LIS_ObterValor (baralho);
      pc = (Carta*) p;
      carta = (Carta*) malloc (sizeof (Carta));
      carta->numero = pc->numero;
      strcpy (carta->naipe, pc->naipe);
      strcpy (carta->cor, pc->cor);
      p = (void*) carta;
      LIS_InserirElementoApos (cell, p);
      LIS_AvancarElementoCorrente (baralho, 1);
    }

#ifdef _DEBUG
    CNT_CONTAR( "TAB_ArrumaTabuleiro_F" ) ;
#endif

    LIS_AvancarElementoCorrente (tabuleiro, 1);
  }

#ifdef _DEBUG
  CNT_CONTAR( "TAB_ArrumaTabuleiro_G" ) ;
#endif

  LIS_EsvaziarLista (baralho);
  LIS_DestruirLista (baralho);

  return 1;
}

/***********************************************************************
 *
 *  $FC Função: conta_espacos_vazios
 *
 *  $ED Descrição da função
 *       Essa funcao determina quantas cartas podem ser movimentadas
 *       de uma so vez baseado no numero de espacos vazios do tabuleiro,
 *       a conta segue com base nessa equacao (Extra+1)*2*Cascade.
 *
 *  $EP Parâmetros
 *     $P pLista - Corresponde a uma cabeca de lista que representa
 *                    o tabuleiro.
 *
 *  $FV Valor retornado
 *     Numero de cartas que podem ser movidas.
 *
 ***********************************************************************/
int conta_espacos_vazios (LIS_tppLista pLista) {
  LIS_tppLista coluna;
  void *ps;
  int n, i = 0;

#ifdef _DEBUG
  CNT_CONTAR( "TAB_ContaEspacosVazios_A" ) ;
  assert( pLista != NULL ) ;
#endif

  IrInicioLista (pLista);

  LIS_AvancarElementoCorrente (pLista, 3);

  n = 0;
  while (LIS_AvancarElementoCorrente (pLista, 1) == LIS_CondRetOK) {
#ifdef _DEBUG
    CNT_CONTAR( "TAB_ContaEspacosVazios_B" ) ;
#endif
    coluna = (LIS_tppLista) LIS_ObterValor (pLista);
    ps = LIS_ObterValor (coluna);

    if (n < 4 && i == 0 && ps == NULL) {
#ifdef _DEBUG
      CNT_CONTAR( "TAB_ContaEspacosVazios_C" ) ;
#endif
      i = 2;
    }
    else if (n < 4 && ps == NULL) {
#ifdef _DEBUG
      CNT_CONTAR( "TAB_ContaEspacosVazios_D" ) ;
#endif
      i++;
    }
    else if (ps == NULL && i == 0) {
#ifdef _DEBUG
      CNT_CONTAR( "TAB_ContaEspacosVazios_E" ) ;
#endif
      i = 1;
    }
    else if (ps == NULL) {
#ifdef _DEBUG
      CNT_CONTAR( "TAB_ContaEspacosVazios_F" ) ;
#endif
      i *= 2;
    }

#ifdef _DEBUG
    CNT_CONTAR( "TAB_ContaEspacosVazios_G" ) ;
#endif

    n++;
  }

#ifdef _DEBUG
  CNT_CONTAR( "TAB_ContaEspacosVazios_H" ) ;
#endif

  IrInicioLista (pLista);

  return i;
}

/***********************************************************************
 *
 *  $FC Função: move_cartas
 *
 *  $ED Descrição da função
 *       Essa funcao movimenta as cartas do tabuleiro.
 *
 *  $EP Parâmetros
 *     $P tabuleiro - Corresponde a uma cabeca de lista que representa
 *                    o tabuleiro.
 *        s - Corresponde a coluna na qual as cartas serão retiradas.
 *        e - Corresponde a coluna na qual as cartas serão inseridas.
 *
 *  $FV Valor retornado
 *     (1) -> Cartas movidas com sucesso.
 *     (0) -> Erro ao mover cartas.
 *
 ***********************************************************************/
int move_cartas (LIS_tppLista pLista, int s, int e) {
  LIS_tppLista entrada, saida;
  int te, ts, num_cartas, num_vazio;
  void* ps;

#ifdef _DEBUG
  CNT_CONTAR( "TAB_MoveCartas_A" ) ;
  assert( pLista != NULL ) ;
  assert( s >= 0 && s < 17 );
  assert( e >= 0 && s < 17 );
#endif

  /* Conto quantas cartas eu posso mexer se uma vez baseado no
     numero de espacos vazios no tabuleiro */
  num_vazio = conta_espacos_vazios (pLista);
  if (num_vazio == 0) {
#ifdef _DEBUG
    CNT_CONTAR( "TAB_MoveCartas_B" ) ;
#endif
    num_vazio = 1;
  }

#ifdef _DEBUG
  CNT_CONTAR( "TAB_MoveCartas_C" ) ;
#endif

  /* Pega a cabeca de lista da onde as cartas serao retiradas */
  IrInicioLista (pLista);
  LIS_AvancarElementoCorrente (pLista, s - 1);
  saida = (LIS_tppLista) LIS_ObterValor (pLista);
  ps = LIS_ObterValor (saida);

  /* Conto quantas cartas estao sendo movidas */
  num_cartas = 1;
  while (LIS_AvancarElementoCorrente (saida, 1) == LIS_CondRetOK) {
#ifdef _DEBUG
    CNT_CONTAR( "TAB_MoveCartas_D" ) ;
#endif
    num_cartas++;
  }

#ifdef _DEBUG
  CNT_CONTAR( "TAB_MoveCartas_E" ) ;
#endif

  /* Testo se consigo mexer esse numero de cartas */
  if (num_cartas > num_vazio) {
#ifdef _DEBUG
    CNT_CONTAR( "TAB_MoveCartas_F" ) ;
#endif
    return 0;
  }

#ifdef _DEBUG
  CNT_CONTAR( "TAB_MoveCartas_G" ) ;
#endif

  IrInicioLista (saida);
  LIS_ProcurarValor (saida, ps);

  /* Pega a cabeca de lista da onde as cartas serao colocadas */
  IrInicioLista (pLista);
  LIS_AvancarElementoCorrente (pLista, e - 1);
  entrada = (LIS_tppLista) LIS_ObterValor (pLista);

  if (s > 8) {
#ifdef _DEBUG
    CNT_CONTAR( "TAB_MoveCartas_H" ) ;
#endif
    ts = testa_saida_sequencia_visivel (saida);
  }
  else if (s > 4) {
#ifdef _DEBUG
    CNT_CONTAR( "TAB_MoveCartas_I" ) ;
#endif
    ts = testa_saida_extra (saida);
  }
  else {
#ifdef _DEBUG
    CNT_CONTAR( "TAB_MoveCartas_J" ) ;
#endif
    ts = 0;
  }

#ifdef _DEBUG
  CNT_CONTAR( "TAB_MoveCartas_K" ) ;
#endif

  if (ts == 0) {
#ifdef _DEBUG
    CNT_CONTAR( "TAB_MoveCartas_L" ) ;
#endif
    return 0;
  }

#ifdef _DEBUG
  CNT_CONTAR( "TAB_MoveCartas_M" ) ;
#endif

  IrInicioLista (saida);
  LIS_ProcurarValor (saida, ps);

  if (e > 8) {
#ifdef _DEBUG
    CNT_CONTAR( "TAB_MoveCartas_N" ) ;
#endif
    te = testa_entrada_sequencia_visivel (entrada, saida);
  }
  else if (e > 4) {
#ifdef _DEBUG
    CNT_CONTAR( "TAB_MoveCartas_O" ) ;
#endif
    te = testa_entrada_extra (entrada, saida);
  }
  else {
#ifdef _DEBUG
    CNT_CONTAR( "TAB_MoveCartas_P" ) ;
#endif
    te = testa_entrada_sequencia_ordenada (entrada, saida);
  }

#ifdef _DEBUG
  CNT_CONTAR( "TAB_MoveCartas_Q" ) ;
#endif

  if ((ts == 1) && (te == 1)) {
#ifdef _DEBUG
    CNT_CONTAR( "TAB_MoveCartas_R" ) ;
#endif
    LIS_InsereBloco (entrada, saida);
    return 1;
  }

#ifdef _DEBUG
  CNT_CONTAR( "TAB_MoveCartas_S" ) ;
#endif

  return 0;
}
