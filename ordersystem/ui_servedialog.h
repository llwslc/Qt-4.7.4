/********************************************************************************
** Form generated from reading UI file 'servedialog.ui'
**
** Created: Mon Jun 18 13:00:34 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVEDIALOG_H
#define UI_SERVEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_serveDialog
{
public:
    QTableWidget *table;

    void setupUi(QDialog *serveDialog)
    {
        if (serveDialog->objectName().isEmpty())
            serveDialog->setObjectName(QString::fromUtf8("serveDialog"));
        serveDialog->resize(600, 480);
        table = new QTableWidget(serveDialog);
        table->setObjectName(QString::fromUtf8("table"));
        table->setGeometry(QRect(40, 50, 521, 391));
        table->setStyleSheet(QString::fromUtf8(""));

        retranslateUi(serveDialog);

        QMetaObject::connectSlotsByName(serveDialog);
    } // setupUi

    void retranslateUi(QDialog *serveDialog)
    {
        serveDialog->setWindowTitle(QApplication::translate("serveDialog", "\346\234\215\345\212\241\345\221\230", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class serveDialog: public Ui_serveDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVEDIALOG_H
