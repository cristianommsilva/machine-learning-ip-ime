#include "classificadortbl.h"

ClassificadorTBL::ClassificadorTBL()
{

}

ClassificadorTBL::~ClassificadorTBL()
{
    //dtor
}

void ClassificadorTBL::inserirRegra( map< int, map< string, string > > rule, string resp )
{
    regras.push_back( rule );
    respRegras.push_back( resp );
}

bool ClassificadorTBL::executarClassificacao( Corpus &corpusProva, int atributo )
{
    corpusProva.criarAtributo( "novo", "NOVO" );
    int qtdAtributos = corpusProva.pegarQtdAtributos();
    int row = corpusProva.pegarQtdSentencas(), column, numRegras = regras.size(), aux;
    bool regraInvalida;
    map< int, map< string, string > >::iterator linha, linha_end;
    map< string, string >::iterator it, it_end;

    for( register int i = 0; i < row; i++ )
    {
        column = corpusProva.pegarQtdTokens( i );
        for( register int j = 0; j < column; j++ )
            for( register int L = 0; L < numRegras; L++ )
            {
                regraInvalida = false;

                linha_end = regras[L].end();
                for( linha = regras[L].begin(); linha != linha_end; linha++ )
                {
                    if( ( aux = j + linha->first ) >= column || aux < 0 )
                    {
                        regraInvalida = true;
                        break;
                    }
                    it_end = linha->second.end();
                    for( it = linha->second.begin(); it != it_end; it++ )
                        if( corpusProva.pegarValor(i,aux,1) != corpusProva.pegarIndice( it->second ) ) //mexer aqui
                        {
                            regraInvalida = true;
                            break;
                        }
                    if( regraInvalida ) break;
                }
                if( !regraInvalida )
                {
                    corpusProva.ajustarValor(i,j,qtdAtributos - 1,corpusProva.pegarIndice( respRegras[L] ) );
                    L = numRegras;
                }
            }
    }
    return true;
}

bool ClassificadorTBL::gravarConhecimento( string arquivo )
{
    ofstream arqout( arquivo.c_str() );
    if( !arqout.is_open() ) //verifica se arquivo conseguiu ser aberto
    {
        cout << "Erro:gravarConhecimento!\nFalha na abertura do arquivo!" << endl;
        return false;
    }

    int numRegras = regras.size();
    map< int, map< string, string > >::iterator linha, linha_end;
    map< string, string >::iterator it, it_end;

    for( register int i = 0; i < numRegras; i++ )
    {
        linha_end = regras[i].end();
        for( linha = regras[i].begin(); linha != linha_end; it++ )
        {
            it_end = linha->second.end();
            for( it = linha->second.begin(); it != it_end; it++ )
                arqout << it->first << ' ' << linha->first << ' ' << it->second << ' ';
        }
        arqout << "=>";
        for( register int j = 0; j < numRegras; j++ )
            arqout << ' ' << respRegras[j];
        arqout << endl;
    }

    arqout.close();
    cout << "Arquivo <" << arquivo << "> gravado com sucesso!" << endl;
    return true;
}

bool ClassificadorTBL::carregarConhecimento( string arquivo )
{
    ifstream arqin( arquivo.c_str() );
    if( !arqin.is_open() ) //verifica se arquivo conseguiu ser aberto
    {
        cout << "Erro:carregarConhecimento!\nFalha na abertura do arquivo!" << endl;
        return false;
    }

    string palavra1, palavra2;
    int posicao;
    char ch ;
    map< int, map< string, string > > atributoValor;

    while( arqin.good() )
    {
        arqin.get( ch );//caso inicial p/ diferenciar de \n
        palavra1.push_back( ch );
        while( ch != '\n' )
        {
            for( arqin.get( ch ); ch != ' '; arqin.get( ch ) )
                palavra1.push_back( ch );
            /*if( palavra1.compare( "=>" ) )
            {
                palavra1.clear();
                while( ch != '\n' )
                {
                    for( arqin.get( ch ); ch != ' '; arqin.get( ch ) )
                        palavra1.push_back( ch );
                    for( arqin.get( ch ); ch != ' ' && ch != '\n'; arqin.get( ch ) )
                        palavra2.push_back( ch );
                    atributoValor2[palavra1] = palavra2;
                    palavra1.clear();
                    palavra2.clear();
                }
            }*/
            if( palavra1.compare( "=>" ) )
            {
                for( arqin.get( ch ); ch != ' ' && ch != '\n'; arqin.get( ch ) )
                    palavra2.push_back( ch );
                respRegras.push_back( palavra2 );
            }
            else
            {
                arqin >> posicao;
                for( arqin.get( ch ); ch != ' '; arqin.get( ch ) )
                    palavra2.push_back( ch );
                atributoValor[posicao][palavra1] = palavra2;
                //palavra1.clear();
                //palavra2.clear();
            }
            palavra1.clear();
            palavra2.clear();
        }
        regras.push_back( atributoValor );
        atributoValor.clear();
    }

    if( arqin.bad() && !arqin.eof() )    //caso de erro na leitura do arquivo
    {
        cout << "Erro:carregarConhecimento!\nErro na leitura do arquivo!" << endl;
        arqin.close();
        return false;
    }

    arqin.close();
    cout << "Arquivo <" << arquivo << "> carregado com sucesso!" << endl;
    return true;
}
