#include "constantes.h"

// Procedimento para exibir os resultados dos simulados
void resultados( void ) {
  int numeroMes, dia, mes, ano, simulado, acertos, erros, questoes;
  string usuario;

  int totalSimulados = 0;
  int totalAcertos = 0;
  int totalErros = 0;
  int totalQuestoes = 0;

  string rUsuario;
  int rAcertos, rErros;
  char achouRankingUsuario;

  int maiorAcerto = 0;
  int maiorErro = 0;
  string usuarioMaisAcertou;
  string usuarioMaisErrou;

  titulo( "Resultados", '=', REPETE + 10 );
  textoColorido( "\nDigite o n. do mes da pesquisa: ", "amarelo" );
  corFonte( "verde", COR_FUNDO );
  cin >> numeroMes;
  corFonte( "branco", COR_FUNDO );

  // Limpa o arquivo de ranking
  ofstream delRanking( "ranking.dat", ios::trunc );
  delRanking.close();

  // Abre o arquivo de resultados para leitura
  ifstream inResultados( "resultados.dat", ios::in );

  if ( inResultados ) { // Se conseguiu abri-lo
    inResultados >> dia >> mes >> ano >> usuario >> simulado >> acertos >> erros >> questoes;

    while ( !inResultados.eof() ) { // Executa ate chegar ao final do arquivo
      if ( numeroMes == mes ) { // Se for do mes escolhido
        totalSimulados++;
        totalAcertos += acertos;
        totalErros += erros;
        totalQuestoes += questoes;

        achouRankingUsuario = 'n';

        // Abre o arquivo de ranking para leitura
        ifstream inRanking( "ranking.dat" );

        if ( inRanking ) { // Se conseguiu abri-lo
          inRanking >> rUsuario >> rAcertos >> rErros; // Le a primeira linha do arquivo

          while ( !inRanking.eof() ) { // Executa enquanto nao chegar no final dele
            // Se encontrar o usuario no arquivo de ranking, na grava-lo mais no ranking
            if ( usuario == rUsuario ) {
              achouRankingUsuario = 's';
              break;
            }

            inRanking >> rUsuario >> rAcertos >> rErros; // Le a proxima linha do arquivo
          }
        }
        inRanking.close();

        // Se nao achou o usuario no arquivo de ranking, deve grava-lo
        if ( achouRankingUsuario == 'n' ) {
          rUsuario = usuario;
          rAcertos = 0;
          rErros = 0;

          // Abre o arquivo de resultados para leitura de acertos e erros do usuario
          ifstream inTotais( "resultados.dat" );

          if ( inTotais ) { // Se conseguiu abri-lo
            inTotais >> dia >> mes >> ano >> usuario >> simulado >> acertos >> erros >> questoes;

            while ( !inTotais.eof() ) {
              // Soma dos acertos e erros do usuario e mes selecionado
              if ( usuario == rUsuario && numeroMes == mes ) {
                rAcertos += acertos;
                rErros += erros;
              }

              inTotais >> dia >> mes >> ano >> usuario >> simulado >> acertos >> erros >> questoes;
            }
          }
          inTotais.close();

          // Abre o arquivo de ranking para gravacao
          ofstream outRanking ( "ranking.dat" , ios::app );
          outRanking << rUsuario << ' ' << rAcertos << ' ' << rErros << '\n';
          outRanking.close();
        }
      }

      inResultados >> dia >> mes >> ano >> usuario >> simulado >> acertos >> erros >> questoes;
    }
    inResultados.close();

    // Abre o arquivo de ranking para leitura dos melhores e piores desempenhos
    ifstream inRanking( "ranking.dat" );

    if ( inRanking ) { // Se conseguiu abri-lo
      inRanking >> rUsuario >> rAcertos >> rErros; // Le a primeira linha do arquivo

      while ( !inRanking.eof() ) { // Executa enquanto nao chegar no final dele
        if ( rAcertos > maiorAcerto ) {
          maiorAcerto = rAcertos;
          usuarioMaisAcertou = rUsuario;
        }

        if ( rErros > maiorErro ) {
          maiorErro = rErros;
          usuarioMaisErrou = rUsuario;
        }

        inRanking >> rUsuario >> rAcertos >> rErros; // Le a proxima linha do arquivo
      }
    }
    inRanking.close();
  }

  if ( totalSimulados > 0 ) {
    textoColorido( "\nSimulados realizados....: ", "amarelo" );
    cout << totalSimulados << endl;
    textoColorido( "\nTotal/Media de Acertos..: ", "amarelo" );
    cout << totalAcertos << " / " << totalAcertos/totalSimulados << endl;
    textoColorido( "\nTotal/Media de Erros....: ", "amarelo" );
    cout << totalErros << " / " << totalErros/totalSimulados << endl;
    textoColorido( "\nUsuario que mais acertou: ", "amarelo" );
    cout << usuarioMaisAcertou << " ( " << maiorAcerto << " )" << endl;
    textoColorido( "\nUsuario que mais errou..: ", "amarelo" );
    cout << usuarioMaisErrou << " ( " << maiorErro << " )" << endl;
    cout << endl;
    replica( '-', REPETE + 10 );
    pausa();
  } else
    mensagem( "RESULTADOS NAO ENCONTRADOS" );
}
