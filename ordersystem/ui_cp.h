/********************************************************************************
** Form generated from reading UI file 'cp.ui'
**
** Created: Thu Jun 14 11:08:45 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CP_H
#define UI_CP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_cp_ui
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *cp_ui)
    {
        if (cp_ui->objectName().isEmpty())
            cp_ui->setObjectName(QString::fromUtf8("cp_ui"));
        cp_ui->resize(400, 300);
        buttonBox = new QDialogButtonBox(cp_ui);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(cp_ui);
        QObject::connect(buttonBox, SIGNAL(accepted()), cp_ui, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), cp_ui, SLOT(reject()));

        QMetaObject::connectSlotsByName(cp_ui);
    } // setupUi

    void retranslateUi(QDialog *cp_ui)
    {
        cp_ui->setWindowTitle(QApplication::translate("cp_ui", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class cp_ui: public Ui_cp_ui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CP_H
