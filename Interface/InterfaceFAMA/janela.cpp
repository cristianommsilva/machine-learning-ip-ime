#include "janela.h"
#include "ui_janela.h"

Janela::Janela(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Janela)
{
    ui->setupUi(this);
    corpus = NULL;
    treinador = NULL;

    //a adição de novos tipos de Corpus deve ser feita identicamente ao modelo abaixo
    ui->comboBox_corpus->addItem( "CorpusMatriz" );

    //a adição de novos tipos de Classificadores deve ser feita identicamente ao modelo abaixo
    ui->comboBox_metodo->addItem( "Mais Provavel" );
    ui->comboBox_metodo->addItem( "Hidden Markov Model - HMM" );
    ui->comboBox_metodo->addItem( "Transformation Based Learning - TBL" );

    ui->tableWidget_atributos->setHorizontalHeaderLabels( QStringList() << "Ordem" << "Nome" );
}

Janela::~Janela()
{
    delete ui;
    if( corpus != NULL ) delete corpus;
    if( treinador != NULL ) delete treinador;
}

void Janela::abrirArquivo()
{
    if( ( s = QFileDialog::getOpenFileName( this, "Abrir","","Documentos de texto (*.txt);;Todos os arquivos (*.*)" ) ) != "" )
    {
        logicaDeAbertura();
        ui->comboBox_metodo->setEnabled( true );
    }
}

void Janela::logicaDeAbertura()
{
    string a = s.toStdString();
    stringstream ss, st;
    int n, posBarra;

    corpus->carregarArquivo( a );

    if( (unsigned)( posBarra = a.rfind( '/' ) ) != string::npos)
        a = a.substr( posBarra + 1 );

    ui->lineEdit_relatorio->setText( QString::fromStdString( a ) );
    ss << ( n = corpus->pegarQtdAtributos() );
    ui->lineEdit_atributos->setText( QString::fromStdString( ss.str() ) );
    st << corpus->pegarQtdSentencas();
    ui->lineEdit_instancias->setText( QString::fromStdString( st.str() ) );

    //limpador da janela de atributos
    ui->tableWidget_atributos->clearContents();

    ui->tableWidget_atributos->setRowCount( n );
    QTableWidgetItem *item;
    for( int i = 0; i < n; ++i )
    {
        item = new QTableWidgetItem( QString( "%1" ).arg( i ) );
        ui->tableWidget_atributos->setItem( i, 0, item );
        item = new QTableWidgetItem( QString( "%1" ).arg( QString::fromStdString(corpus->pegarAtributo(i)) ) );
        ui->tableWidget_atributos->setItem( i, 1, item );
    }
}

void Janela::habilitarBotao(int index)
{
    if( corpus != NULL )
    {
        delete corpus;

        ui->lineEdit_relatorio->setText( "Nenhum" );
        ui->lineEdit_atributos->setText( "Nenhum" );
        ui->lineEdit_instancias->setText( "Nenhum" );
        ui->lineEdit_nome->setText( "Nenhum" );
        ui->lineEdit_tipo->setText( "Nenhum" );
        ui->lineEdit_distintos->setText( "Nenhum" );

        //limpador da janela de atributos
        ui->tableWidget_atributos->clearContents();
        ui->tableWidget_atributos->setRowCount( 0 );

        //limpador da janela de estatistica
        ui->tableWidget_estatistica->clearContents();
        ui->tableWidget_estatistica->setRowCount( 0 );

        ui->comboBox_metodo->setEnabled( false );
        ui->pushButton_start->setEnabled( false );

    }
    if( !index )
    {
        ui->pushButton_abrir->setEnabled( false );
        ui->toolButton_construtor->setEnabled( false );
    }
    else
    {
        ui->pushButton_abrir->setEnabled( true );
        ui->toolButton_construtor->setEnabled( true );
    }
    switch( index )
    {
        case 0 :
            corpus = NULL;
            break;
        case 1 :
            corpus = new CorpusMatrizUI();
            break;
    }
}

void Janela::atributoSelecionado( int row, int column )
{
    int atributo = ui->tableWidget_atributos->item( row, 0 )->text().toInt();
    int i, j, distintos, conjEx = corpus->pegarQtdConjExemplos(), qtdEx, totalSimbolos = corpus->pegarQtdSimbolos();
    string aux = "Nominal";
    vector< int > estatistica( totalSimbolos ), indices;

    ui->lineEdit_nome->setText( ui->tableWidget_atributos->item( row, 1 )->text() );

    //calculo estatistico
    for( i = 0; i < conjEx; ++i )
    {
        qtdEx = corpus->pegarQtdExemplos( i );
        for( j = 0; j < qtdEx; ++j )
            ++estatistica[corpus->pegarValor( i, j, atributo )];
    }

    for( i = 0; i < totalSimbolos; ++i  )
        if( estatistica[i] ) indices.push_back( i );

    distintos = indices.size();

    //ui->lineEdit_tipo->setText( aux = corpus->tipoDoAtributo( atributo ) );
    ui->lineEdit_tipo->setText( "Nominal" );
    ui->lineEdit_distintos->setText( QString( "%1" ).arg( distintos ) );

    if( aux == "Nominal" ) ui->tableWidget_estatistica->setHorizontalHeaderLabels( QStringList() << "Label" << "Quantidade" );

    //limpador da janela de estatistica
    ui->tableWidget_estatistica->clearContents();

    ui->tableWidget_estatistica->setRowCount( distintos );   
    QTableWidgetItem *item;
    for( i = 0; i < distintos; ++i )
    {
        item = new QTableWidgetItem( QString( "%1" ).arg( QString::fromStdString(corpus->pegarSimbolo( indices[i] ) ) ) );
        ui->tableWidget_estatistica->setItem( i, 0, item );
        item = new QTableWidgetItem( QString( "%1" ).arg( estatistica[indices[i]] ) );
        ui->tableWidget_estatistica->setItem( i, 1, item );
    }

}

void Janela::definirParametros()
{
    //Janela construida na classe Corpus por um método virtual
    Corpus *temp = corpus->construirJanela( &popUp );
    if( temp != corpus )
    {
        delete corpus;
        corpus = temp;
        if( s != "" ) logicaDeAbertura();
    }
}

void Janela::definirParametrosTreinador()
{
    //Janela construida na classe Treinador por um método virtual
    Treinador *temp = treinador->construirJanela( &popUp, *corpus );
    if( temp != treinador )
    {
        delete treinador;
        treinador = temp;
    }
}

void Janela::escolherClassificador( int index )
{
    if( treinador != NULL ) delete treinador;
    switch( index )
    {
        case 0 :
            treinador = NULL;
            break;
        case 1 :
            treinador = new MaisProvavel();
            break;
        case 2 :
            treinador = new HMM();
            break;
        case 3 :
            treinador = new TBL();
            break;
    }
    definirParametrosTreinador();
}
