/********************************************************************************
** Form generated from reading UI file 'cpgl.ui'
**
** Created: Mon Jun 18 13:02:07 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CPGL_H
#define UI_CPGL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTableView>

QT_BEGIN_NAMESPACE

class Ui_cpgl
{
public:
    QPushButton *pbback;
    QTableView *tv;
    QLabel *label;
    QPushButton *pbadd;
    QPushButton *pbdelete;
    QPushButton *pbfind;
    QLineEdit *getvalue;
    QPushButton *pbsave;
    QLabel *label_2;

    void setupUi(QDialog *cpgl)
    {
        if (cpgl->objectName().isEmpty())
            cpgl->setObjectName(QString::fromUtf8("cpgl"));
        cpgl->resize(523, 382);
        pbback = new QPushButton(cpgl);
        pbback->setObjectName(QString::fromUtf8("pbback"));
        pbback->setGeometry(QRect(440, 290, 71, 23));
        tv = new QTableView(cpgl);
        tv->setObjectName(QString::fromUtf8("tv"));
        tv->setGeometry(QRect(10, 80, 421, 291));
        label = new QLabel(cpgl);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(190, 20, 131, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        pbadd = new QPushButton(cpgl);
        pbadd->setObjectName(QString::fromUtf8("pbadd"));
        pbadd->setGeometry(QRect(440, 170, 71, 23));
        pbdelete = new QPushButton(cpgl);
        pbdelete->setObjectName(QString::fromUtf8("pbdelete"));
        pbdelete->setGeometry(QRect(440, 230, 71, 23));
        pbfind = new QPushButton(cpgl);
        pbfind->setObjectName(QString::fromUtf8("pbfind"));
        pbfind->setGeometry(QRect(360, 50, 71, 23));
        getvalue = new QLineEdit(cpgl);
        getvalue->setObjectName(QString::fromUtf8("getvalue"));
        getvalue->setGeometry(QRect(60, 50, 271, 21));
        pbsave = new QPushButton(cpgl);
        pbsave->setObjectName(QString::fromUtf8("pbsave"));
        pbsave->setGeometry(QRect(440, 110, 71, 23));
        label_2 = new QLabel(cpgl);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 50, 41, 16));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setWeight(50);
        label_2->setFont(font1);

        retranslateUi(cpgl);

        QMetaObject::connectSlotsByName(cpgl);
    } // setupUi

    void retranslateUi(QDialog *cpgl)
    {
        cpgl->setWindowTitle(QApplication::translate("cpgl", "\350\217\234\345\223\201\347\256\241\347\220\206", 0, QApplication::UnicodeUTF8));
        pbback->setText(QApplication::translate("cpgl", "\350\277\224\345\233\236", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("cpgl", "\350\217\234\345\223\201\347\256\241\347\220\206", 0, QApplication::UnicodeUTF8));
        pbadd->setText(QApplication::translate("cpgl", "\346\267\273\345\212\240", 0, QApplication::UnicodeUTF8));
        pbdelete->setText(QApplication::translate("cpgl", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
        pbfind->setText(QApplication::translate("cpgl", "\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        pbsave->setText(QApplication::translate("cpgl", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("cpgl", "\350\217\234\345\220\215", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class cpgl: public Ui_cpgl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CPGL_H
