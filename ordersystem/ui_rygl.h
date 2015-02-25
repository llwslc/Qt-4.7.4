/********************************************************************************
** Form generated from reading UI file 'rygl.ui'
**
** Created: Mon Jun 18 13:02:07 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RYGL_H
#define UI_RYGL_H

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

class Ui_rygl
{
public:
    QPushButton *pbback;
    QLineEdit *getvalue;
    QPushButton *pbsave;
    QPushButton *pbdelete;
    QLabel *label;
    QTableView *tv;
    QLabel *label_2;
    QPushButton *pbfind;
    QPushButton *pbadd;

    void setupUi(QDialog *rygl)
    {
        if (rygl->objectName().isEmpty())
            rygl->setObjectName(QString::fromUtf8("rygl"));
        rygl->resize(523, 382);
        pbback = new QPushButton(rygl);
        pbback->setObjectName(QString::fromUtf8("pbback"));
        pbback->setGeometry(QRect(440, 290, 71, 23));
        getvalue = new QLineEdit(rygl);
        getvalue->setObjectName(QString::fromUtf8("getvalue"));
        getvalue->setGeometry(QRect(60, 50, 271, 21));
        pbsave = new QPushButton(rygl);
        pbsave->setObjectName(QString::fromUtf8("pbsave"));
        pbsave->setGeometry(QRect(440, 110, 71, 23));
        pbdelete = new QPushButton(rygl);
        pbdelete->setObjectName(QString::fromUtf8("pbdelete"));
        pbdelete->setGeometry(QRect(440, 230, 71, 23));
        label = new QLabel(rygl);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(190, 20, 131, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        tv = new QTableView(rygl);
        tv->setObjectName(QString::fromUtf8("tv"));
        tv->setGeometry(QRect(10, 80, 421, 291));
        label_2 = new QLabel(rygl);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 50, 41, 16));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setWeight(50);
        label_2->setFont(font1);
        pbfind = new QPushButton(rygl);
        pbfind->setObjectName(QString::fromUtf8("pbfind"));
        pbfind->setGeometry(QRect(360, 50, 71, 23));
        pbadd = new QPushButton(rygl);
        pbadd->setObjectName(QString::fromUtf8("pbadd"));
        pbadd->setGeometry(QRect(440, 170, 71, 23));

        retranslateUi(rygl);

        QMetaObject::connectSlotsByName(rygl);
    } // setupUi

    void retranslateUi(QDialog *rygl)
    {
        rygl->setWindowTitle(QApplication::translate("rygl", "\344\272\272\345\221\230\347\256\241\347\220\206", 0, QApplication::UnicodeUTF8));
        pbback->setText(QApplication::translate("rygl", "\350\277\224\345\233\236", 0, QApplication::UnicodeUTF8));
        pbsave->setText(QApplication::translate("rygl", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
        pbdelete->setText(QApplication::translate("rygl", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("rygl", "\344\272\272\345\221\230\347\256\241\347\220\206", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("rygl", "\345\247\223\345\220\215", 0, QApplication::UnicodeUTF8));
        pbfind->setText(QApplication::translate("rygl", "\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        pbadd->setText(QApplication::translate("rygl", "\346\267\273\345\212\240", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class rygl: public Ui_rygl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RYGL_H
