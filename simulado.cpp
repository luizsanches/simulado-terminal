/*
 Programa.......: Simulado Virtual
 Projetado em...: 26 de Outubro  de 2006
 Criado em......: 02 de Novembro de 2006
 Desenvolvedores: Luiz Sanches
 Objetivo.......: Atraves da leitura de arquivos textos, criar rapidamente
                  simulados virtuais para qualquer instituicao de ensino
                  obtendo um resultado rapido dos testes realizados pelos alunos.
*/

// Inclusao de bibliotecas
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "funcoes.h"
#include "arquivos.h"
#include "resultados.h"
#include "constantes.h"

// Prototipos de funcoes
void realizaSimulados( void );
void criaArquivos( void );
void limpaTela( void );
void pausa( void );
void replica( char, int );
void mensagem( const char * const );
void titulo( const char * const , char, int );
void corFonte( const char * const, const char * const );
void textoColorido( const char * const, const char * const );
void sobreSistema( void );
void resultados( void );

char nomeUsuario[15]; // Variavel global para o nome do usuario

// Menu principal
int main() {
	criaArquivos(); // Cria os arquivos de dados que nao existem

	// Pede a digitacao do nome do usuario
	titulo( "Simulado Virtual - Acesso ao Sistema", '=', REPETE + 10 );
	textoColorido( "\nDigite seu primeiro nome: ", "amarelo" );
	corFonte( "verde", COR_FUNDO );
	cin >> nomeUsuario;
	corFonte( "branco", COR_FUNDO );
	replica( '-', REPETE + 10 );

	int opcao = 1;

	while ( opcao != 0 ) {
		titulo( "Simulado Virtual", '=', REPETE );
		textoColorido( "Por: Luiz Sanches\n", "verde" );

		corFonte( "branco", COR_FUNDO );
		replica( '-', REPETE );
		cout << "\n1 - Realizar Simulados\n\n";
		cout << "2 - Resultados\n\n";
		cout << "3 - Sobre o Sistema\n\n";
		textoColorido( "0 - Sair\n\n", "amarelo" );
		replica( '-', REPETE );

		textoColorido( "Escolha uma opcao: ", "amarelo" );
		corFonte( "verde", COR_FUNDO );
		cin >> opcao;
		corFonte( "branco", COR_FUNDO );

		switch ( opcao ) {
			case 0:
				break;
			case 1:
				realizaSimulados();
				break;
			case 2:
				resultados();
				break;
			case 3:
				sobreSistema();
				break;
			default:
				mensagem( "OPCAO INVALIDA" );
				break;
		}
	}

	corFonte( "branco", "preto" );
	limpaTela();
	return 0;
}

