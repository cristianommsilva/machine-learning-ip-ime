/********************************************************************************
** Form generated from reading UI file 'param.ui'
**
** Created: Sun 26. Aug 20:02:07 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAM_H
#define UI_PARAM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QTableView>

QT_BEGIN_NAMESPACE

class Ui_Param
{
public:
    QDialogButtonBox *buttonBox_ok;
    QTableView *tableView;

    void setupUi(QDialog *Param)
    {
        if (Param->objectName().isEmpty())
            Param->setObjectName(QString::fromUtf8("Param"));
        Param->resize(219, 300);
        buttonBox_ok = new QDialogButtonBox(Param);
        buttonBox_ok->setObjectName(QString::fromUtf8("buttonBox_ok"));
        buttonBox_ok->setGeometry(QRect(10, 260, 201, 32));
        buttonBox_ok->setOrientation(Qt::Horizontal);
        buttonBox_ok->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        tableView = new QTableView(Param);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(10, 10, 201, 241));
        tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->horizontalHeader()->setVisible(false);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setVisible(false);

        retranslateUi(Param);
        QObject::connect(buttonBox_ok, SIGNAL(accepted()), Param, SLOT(accept()));
        QObject::connect(buttonBox_ok, SIGNAL(rejected()), Param, SLOT(reject()));

        QMetaObject::connectSlotsByName(Param);
    } // setupUi

    void retranslateUi(QDialog *Param)
    {
        Param->setWindowTitle(QApplication::translate("Param", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Param: public Ui_Param {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAM_H
