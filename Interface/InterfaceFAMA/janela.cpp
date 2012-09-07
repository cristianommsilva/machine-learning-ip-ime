#include "janela.h"
#include "ui_janela.h"

Janela::Janela(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Janela)
{
    ui->setupUi(this);
    corpus = NULL;

    //ui->comboBox_corpus->addItem( "Escolha o Corpus" );
    ui->comboBox_corpus->addItem( "CorpusMatriz" );

    //ui->tableWidget_atributos->setColumnCount( 2 );
    //ui->tableWidget_atributos->setColumnWidth(1,5);
    ui->tableWidget_atributos->setHorizontalHeaderLabels( QStringList() << "No." << "Nome" );
    //ui->tableWidget_atributos->verticalHeader()->setVisible( false ); // Deixa invisível o cabeçalho vertical
    //ui->tableWidget_atributos->horizontalHeader()->setStretchLastSection(true); // Alarga a última coluna conforme o tamanho do TableView
    //ui->tableWidget_atributos->setSelectionBehavior(QAbstractItemView::SelectRows);  // Seleciona toda a linha quando um item da linha é ativado
    //ui->tableWidget_atributos->setSelectionMode(QAbstractItemView::SingleSelection); // Permite selecionar apenas um item por vez
}

Janela::~Janela()
{
    delete ui;
    if( corpus != NULL ) delete corpus;
}

void Janela::abrirArquivo()
{
    if( s == "" ) s = QFileDialog::getOpenFileName( this, "Abrir","","Documentos de texto (*.txt);;Todos os arquivos (*.*)" );
    if( s != "" )
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
        for( int i = 0; i < ui->tableWidget_atributos->rowCount(); ++i )
        {
            delete ui->tableWidget_atributos->item( i, 0 );
            delete ui->tableWidget_atributos->item( i, 1 );
        }

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
}

void Janela::habilitarBotao(int index)
{
    if( corpus != NULL ) delete corpus;
    indexCorpus = index;
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
            corpus = new CorpusMatriz();
            break;
    }
}

void Janela::atributoSelecionado( int row, int column )
{
    int atributo = ui->tableWidget_atributos->item( row, 0 )->text().toInt();

    ui->lineEdit_nome->setText( ui->tableWidget_atributos->item( row, 1 )->text() );
}

void Janela::definirParametros()
{
    switch( indexCorpus )
    {
        case 1 :
            delete corpus;
            ModeloParam model;
            //coluna 0 é de nomes e coluna 1 de valores ou widgets

            //inserção de textos
            model.inserirDados(0,0,"Separador:");
            model.inserirDados(1,0,"Dividir Exemplos:");
            model.inserirDados(0,1,"_");
            model.inserirDados(2,0,"Atributos automaticos:");
            model.inserirDados(3,0,"Nº atributos:");

            popUp.ajustarModelo( model );

            //inserção Widgets
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
            //QTableWidget *tw = new QTableWidget();
            //tw->setColumnCount( 1 );
            //tw->setRowCount( 3 );
            //tw->setEnabled( true );
            //tw->setEditTriggers( QAbstractItemView::AllEditTriggers );
            //tw->horizontalHeader()->setStretchLastSection( true );
            //model.inserirDados( 4, 1, popUp, tw );

            //inserção de Evento(slot deve estar no Widget ou na class Param
            QObject::connect( cbox2, SIGNAL( clicked(bool) ), &popUp, SLOT( escolherAtributos(bool) ) );
            QObject::connect( sbox, SIGNAL( valueChanged(int)), &popUp, SLOT( redimensionarAtributos(int) ) );
            QMetaObject::connectSlotsByName( &popUp );

            //inicia Dialog
            popUp.iniciarDialog();

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

            //ParamCorpus construtor;
            //construtor.exec();
            //corpus = new CorpusMatriz( construtor.atributos, construtor.separador, construtor.dividirExemplos );
            break;
    }
    if( s != "" ) abrirArquivo();
}
