/********************************************************************************
** Form generated from reading UI file 'admindialog.ui'
**
** Created: Fri Jun 15 15:29:24 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINDIALOG_H
#define UI_ADMINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_adminDialog
{
public:
    QPushButton *pbcp;
    QPushButton *pbry;

    void setupUi(QDialog *adminDialog)
    {
        if (adminDialog->objectName().isEmpty())
            adminDialog->setObjectName(QString::fromUtf8("adminDialog"));
        adminDialog->resize(600, 480);
        pbcp = new QPushButton(adminDialog);
        pbcp->setObjectName(QString::fromUtf8("pbcp"));
        pbcp->setGeometry(QRect(220, 160, 151, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        pbcp->setFont(font);
        pbry = new QPushButton(adminDialog);
        pbry->setObjectName(QString::fromUtf8("pbry"));
        pbry->setGeometry(QRect(220, 240, 151, 51));
        pbry->setFont(font);

        retranslateUi(adminDialog);

        QMetaObject::connectSlotsByName(adminDialog);
    } // setupUi

    void retranslateUi(QDialog *adminDialog)
    {
        adminDialog->setWindowTitle(QApplication::translate("adminDialog", "\347\256\241\347\220\206\345\221\230", 0, QApplication::UnicodeUTF8));
        pbcp->setText(QApplication::translate("adminDialog", "\350\217\234\345\223\201\347\256\241\347\220\206", 0, QApplication::UnicodeUTF8));
        pbry->setText(QApplication::translate("adminDialog", "\344\272\272\345\221\230\347\256\241\347\220\206", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class adminDialog: public Ui_adminDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINDIALOG_H