// Rotina para realizar os simulados
void realizaSimulados( void ) {
	// Criacao de constantes
	const int MAX = 80;

	// Criacao de variaveis
	int op = 1;
	char opSimulado;
	char opPergunta;
	char opResposta;
	char respostaCorreta;
	int respostaMaxima;

	int i;

	int achouSimulado;
	int achouResposta;

	float numeroQuestoes;
	float numeroAcertos;
	float numeroErros;

	float percentualTotal = 0;
	float percentualAcertos = 0;
	float percentualErros = 0;

	time_t dataSistema;
	struct tm *dataExpandida;
	char dataAtual[11];

	// Criacao de vetores
	char texto[ MAX ] = { "" };
	char textoPergunta[ MAX ] = { "" };
	char simulado[ MAX ] = { "" };

	while ( op != 0 ) {
		achouSimulado = 0;
		achouResposta = 0;

		numeroQuestoes = 0;
		numeroAcertos = 0;
		numeroErros = 0;

		limpaTela();

		// Abertura do arquivo de simulados
		ifstream inSimulados( "simulados.dat", ios::in );

		// Se nao conseguir abrir o arquivo, emite uma mensagem de erro
		if ( !inSimulados ) {
			cerr << "\nArquivo nao pode ser aberto\n";
			inSimulados.close();
			pausa();
		}
		else {
			// Se conseguiu abrir o arquivo, exibe o conteudo do mesmo
			titulo( "Realizar Simulados", '=', REPETE );

			// Exibe os simulados
			while ( inSimulados ) {
				inSimulados.getline( texto, MAX );

				if ( strlen(texto) > 0 ) {
					cout << '\n' << texto[ 0 ] << " - "; // Imprime o codigo do simulado

					// Imprime o nome do simulado
					for ( i = 2; texto[ i ] != '\0'; i++ )
						cout << texto[ i ];

					cout << '\n';
				}
			}

			textoColorido( "\n0 - Voltar\n\n" , "amarelo" );
			replica( '-', REPETE );

			// Pede a digitacao do numero do simulado
			textoColorido( "Escolha o simulado: ", "amarelo" );
			corFonte( "verde", COR_FUNDO );
			cin >> op;
			corFonte( "branco", COR_FUNDO );

			if ( op == 0 )
				break;

			// Conversao de inteiro para caractere
			op = op + 48; // Em ascii 48-57 = 0-9
			opSimulado = (char) op;

			inSimulados.clear(); // Desliga fim de arquivo para proxima entrada
			inSimulados.seekg( 0 ); // Vai para o inicio do arquivo

			// Procura o codigo do simulado no arquivo simulados.dat
			while ( inSimulados ) {
				inSimulados.getline( texto, MAX ); // Seleciona a linha do arquivo

				// Se a posicao zero da linha for igual ao simulado escolhido
				if ( texto[0] == opSimulado ) {
					for ( i = 0; i < MAX; i++ )
						simulado[ i ] = texto[ i ];

					achouSimulado = 1;
					break;
				}
			}
			inSimulados.close(); // Fecha o arquivo de simulados

			if ( achouSimulado ) { // Abre o arquivo perguntas.dat
				ifstream inPerguntas( "perguntas.dat", ios::in );

				if ( !inPerguntas ) {
					cerr << "\nArquivo de perguntas nao pode ser aberto\n";
					inPerguntas.close();
					pausa();
				} else {
					// Procura as perguntas no arquivo
					while ( inPerguntas ) {
						inPerguntas.getline( textoPergunta, MAX );

						// Se a linha for do simulado selecionado, realiza a pergunta
						if ( textoPergunta[0] == opSimulado ) {
							numeroQuestoes++;

							op = 1;
							// Executa o laco enquanto nao abandonar o simulado
							while ( op != 0 ) {
								limpaTela();

								replica( '=', REPETE + 30 );
								corFonte ( "amarelo", COR_FUNDO );

								// Exibe o nome do simulado
								for ( i = 2; i < strlen(simulado); i++ )
									cout << simulado[ i ];

								textoColorido(" - Usuario: " , "verde" );
								textoColorido(nomeUsuario , "verde" );
								cout << '\n';
								corFonte ( "branco", COR_FUNDO );
								replica( '=', REPETE + 30 );
								cout << '\n';

								// Exibe a pergunta
								corFonte( "verde", COR_FUNDO );

								opPergunta = textoPergunta[ 2 ];

								//cout << opPergunta << " - ";

								for ( i = 4; textoPergunta[ i ] != '\0'; i++ )
									cout << textoPergunta[ i ];

								cout << "\n\n";

								corFonte( "branco", COR_FUNDO );

								// Abre o arquivo de respostas
								ifstream inRespostas( "respostas.dat", ios::in );

								if ( !inRespostas ) {
									cerr << "\nArquivo de respostas nao pode ser aberto\n";
									inRespostas.close();
									pausa();
								} else {
									// Procura as respostas da pergunta no arquivo
									respostaCorreta = ' ';
									respostaMaxima = 0;
									achouResposta = 0;

									while ( inRespostas ) {
										inRespostas.getline( texto, MAX );

										// Se a linha for do simulado
										// e pergunta selecionada, exibe a resposta
										if ( texto[ 0 ] == opSimulado && texto[ 2 ] == opPergunta ) {
											achouResposta = 1;
											respostaMaxima++;

											if ( texto[ 6 ] == 's' ) // Se a resposta for correta='s'
												respostaCorreta = texto[ 4 ]; // Pega o numero da resposta

											cout << texto[ 4 ] << " - "; // Imprime o numero da resposta

											// Exibe a resposta
											for ( i = 8; texto[ i ] != '\0'; i++ )
												cout << texto[ i ];

											cout << endl << endl;
										}
									}
									inRespostas.close();

									// Se achou a resposta da pergunta
									if ( achouResposta ) {
										textoColorido( "0 - Abandona\n\n", "amarelo" );
										replica( '-', REPETE + 30 );
										textoColorido( "Escolha a resposta: ", "amarelo" );
										corFonte( "verde", COR_FUNDO );
										cin >> op;
										corFonte( "branco", COR_FUNDO );

										if ( op == 0 ) // Se for zero abandona o simulado
											break;

										// Se a opcao escolhida for valida
										if ( op >= 1 && op <= respostaMaxima ) {
											// Conversao de inteiro para caractere
											op = op + 48; // Em ascii 48-57 = 0-9
											opResposta = (char) op;

											if ( opResposta == respostaCorreta ) {
												numeroAcertos++;
												mensagem( "PARABENS! RESPOSTA CORRETA" );
												break;
											} else {
												numeroErros++;
												mensagem( "QUE PENA, RESPOSTA INCORRETA" );
												break;
											}
										} else
											mensagem( "RESPOSTA INVALIDA" );

									} // Fim da condicao se achou a resposta
								} // Fim da condicao se abriu o arquivo de respostas
							} // Fim do laco de escolha da resposta

							if ( op == 0 ) { // Se for zero abandona o simulado
								numeroQuestoes--; // Substrai o n. de questoes para o resultado
								break;
							}

						} // Fim da condicao se encontrou a pergunta do simulado escolhido
					} // Fim do laco de leitura do arquivo de perguntas
					inPerguntas.close(); // Fecha o arquivo de perguntas

					if ( numeroQuestoes > 0 ) {
						// Exibe o resultado do simulado
						percentualAcertos = ( numeroAcertos / numeroQuestoes ) * 100;
						percentualErros = ( numeroErros / numeroQuestoes ) * 100;
						percentualTotal = percentualAcertos + percentualErros;

						titulo( "Resultado do Simulado", '=', REPETE );
						textoColorido( "\nAcertos: ", "amarelo" );
						cout << numeroAcertos << " - " << (int) percentualAcertos << "%\n";

						textoColorido( "\nErros..: ", "amarelo" );
						cout << numeroErros << " - " << (int) percentualErros << "%\n\n";

						replica( '-', REPETE );
						textoColorido( "\nTotal..: ", "amarelo" );
						cout << numeroQuestoes << " - " << percentualTotal << "%\n";

						// Recupera a data atual do sistema
						dataSistema = time( NULL );
						dataExpandida = localtime( &dataSistema );
						strftime( dataAtual, 11, "%d %m %Y", dataExpandida );

						// Grava no arquivo resultados.dat
						ofstream outResultados( "resultados.dat", ios::app );

						outResultados << dataAtual << ' ' <<nomeUsuario << ' ' << opSimulado
									<< ' ' << numeroAcertos << ' ' << numeroErros
									<< ' ' << numeroQuestoes << '\n';
						outResultados.close();

						pausa();
					}
				} // Fim da condicao se abriu o arquivo de perguntas
			} else {
				mensagem( "O SIMULADO NAO FOI ENCONTRADO" );

			} // Fim da condicao se achou o simulado no arquivo
		} // Fim da condicao se abriu o arquivo de simulados
	} // Fim do laco de escolha do simulado
} // Fim da rotina para realizar simulados

// Procedimento para exibir a tela de informacao sobre o sistema
void sobreSistema( void ) {
	titulo( "Sobre o Simulado Virtual", '=', REPETE + 18 );
	cout << "\n Instituto de Estudos Superiores da Amazonia - IESAM";
	cout << "\n Curso de Bacharelado em Sistemas de Informacao";
	cout << "\n 1o Ano - Novembro de 2006";
	cout << "\n Algoritmo e Programacao - C++";
	cout << "\n Profa. Lenilda Pinheiro";
	cout << "\n Aluno: Luiz Sanches\n\n";
	replica( '-', REPETE + 18 );
	pausa();
}

