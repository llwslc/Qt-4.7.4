/********************************************************************************
** Form generated from reading UI file 'logdialog.ui'
**
** Created: Mon Jun 18 13:03:56 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGDIALOG_H
#define UI_LOGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_logDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *lbname;
    QLineEdit *lename;
    QLabel *lbpasswd;
    QLineEdit *lepasswd;
    QGridLayout *gridLayout_2;
    QRadioButton *rbadmin;
    QRadioButton *rbserve;
    QGridLayout *gridLayout_3;
    QPushButton *pblogin;
    QPushButton *pbcancel;

    void setupUi(QDialog *logDialog)
    {
        if (logDialog->objectName().isEmpty())
            logDialog->setObjectName(QString::fromUtf8("logDialog"));
        logDialog->resize(480, 288);
        layoutWidget = new QWidget(logDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 20, 421, 231));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lbname = new QLabel(layoutWidget);
        lbname->setObjectName(QString::fromUtf8("lbname"));

        gridLayout->addWidget(lbname, 0, 0, 1, 1);

        lename = new QLineEdit(layoutWidget);
        lename->setObjectName(QString::fromUtf8("lename"));

        gridLayout->addWidget(lename, 0, 1, 1, 1);

        lbpasswd = new QLabel(layoutWidget);
        lbpasswd->setObjectName(QString::fromUtf8("lbpasswd"));

        gridLayout->addWidget(lbpasswd, 1, 0, 1, 1);

        lepasswd = new QLineEdit(layoutWidget);
        lepasswd->setObjectName(QString::fromUtf8("lepasswd"));
        lepasswd->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lepasswd, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        rbadmin = new QRadioButton(layoutWidget);
        rbadmin->setObjectName(QString::fromUtf8("rbadmin"));

        gridLayout_2->addWidget(rbadmin, 0, 0, 1, 1);

        rbserve = new QRadioButton(layoutWidget);
        rbserve->setObjectName(QString::fromUtf8("rbserve"));

        gridLayout_2->addWidget(rbserve, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        pblogin = new QPushButton(layoutWidget);
        pblogin->setObjectName(QString::fromUtf8("pblogin"));

        gridLayout_3->addWidget(pblogin, 0, 0, 1, 1);

        pbcancel = new QPushButton(layoutWidget);
        pbcancel->setObjectName(QString::fromUtf8("pbcancel"));

        gridLayout_3->addWidget(pbcancel, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_3);


        retranslateUi(logDialog);

        QMetaObject::connectSlotsByName(logDialog);
    } // setupUi

    void retranslateUi(QDialog *logDialog)
    {
        logDialog->setWindowTitle(QApplication::translate("logDialog", "\347\231\273\345\275\225\347\252\227\345\217\243", 0, QApplication::UnicodeUTF8));
        lbname->setText(QApplication::translate("logDialog", "\347\224\250\346\210\267\345\220\215", 0, QApplication::UnicodeUTF8));
        lbpasswd->setText(QApplication::translate("logDialog", "\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
        rbadmin->setText(QApplication::translate("logDialog", "\347\256\241\347\220\206\345\221\230", 0, QApplication::UnicodeUTF8));
        rbserve->setText(QApplication::translate("logDialog", "\346\234\215\345\212\241\345\221\230", 0, QApplication::UnicodeUTF8));
        pblogin->setText(QApplication::translate("logDialog", "\347\231\273\345\275\225", 0, QApplication::UnicodeUTF8));
        pbcancel->setText(QApplication::translate("logDialog", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class logDialog: public Ui_logDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGDIALOG_H
