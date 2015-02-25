/********************************************************************************
** Form generated from reading UI file 'dishlist.ui'
**
** Created: Sun Jun 17 19:25:02 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISHLIST_H
#define UI_DISHLIST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_dishlist
{
public:
    QLabel *label_2;
    QPushButton *add;
    QPushButton *pushButton_2;
    QTableWidget *table;
    QLCDNumber *desknum;

    void setupUi(QDialog *dishlist)
    {
        if (dishlist->objectName().isEmpty())
            dishlist->setObjectName(QString::fromUtf8("dishlist"));
        dishlist->resize(525, 438);
        label_2 = new QLabel(dishlist);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(430, 50, 91, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\226\260\345\256\213\344\275\223"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        add = new QPushButton(dishlist);
        add->setObjectName(QString::fromUtf8("add"));
        add->setGeometry(QRect(440, 160, 75, 41));
        pushButton_2 = new QPushButton(dishlist);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(440, 230, 75, 41));
        table = new QTableWidget(dishlist);
        table->setObjectName(QString::fromUtf8("table"));
        table->setGeometry(QRect(10, 10, 411, 411));
        desknum = new QLCDNumber(dishlist);
        desknum->setObjectName(QString::fromUtf8("desknum"));
        desknum->setGeometry(QRect(440, 80, 71, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setBold(true);
        font1.setWeight(75);
        desknum->setFont(font1);
        desknum->setSmallDecimalPoint(true);
        desknum->setNumDigits(3);

        retranslateUi(dishlist);

        QMetaObject::connectSlotsByName(dishlist);
    } // setupUi

    void retranslateUi(QDialog *dishlist)
    {
        dishlist->setWindowTitle(QApplication::translate("dishlist", "Dialog", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("dishlist", "\345\275\223\345\211\215\346\241\214\345\217\267", 0, QApplication::UnicodeUTF8));
        add->setText(QApplication::translate("dishlist", "\345\212\240\350\217\234", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("dishlist", "\347\273\223\350\264\246", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class dishlist: public Ui_dishlist {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISHLIST_H
