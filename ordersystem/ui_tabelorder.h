/********************************************************************************
** Form generated from reading UI file 'tabelorder.ui'
**
** Created: Thu Jun 14 11:08:45 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABELORDER_H
#define UI_TABELORDER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_TabelOrder
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *TabelOrder)
    {
        if (TabelOrder->objectName().isEmpty())
            TabelOrder->setObjectName(QString::fromUtf8("TabelOrder"));
        TabelOrder->resize(441, 321);
        buttonBox = new QDialogButtonBox(TabelOrder);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(40, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(TabelOrder);
        QObject::connect(buttonBox, SIGNAL(accepted()), TabelOrder, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TabelOrder, SLOT(reject()));

        QMetaObject::connectSlotsByName(TabelOrder);
    } // setupUi

    void retranslateUi(QDialog *TabelOrder)
    {
        TabelOrder->setWindowTitle(QApplication::translate("TabelOrder", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TabelOrder: public Ui_TabelOrder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABELORDER_H
