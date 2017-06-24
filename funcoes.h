#include "constantes.h"

// Procedimento para mudar a cor da fonte
// Parametros: cor da letra, cor de fundo
void corFonte( const char * const corLetra, const char * const corFundo ) {
  int corL = 0, corF = 0;

  if ( corLetra == "preto" ) corL = 30;
  if ( corLetra == "vermelho" ) corL = 31;
  if ( corLetra == "verde" ) corL = 32;
  if ( corLetra == "amarelo" ) corL = 33;
  if ( corLetra == "azul" ) corL = 34;
  if ( corLetra == "rosa" ) corL = 35;
  if ( corLetra == "ciano" ) corL = 36;
  if ( corLetra == "branco" ) corL = 37;

  if ( corFundo == "preto" ) corF = 40;
  if ( corFundo == "vermelho" ) corF = 41;
  if ( corFundo == "verde" ) corF = 42;
  if ( corFundo == "amarelo" ) corF = 43;
  if ( corFundo == "azul" ) corF = 44;
  if ( corFundo == "rosa" ) corF = 45;
  if ( corFundo == "ciano" ) corF = 46;
  if ( corFundo == "branco" ) corF = 47;

  if ( SO == 'x' ) // Se o sistema operacional for Unix/Linux
    cout << "\e[" << corF << ";" << corL << ";1m"; // Usa os comandos do shell
}

// Procedimento para limpar a tela
// Parametros: nenhum
void limpaTela( void ) {
  if ( SO == 'x' ) // Se o sistema operacional for Unix/Linux
    cout << "\e[H\e[2J"; // Usa os comandos do shell
  else // Se o sistema operacional for Windows
    system( "CLS" );
}

// Procedimento para dar pausa na tela
// Parametros: nenhum
void pausa( void ) {
  if ( SO == 'x' ) { // Se o sistema operacional for Unix/Linux
    corFonte( "verde", COR_FUNDO );
    cout << "\nTecle < ENTER > para continuar...\n";
    corFonte( "branco", COR_FUNDO );
    system( "read -r REPLY" );
  } else { // Se o sistema operacional for Windows
    cout << endl;
    system( "PAUSE" );
  }
}

// Procedimento para replicar um caracter n vezes
// Parametros: caractere a ser impresso, numero de vezes para ser impresso
void replica( char caractere, int nvezes ) {
  for ( int i = 1; i <= nvezes; i++ )
    cout << caractere;

  cout << endl;
}

// Procedimento para exibir mensagem na tela
// Parametros: texto da mensagem
void mensagem( const char * const aviso ) {
  cout << endl;
  corFonte( "branco", "vermelho" );
  replica( '*', strlen( aviso ) + 8 );
  cout << "*** " << aviso << " ***\n";
  replica( '*', strlen( aviso ) + 8 );
  corFonte( "branco", COR_FUNDO );
  pausa();
}

// Procedimento para exibir um titulo destacado na tela
// Parametros: texto do titulo, caractere para as linhas, tamanho da linha
void titulo( const char * const texto, char caractere, int tamanhoLinha ) {
  corFonte( "branco", COR_FUNDO );
  limpaTela();
  replica( caractere, tamanhoLinha );
  corFonte( "amarelo", COR_FUNDO );
  cout << texto << "\n";
  corFonte( "branco", COR_FUNDO );
  replica( caractere, tamanhoLinha );
  corFonte( "branco", COR_FUNDO );
}

// Procedimento para exibir um texto colorido
// Parametros: texto, cor da letra
void textoColorido( const char * const texto, const char * const cor ) {
  corFonte( cor, COR_FUNDO );
  cout << texto;
  corFonte( "branco", COR_FUNDO );
}
