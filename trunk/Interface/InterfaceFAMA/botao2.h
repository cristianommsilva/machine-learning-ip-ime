#ifndef BOTAO2_H
#define BOTAO2_H

#include <QWidget>
#include <QToolButton>

class Botao2 : public QToolButton
{
    Q_OBJECT
public:
    explicit Botao2(QWidget *parent = 0);
    
signals:
    
public slots:
    void habilitarBotao(int index);
};

#endif // BOTAO2_H
