#include "corpus.h"

Corpus::Corpus( vector<string> atributos )
    : atributos( atributos )
{
    frases.resize(1);
    frases[0].resize(1);
    frases[0][0].resize( atributos.size() );
    qtd_sentencas = 1;
    qtd_atributos = atributos.size();
    qtd_simbolos = 0;
}

Corpus::~Corpus()
{

}

string Corpus::pegarSimbolo( int indice )
{
    if ( indice < 0 || indice >= ( int )simbolos.size() )
    {
        cout << "Erro: pegarSimbolo!\nBusca fora dos limites!" << endl;
        return "erro!!";
    }

    return simbolos[ indice ];
}

int Corpus::pegarIndice( string simbolo )
{
    int aux;
    map< string, int >:: iterator it; //utilizado p/ n precisar varrer o map 2 vezes

    if( ( it = dicionario.find( simbolo ) ) == dicionario.end() ) //mesmo tratamento da criarAtributo
    {
        aux = dicionario[ simbolo ] = dicionario.size() - 1;
        simbolos.push_back( simbolo );
        ++qtd_simbolos;
        return aux;
    }
    return it->second;
}

bool Corpus::criarAtributo( string atributo, string valorAtributo )
{
    /**
    *   Verifica se o atributo j� existe.
    *   Se n�o existe cria-se um novo atributo.
    */
    for ( register int i = 0; i < qtd_atributos; i++ )
        if ( atributo == atributos[ i ] )
        {
            cout << "Erro:criarAtributo!\nAtributo ja existe!" << endl;
            return false;
        }

    atributos.push_back( atributo );

    /**
    *   verifica se valorAtributo j� existe no dicion�rio.
    *   Se n�o existir cria-se um novo valor no dicion�rio.
    */
    if ( dicionario.find( valorAtributo ) == dicionario.end() )
    {
        dicionario[ valorAtributo ] = dicionario.size() - 1;    // nessa linha primeiro cria-se um elemento(ou seja, aumenta o size),
                                                                // depois realiza-se a atribui��o
        simbolos.push_back( valorAtributo );
        ++qtd_simbolos;
    }

    /**
    *   Cria mais uma posi��o(inicializada com valorAtributo) em cada token de frases
    */
    int column;
    int dicionario_valorAtributo = dicionario[ valorAtributo ];

    for( register int i = 0; i < qtd_sentencas; i++ )
    {
        column = frases[i].size();
        for( register int j = 0; j < column; j++ )
            frases[i][j].push_back( dicionario_valorAtributo );
    }

    ++qtd_atributos; //como foi adicionado um novo atributo, sua qtd � incrementada

/*    /// TESTE DE IMPRESS�O DE "FRASES[][][]"
    for ( register int i = 0; i < qtd_sentencas; i++ )
    {
    	for ( register int j = 0; j < frases[ i ].size(); j++ )
    	{
    		cout << frases[i][j][0] << "_" << frases[i][j][1] << "_" << frases[i][j][2] << endl;
    	}
    	cout << endl;
    }*/

    cout << "Atributo <\"" << atributo << "\" -> " << "\"" << valorAtributo << "\"" << "> criado com sucesso!" << endl;
    return true;
}

int Corpus::pegarValor( int sentenca, int token, int atributo )
{
    if ( sentenca < 0 || sentenca >= ( int )qtd_sentencas ||
         token < 0 || token >= ( int )frases[sentenca].size() ||
         atributo < 0 || atributo >= ( int )qtd_atributos )
    {
        cout << "Erro: pegarValor!\nBusca fora dos limites!" << endl;
        return -1;
    }

    return frases[sentenca][token][atributo];
}

int Corpus::pegarQtdSentencas()
{
    return qtd_sentencas;
}

int Corpus::pegarQtdAtributos()
{
    return qtd_atributos;
}

int Corpus::pegarQtdTokens( int i )
{
    if( i < 0 || i >= ( int )qtd_sentencas )
    {
        cout << "Erro: pegarQtdTokens!\nBusca fora dos limites!" << endl;
        return -1;
    }
    return frases[i].size();
}

int Corpus::pegarQtdSimbolos()
{
    return qtd_simbolos;
}

bool Corpus::ajustarValor( int sentenca, int token, int atributo, int valor )
{
    if ( sentenca < 0 || sentenca >= ( int )qtd_sentencas ||
         token < 0 || token >= ( int )frases[sentenca].size() ||
         atributo < 0 || atributo >= ( int )qtd_atributos )
    {
        cout << "Erro: ajustarValor!\nInsercao cancelada: posicao inexistente!" << endl;
        return false;
    }
    frases[ sentenca ][ token ][ atributo ] = valor;
    return true;
}

string Corpus::pegarAtributo( int indice )
{
    if( indice < 0 || indice >= qtd_atributos )
    {
        cout << "Erro: pegarAtributo!\nBusca fora dos limites!" << endl;
        return NULL;
    }
    return atributos[indice];
}