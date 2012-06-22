#include "corpusmatriz.h"

CorpusMatriz::CorpusMatriz( vector<string> atributos )
    :Corpus( atributos )
{
    //ctor
}

bool CorpusMatriz::carregarArquivo( string arquivo )
{
    ifstream arqin( arquivo.c_str() ); // Abre arquivo para leitura em modo texto
    if( !arqin.is_open() ) //verifica se arquivo conseguiu ser aberto
    {
        cout << "Erro:carregarArquivo!\nFalha na abertura do arquivo!" << endl;
        return false;
    }

    string str;
    int row = 0, column = 0, contador = -1,count = 0;
    char ch;

    // l� um caracter inicial do arquivo
    arqin.get( ch );

    while( arqin.good() ) // Enquanto n�o for fim de arquivo e a leitura n�o contiver erros
    {
        if ( ch != '[' && ch != '#' )
        {
            if( ch != '\n' ) //considera frases com distancia maior que 1 espa�o
            {
                for( register int i = 0; i < qtd_atributos; i++ )
                {
                    // l� a palavra que ser� colocada no vector s�mbolos
                    while( ( ch != '_' || i == qtd_atributos - 1 ) && ch != '\n' && !arqin.eof() ) //torna programa mais
                    {                                                              //robusto em rela��o a erros '_' no corpus
                        str.push_back( ch );
                        arqin.get( ch );
                    }
                    if ( dicionario.find( str ) == dicionario.end() )
                    {
                        dicionario[ str ] = ++contador; // nessa linha primeiro cria-se um elemento(ou seja, aumenta o size),
                                                                   // depois realiza-se a atribui��o
                        simbolos.push_back( str );
                        //if( i == 1 ) cout << str << endl;
                    }
                    count++;
                    frases[ row ][ column ][ i ] = dicionario[ str ];
                    str.clear();    // limpa str para armazenar a pr�xima string
                    arqin.get( ch );
                }
            }

            if( arqin.eof() ) //arquivo terminando sem linha em branco
            {
                qtd_sentencas = frases.size(); //atualiza qtd de sentencas
                qtd_simbolos = simbolos.size(); //atualiza qtd de simbolos
                break;
            }

            if( ch == '\n' ) //verifica se ha mudan�a de frase
            {
                if( arqin.get( ch ) && !arqin.eof() && ch != '\n') //caso em que ha nova frase
                {
                    frases.resize( ++row + 1 ); //desloca para a proxima linha na matriz ( proxima frase no texto )
                    frases[row].resize(1);
                    frases[row][0].resize( qtd_atributos );
                    column = 0;
                }
                if( arqin.eof() )
                {
                    qtd_sentencas = frases.size(); //atualiza qtd de sentencas
                    qtd_simbolos = simbolos.size(); //atualiza qtd de simbolos
                    break;
                }
            }
            else
            {
            frases[row].resize( ++column + 1 ); //desloca p/ o proximo elemento da matriz na mesma linha
            frases[row][column].resize( qtd_atributos );
        }
        }
        else
        {
            arqin.ignore( INF, '\n' );
            arqin.get( ch );
        }
    }

    if( arqin.bad() && !arqin.eof() )    //caso de erro na leitura do arquivo
    {
        cout << "Erro:carregarArquivo!\nErro na leitura do arquivo!" << endl;
        arqin.close();
        return false;
    }

    arqin.close();
    cout << "Arquivo <" << arquivo << "> carregado com sucesso!" << endl;
    return true;
}

bool CorpusMatriz::gravarArquivo( string arquivo )
{
//    /// TESTE DE IMPRESS�O DE "FRASES[][][]"
//    for ( register int i = 0; i < qtd_sentencas; i++ )
//    {
//    	for ( register int j = 0; j < (int)frases[ i ].size(); j++ )
//    	{
//    		cout << frases[i][j][0] << "_" << frases[i][j][1] << "_" << frases[i][j][2] << endl;
//    	}
//    	cout << "Mudou de linha" << count++ << endl;
//    }
//
//    cout << "Terminou" << endl;

    ofstream arqout( arquivo.c_str() ); //Abre arquivo para escrita em modo texto
    if( !arqout.is_open() ) //verifica se arquivo conseguiu ser aberto
    {
        cout << "Erro:gravarArquivo!\nFalha na abertura do arquivo!" << endl;
        return false;
    }

    int column;

    for( register int i = 0; i < qtd_sentencas; i++ )
    {
        column = frases[i].size();
        for( register int j = 0; j < column; j++ )
            for( register int k = 0; k < qtd_atributos; k++ )
            {
                if( k == qtd_atributos - 1 ) arqout << simbolos[ frases[i][j][k] ] << endl;
                else arqout << simbolos[ frases[i][j][k] ] << '_';
            }
        arqout << endl;
    }

    arqout.close();

    cout << "Arquivo <" << arquivo << "> gravado com sucesso!" << endl;
    return true;
}
