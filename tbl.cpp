#include "tbl.h"

TBL::TBL( int toleranciaScore )
{
    this->toleranciaScore = toleranciaScore;
}

TBL::~TBL()
{
    //dtor
}

//{ word 0 pos 1 adpos 2 }
//vector<string> at = corpus.atributo();

#define POS 2
#define WORD 1

Classificador *TBL::executarTreinamento( Corpus &corpus, int atributo )
{
    int row = corpus.pegarQtdSentencas(), column, numMoldeRegras, qtdAtributos, aux, aux2;
    map< int, int >::iterator it, it_end;
    map< int, int > var;
    bool moldeInvalido;
    //vector< int > = new Vector corpus.pegarQtdAtributos();
    vector< vector< map< int, int > > > regras;
    vector< vector< vector< int > > > score;
    vector< vector< int > > respRegras;
    vector< map< int, int> > moldeRegras;
    vector< int > respMolde; //se for feita mais de uma classificação simultanea respMolde tem que ser atualizado para map

    //incializar molde de regras
    map< int, int > mprg;
    mprg[-1] = POS;
    mprg[0] = WORD;
    respMolde.push_back( POS );
    moldeRegras.push_back( mprg );
    numMoldeRegras = moldeRegras.size();
    regras.resize( numMoldeRegras );
    score.resize( numMoldeRegras );
    respRegras.resize( numMoldeRegras );

    //Classificação inicial do corpus
    MaisProvavel objMProv( LIM_FREQ_UNKNOWN );
    Classificador *objClass = objMProv.executarTreinamento( corpus, atributo );
    objClass->executarClassificacao( corpus, ATRBT_CLASSIFICADO );

    qtdAtributos = corpus.pegarQtdAtributos();
    //varre corpus criando as regras
    for( register int i = 0; i < row; i++ )
    {
        column = corpus.pegarQtdTokens( i );
        for( register int j = 0; j < column; j++ )
            if( ( aux = corpus.pegarValor(i,j,atributo) ) != corpus.pegarValor(i,j, qtdAtributos - 1) )
            {
                for( register int L = 0; L < numMoldeRegras; L++ )
                {
                    moldeInvalido = false;

                    it_end = moldeRegras[L].end();
                    for( it = moldeRegras[L].begin(); it != it_end; it++ )
                    {
                        if( ( aux2 = j + it->first ) >= column || aux < 0 )
                        {
                            moldeInvalido = true;
                            break;
                        }
                        var[it->first] = corpus.pegarValor(i, aux2, it->second);
                    }
                    if( !moldeInvalido )
                    {
                        regras[L].push_back( var );
                        respRegras[L].push_back( aux );
                    }
                    var.clear();
                }
            }
    }

    for( register int L = 0; L < numMoldeRegras; L++ )
        score[L].resize( regras[L].size() );
    //varre corpus aplicando as regras e computando o score
    for( register int i = 0; i < row; i++ )
    {
        column = corpus.pegarQtdTokens( i );
        for( register int j = 0; j < column; j++ )
                for( register int L = 0; L < numMoldeRegras; L++ )
                {

                }
    }

    return NULL;
}
