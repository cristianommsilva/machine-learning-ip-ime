#include "classificadortbl.h"

ClassificadorTBL::ClassificadorTBL()
{

}

ClassificadorTBL::~ClassificadorTBL()
{
    //dtor
}

bool ClassificadorTBL::executarClassificacao( Corpus &corpusProva, int atributo )
{
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
    map<string,string>::iterator it;

    for( register int i = 0; i < numRegras; i++ )
    {
        for( it = regras[i].begin(); it != regras[i].end(); it++ )
            arqout << it->first << ' ' << it->second;
        arqout << ' ' << "=>" << ' ';
        for( it = respRegras[i].begin(); it != respRegras[i].end(); it++ )
            arqout << it->first << ' ' << it->second;
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
    char ch = ' ';
    map< string, string> atributoValor, atributoValor2;

    while( arqin.good() )
    {
        while( ch != '\n' )
        {
            for( arqin.get( ch ); ch != ' '; arqin.get( ch ) )
                palavra1.push_back( ch );
            if( palavra1.compare( "=>" ) )
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
            }
            else
            {
                for( arqin.get( ch ); ch != ' '; arqin.get( ch ) )
                    palavra2.push_back( ch );
                atributoValor[palavra1] = palavra2;
                palavra1.clear();
                palavra2.clear();
            }
        }
        regras.push_back( atributoValor );
        respRegras.push_back( atributoValor2 );
        atributoValor.clear();
        atributoValor2.clear();
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
