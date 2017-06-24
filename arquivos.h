#include <fstream>
#include "constantes.h"

// Rotina para criar os arquivos que nao existirem
void criaArquivos( void ) {
  // Cria o arquivo simulados.dat
  // Estrutura: codigo do simulado, descricao do simulado
  ifstream inSimulados( "simulados.dat", ios::in );

  if ( !inSimulados ) { // Se o arquivo nao existir, deve cria-lo
    ofstream outSimulados( "simulados.dat", ios::out );

    outSimulados << "1 Simulado de Windows\n";
    outSimulados << "2 Simulado de Linux\n";

    outSimulados.close();
  }
  inSimulados.close();

  // Cria o arquivo perguntas.dat
  // Estrutura: codigo do simulado, codigo da pergunta, descricao da pergunta
  ifstream inPerguntas( "perguntas.dat", ios::in );

  if ( !inPerguntas ) { // Se o arquivo nao existir, deve cria-lo
    ofstream outPerguntas( "perguntas.dat", ios::out );

    outPerguntas << "1 1 O que significa Windows?\n";
    outPerguntas << "1 2 Qual empresa e proprietaria do Windows?\n";
    outPerguntas << "1 3 Qual tecla de atalho fecha uma janela no Windows?\n";
    outPerguntas << "1 4 Qual e o pacote de escritorios do Windows?\n";
    outPerguntas << "1 5 Qual e a ultima versao do Windows?\n";

    outPerguntas << "2 1 O que e o Linux?\n";
    outPerguntas << "2 2 Quem criou o Linux?\n";
    outPerguntas << "2 3 Em quantos tipos de computador o Linux e usado?\n";
    outPerguntas << "2 4 Qual e o gerenciador de janelas mais usado no Linux?\n";
    outPerguntas << "2 5 O que significa LAMP?\n";
    outPerguntas << "2 6 Qual das distribuicoes Linux abaixo e a mais antiga?\n";

    outPerguntas.close();
  }
  inPerguntas.close();

  // Cria o arquivo respostas.dat
  // Estrutura: codigo do simulado, codigo da pergunta, codigo da resposta,
  // resposta correta (s/n), descricao da resposta
  ifstream inRespostas( "respostas.dat", ios::in );

  if ( !inRespostas ) { // Se o arquivo nao existir, deve cria-lo
    ofstream outRespostas( "respostas.dat", ios::out );

    // Respostas de Windows
    outRespostas << "1 1 1 s Janelas\n";
    outRespostas << "1 1 2 n Portas\n";
    outRespostas << "1 1 3 n Telhados\n";
    outRespostas << "1 1 4 n Quartos\n";

    outRespostas << "1 2 1 n IBM\n";
    outRespostas << "1 2 2 s Microsoft\n";
    outRespostas << "1 2 3 n HP\n";

    outRespostas << "1 3 1 n Shift+F4\n";
    outRespostas << "1 3 2 n Ctrl+F4\n";
    outRespostas << "1 3 3 s Alt+F4\n";
    outRespostas << "1 3 4 n Ctrl+Alt+Del\n";

    outRespostas << "1 4 1 n OpenOffice\n";
    outRespostas << "1 4 2 s MS Office\n";
    outRespostas << "1 4 3 n StarOffice\n";

    outRespostas << "1 5 1 s Vista\n";
    outRespostas << "1 5 2 n 2003\n";
    outRespostas << "1 5 3 n XP\n";

    // Respostas de Linux
    outRespostas << "2 1 1 n Um sistema de arquivos\n";
    outRespostas << "2 1 2 s Um sistema operacional\n";
    outRespostas << "2 1 3 n Um sistema de automacao\n";
    outRespostas << "2 1 4 n Um sistema de redes\n";

    outRespostas << "2 2 1 n Richard Stallman\n";
    outRespostas << "2 2 2 n Andrew Tanembaum\n";
    outRespostas << "2 2 3 s Linus Torvalds\n";

    outRespostas << "2 3 1 n Em pc's\n";
    outRespostas << "2 3 2 n Em Mainframes\n";
    outRespostas << "2 3 3 s Na maioria das arquiteturas\n";
    outRespostas << "2 3 4 n Em palmtops\n";

    outRespostas << "2 4 1 n GNOME\n";
    outRespostas << "2 4 2 s KDE\n";
    outRespostas << "2 4 3 n WindowMaker\n";
    outRespostas << "2 4 4 n Fluxbox\n";

    outRespostas << "2 5 1 n Sistema de arquivos lampada\n";
    outRespostas << "2 5 2 s Linux/Apache/Mysql/Php\n";
    outRespostas << "2 5 3 n Linux Advanced Media Player\n";

    outRespostas << "2 6 1 n RedHat\n";
    outRespostas << "2 6 2 n Debian\n";
    outRespostas << "2 6 3 s Slackware\n";
    outRespostas << "2 6 4 n SuSE\n";
    outRespostas << "2 6 5 n Mandriva\n";
    outRespostas << "2 6 6 n Gentoo\n";

    outRespostas.close();
  }
  inRespostas.close();
}
