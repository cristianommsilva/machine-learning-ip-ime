#include "hmm.h"

HMM::~HMM()
{
    //dtor
}

Classificador *HMM::executarTreinamento( Corpus &corpus, int atributo )
{
    ClassificadorHMM *objClassificador = new ClassificadorHMM();
    map< string, map< string, double > > matrizTransicao;
    int row = corpus.pegarQtdSentencas(), column;
    double total = 0.0;

    if ( atributo <= 0 || atributo >= ( int )corpus.pegarQtdAtributos() )
    {
        cout << "Erro:executarTreinamento!\nAtributo inexistente!" << endl;
    	return objClassificador;
    }

    for ( register int i = 0; i < row; i++ )
    {
        column = corpus.pegarQtdTokens( i );

    	for ( register int j = 0; j < column; j++ )
    	{
    	    objClassificador->ajustarTabFreqObservacoes( corpus.pegarSimbolo(corpus.pegarValor(i,j,atributo)), corpus.pegarSimbolo(corpus.pegarValor(i,j,0)) );
    	    if( j == 0 )
                objClassificador->ajustarVetInicial( corpus.pegarSimbolo(corpus.pegarValor(i,j,atributo)) );
            if( j != column -1 )
                ++matrizTransicao[corpus.pegarSimbolo(corpus.pegarValor(i,j,atributo))][corpus.pegarSimbolo(corpus.pegarValor(i,j+1,atributo))];
    	}
    }

    ///Verificar depois at� onde o double mantem a precis�o
    map< string, map< string, double > >::iterator linha;
    map< string, double >:: iterator coluna, it;
    //faz convers�o para matriz de probabilidades
    for( linha = matrizTransicao.begin();  linha!= matrizTransicao.end(); linha++ )
    {
        for( coluna = linha->second.begin(); coluna != linha->second.end(); coluna++ )
            total += coluna->second;
        for( coluna = linha->second.begin(); coluna != linha->second.end(); coluna++ )
            matrizTransicao[linha->first][coluna->first] = ( coluna->second )/total; //pode haver um erro carregado aqui
        total = 0.0;
    }

    objClassificador->definirMatrizTransicao( matrizTransicao );

    //A principio n�o precisa de Unknown, sera utilizado a melhor sequencia de estados
    cout << "A, B e Pi criados" << endl;
    return objClassificador;
}
