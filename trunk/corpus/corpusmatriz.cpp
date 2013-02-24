#include "corpusmatriz.h"

CorpusMatriz::CorpusMatriz( vector<string> atributos, char separador, bool dividirExemplos)
    :Corpus( atributos )
{
    //ctor
    this->separador = separador;
    this->dividirExemplos = dividirExemplos;
}

void CorpusMatriz::ajustarSeparador( char separador )
{
    this->separador = separador;
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
    char ch;

    //verifica se atributos foram passados
    if (!atributos.size())
    {
        string at;
        ifstream arqat( (arquivo + ".names").c_str() ); // Abre arquivo para leitura em modo texto
        if( !arqat.is_open() ) //verifica se arquivo conseguiu ser aberto
        {
            at = "";
            arqin.get( ch );
            if( ch == '[' )
            {
                char s[1000];
                arqin.get( s, 1000, '\n' );
                string str(s);
                int i = 0;
                //apaga espa�os em branco da string
                for( string::iterator it = str.begin(); it != str.end(); )
                    if( *it == ' ' ) it = str.erase( it );
                    else ++it;

                while( str[i] != '=' )
                    at += str[i++];
                if( at == "features" )
                {
                    while( str[i] != ']' )
                    {
                        at = "";
                        while( str[++i] != ',' && str[i] != ']' )
                            at += str[i];
                        atributos.push_back( at );
                    }
                    if( str[++i] == '[' )
                    {
                        at = "";
                        while( str[++i] != '=' && str[i] != ']' )
                            at += str[i];
                        if( at == "separator" )
                            separador = str[++i];
                    }
                    arqin.seekg( 0, ios::beg );
                }
                else
                {
                    cout << "Aviso:carregarArquivo!\nN�o foi poss�vel carregar atributos!" << endl;
                    return false;
                }
            }
            else
            {
                cout << "Aviso:carregarArquivo!\nN�o foi poss�vel carregar atributos!" << endl;
                return false;
            }
        }
        else
        {
            //varre linha a linha por atributos
            while(arqat.good())
            {
                arqat >> at;
                if (arqat.eof())
                    break;
                atributos.push_back(at);
            }
            arqat.close();
        }

        //realoca membros em fun��o de novos atributos do corpus
        qtd_atributos = atributos.size();
        for( register int i = 0; i < qtd_atributos; ++i )
            posAtributos[atributos[i]] = i;

        //verifica se os atributos foram carregados
        if( !qtd_atributos )
        {
            cout << "Aviso:carregarArquivo!\nN�o foi poss�vel carregar atributos!" << endl;
            return false;
        }
        else
            cout << qtd_atributos << " atributos carregados com sucesso." << endl;
    }

    qtd_sentencas = 1;
    frases.resize(1);
    frases[0].resize(1);
    frases[0][0].resize( qtd_atributos );

    int row = 0, column = 0, contador = -1,count = 0;

    // l� um caracter inicial do arquivo
    arqin.get( ch );

    while( arqin.good() ) // Enquanto n�o for fim de arquivo e a leitura n�o contiver erros
    {
        if ( ch != '[' && ch != '#' )
        {
            if( ch != '\n' ) //considera frases com distancia maior que 1 espa�o
            {
                for( register int i = 0; i < qtd_atributos; ++i )
                {
                    // l� a palavra que ser� colocada no vector s�mbolos
                    while( ( ch != separador || i == qtd_atributos - 1 ) && ch != '\n' && !arqin.eof() ) //torna programa mais
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
                    ++count;
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
                if (dividirExemplos){
                    frases.resize( ++row + 1 ); //desloca para a proxima linha na matriz ( proxima frase no texto )
                    frases[row].resize(1);
                    frases[row][0].resize( qtd_atributos );
                    column = 0;
                }
                else{
                    frases[row].resize( ++column + 1 ); //desloca p/ o proximo elemento da matriz na mesma linha
                    frases[row][column].resize( qtd_atributos );
                }
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

    int column, k;

    for( register int i = 0; i < qtd_sentencas; ++i )
    {
        column = frases[i].size();
        for( register int j = 0; j < column; ++j )
        {
            for( k = 0; k < qtd_atributos - 1; ++k )
                arqout << simbolos[ frases[i][j][k] ] << separador;
            arqout << simbolos[ frases[i][j][k] ] << endl;
        }
        arqout << endl;
    }

    arqout.close();

    cout << "Arquivo <" << arquivo << "> gravado com sucesso!" << endl;

    return true;
}

Corpus* CorpusMatriz::clone()
{
    return new CorpusMatriz( *this );
}

Corpus& CorpusMatriz::construirJanela( Param &popUp )
{
    ModeloParam model;
    int ok;
    //coluna 0 � de nomes e coluna 1 de valores ou widgets

    //inser��o de textos
    model.inserirDados(0,0,"Separador:");
    model.inserirDados(1,0,"Dividir Exemplos:");
    model.inserirDados(0,1,"_");
    model.inserirDados(2,0,"Atributos automaticos:");
    model.inserirDados(3,0,"N� atributos:");

    //O modelo tem que ser inserido no Param antes de definir os Widgets
    popUp.ajustarModelo( model );

    //inser��o Widgets
    QCheckBox *cbox = new QCheckBox();
    model.inserirDados(1,1,popUp,cbox);
    QCheckBox *cbox2 = new QCheckBox();
    cbox2->setChecked( true );
    model.inserirDados(2,1,popUp,cbox2);
    QSpinBox *sbox = new QSpinBox();
    sbox->setValue( 1 );
    sbox->setMaximum( 99 );
    sbox->setMinimum( 1 );
    sbox->setEnabled( false );
    model.inserirDados(3,1,popUp,sbox);

    //inser��o de Evento(slot deve estar no Widget ou na classe Param)
    QObject::connect( cbox2, SIGNAL( clicked(bool) ), &popUp, SLOT( escolherAtributos(bool) ) );
    QObject::connect( sbox, SIGNAL( valueChanged(int)), &popUp, SLOT( redimensionarAtributos(int) ) );
    QMetaObject::connectSlotsByName( &popUp );

    //inicia Dialog
    ok = popUp.iniciarDialog();

    if( ok )
    {
        Corpus *corpus;
        QCheckBox *geral;
        bool dividirExemplos;
        dividirExemplos = (( QCheckBox* )popUp.pegarWidget( 1 ))->isChecked();
        geral = ( QCheckBox* )popUp.pegarWidget( 2 );
        if( geral->isChecked() )
            corpus = new CorpusMatriz( vector<string>(), popUp.pegarString(0)[0], dividirExemplos );
        else
        {
            int i, tam;
            vector< string > atributos( tam = (( QSpinBox* )popUp.pegarWidget( 3 ))->value() );
            for( i = 0; i < tam; ++i ) atributos[i] = popUp.pegarString(i+4);
            corpus = new CorpusMatriz( atributos, popUp.pegarString(0)[0], dividirExemplos );
        }
        return *corpus;
    }

    return *this;
}