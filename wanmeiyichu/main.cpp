#include <QtGui/QApplication>
#include "common.h"
#include "myDatabase.h"
#include "mainwindow.h"
#include "createbutton.h"
#include "animation.h"
#include "otherobject.h"

//初始化所有全局变量
void initAllGlobalVariables();

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));

    QApplication a(argc, argv);    

    //打开数据库
    myDatabase db;
    if(db.opendb("wanmeiyichu.db"))
    {
        //创建数据库表
        db.createtable();
    }

    //创建相应的文件夹
    createFolder("clothes"); //衣服

    initAllGlobalVariables();

    MainWindow *w = new MainWindow;

    createMainButtonFunc(w);
    createMainOtherObjectFunc(w);
    createMainStateFunc();

    w->setWindowOpacity(1);    //透明度1.0-0.0
    w->setWindowFlags(Qt::FramelessWindowHint);   //窗口无边框
    w->setAttribute(Qt::WA_TranslucentBackground); //透明窗口

    w->show();

    QObject::connect(myclothesButton, SIGNAL(clicked()), w, SLOT(myclothesButton_clicked()));
    QObject::connect(fashionButton, SIGNAL(clicked()), w, SLOT(fashionButton_clicked()));
    QObject::connect(daydressButton, SIGNAL(clicked()), w, SLOT(daydressButton_clicked()));
    QObject::connect(settingButton, SIGNAL(clicked()), w, SLOT(settingButton_clicked()));
    QObject::connect(clothesButton, SIGNAL(clicked()), w, SLOT(clothesButton_clicked()));
    QObject::connect(bagButton, SIGNAL(clicked()), w, SLOT(bagButton_clicked()));
    QObject::connect(shoeButton, SIGNAL(clicked()), w, SLOT(shoeButton_clicked()));
    QObject::connect(decoButton, SIGNAL(clicked()), w, SLOT(decoButton_clicked()));
    QObject::connect(cosButton, SIGNAL(clicked()), w, SLOT(cosButton_clicked()));
    QObject::connect(labelButton, SIGNAL(clicked()), w, SLOT(labelButton_clicked()));
    QObject::connect(springButton, SIGNAL(clicked()), w, SLOT(springButton_clicked()));
    QObject::connect(summerButton, SIGNAL(clicked()), w, SLOT(summerButton_clicked()));
    QObject::connect(autumnButton, SIGNAL(clicked()), w, SLOT(autumnButton_clicked()));
    QObject::connect(winterButton, SIGNAL(clicked()), w, SLOT(winterButton_clicked()));
    QObject::connect(workplaceButton, SIGNAL(clicked()), w, SLOT(workplaceButton_clicked()));
    QObject::connect(banquetButton, SIGNAL(clicked()), w, SLOT(banquetButton_clicked()));
    QObject::connect(leisureButton, SIGNAL(clicked()), w, SLOT(leisureButton_clicked()));
    QObject::connect(sportButton, SIGNAL(clicked()), w, SLOT(sportButton_clicked()));
    QObject::connect(otherButton, SIGNAL(clicked()), w, SLOT(otherButton_clicked()));

    QObject::connect(addButton, SIGNAL(clicked()), w, SLOT(addButton_clicked()));
    QObject::connect(delButton, SIGNAL(clicked()), w, SLOT(delButton_clicked()));

    QObject::connect(clothesListWidget, SIGNAL(doubleClicked(QModelIndex)), w, SLOT(clothesListWidget_DoubleClicked(QModelIndex)));

    QObject::connect(clothesButton, SIGNAL(clicked()), secondLayerButton, SLOT(Clicked()));
    QObject::connect(bagButton, SIGNAL(clicked()), secondLayerButton, SLOT(Clicked()));
    QObject::connect(shoeButton, SIGNAL(clicked()), secondLayerButton, SLOT(Clicked()));
    QObject::connect(decoButton, SIGNAL(clicked()), secondLayerButton, SLOT(Clicked()));
    QObject::connect(cosButton, SIGNAL(clicked()), secondLayerButton, SLOT(Clicked()));
    QObject::connect(labelButton, SIGNAL(clicked()), secondLayerButton, SLOT(Clicked()));
    QObject::connect(springButton, SIGNAL(clicked()), secondLayerButton, SLOT(Clicked()));
    QObject::connect(summerButton, SIGNAL(clicked()), secondLayerButton, SLOT(Clicked()));
    QObject::connect(autumnButton, SIGNAL(clicked()), secondLayerButton, SLOT(Clicked()));
    QObject::connect(winterButton, SIGNAL(clicked()), secondLayerButton, SLOT(Clicked()));
    QObject::connect(workplaceButton, SIGNAL(clicked()), secondLayerButton, SLOT(Clicked()));
    QObject::connect(banquetButton, SIGNAL(clicked()), secondLayerButton, SLOT(Clicked()));
    QObject::connect(leisureButton, SIGNAL(clicked()), secondLayerButton, SLOT(Clicked()));
    QObject::connect(sportButton, SIGNAL(clicked()), secondLayerButton, SLOT(Clicked()));
    QObject::connect(otherButton, SIGNAL(clicked()), secondLayerButton, SLOT(Clicked()));

    QObject::connect(secondLayerButton, SIGNAL(clicked()), w, SLOT(secondLayerButton_clicked()));

    QObject::connect(daydressButton, SIGNAL(clicked()), w, SLOT(daydressListWidget_update()));
    QObject::connect(daydressListWidget, SIGNAL(clicked(QModelIndex)), w, SLOT(daydressListWidget_Clicked(QModelIndex)));
    QObject::connect(daydressListWidget, SIGNAL(doubleClicked(QModelIndex)), w, SLOT(daydressListWidget_DoubleClicked(QModelIndex)));

    QObject::connect(closeButton, SIGNAL(clicked()), w, SLOT(close()));

    w->clothesw.setWindowOpacity(1);
    w->clothesw.setWindowFlags(Qt::FramelessWindowHint);
    w->clothesw.setAttribute(Qt::WA_TranslucentBackground);

    createClothesButtonFunc(&w->clothesw);
    createClothesOtherObjectFunc(&w->clothesw);

    QObject::connect(picButton, SIGNAL(clicked()), &w->clothesw, SLOT(picButton_clicked()));
    QObject::connect(modifyButton, SIGNAL(clicked()), &w->clothesw, SLOT(modifyButton_clicked()));
    QObject::connect(cancelButton, SIGNAL(clicked()), &w->clothesw, SLOT(cancelButton_clicked()));

    QObject::connect(&w->clothesw, SIGNAL(modifyClothes()), w, SLOT(secondLayerButton_clicked()));

    w->filterw.setWindowOpacity(1);
    w->filterw.setWindowFlags(Qt::FramelessWindowHint);
    w->filterw.setAttribute(Qt::WA_TranslucentBackground);

    createFilterButtonFunc(&w->filterw);
    createFilterOtherObjectFunc(&w->filterw);

    QObject::connect(exitButton, SIGNAL(clicked()), &w->filterw, SLOT(exitButton_clicked()));
    QObject::connect(filterListWidget, SIGNAL(doubleClicked(QModelIndex)), &w->filterw, SLOT(filterListWidget_DoubleClicked(QModelIndex)));
    QObject::connect(&w->filterw, SIGNAL(modifyDaydress()), w, SLOT(daydressListWidget_update()));

    return a.exec();
}


//初始化所有全局需赋值变量
void initAllGlobalVariables()
{
    clothesFont.setFamily(QString("Hiragino Sans GB W6"));
    clothesFont.setPointSize(CLOTHESFONTSIZE);

    digiClockDateFont.setFamily(QString("微软雅黑"));
    digiClockDateFont.setPointSize(DIGICLOCKDATEFONTSIZE);

    weatherPlaceFont.setFamily(QString("Hiragino Sans GB W6"));
    weatherPlaceFont.setPointSize(WEATHERPLACEFONTSIZE);

    weatherTempFont.setFamily(QString("Hiragino Sans GB W6"));
    weatherTempFont.setPointSize(WEATHERTEMPFONTSIZE);

    mainPressed = NOBUTTONPRESSED;
    typePressed = NOBUTTONPRESSED;
    seasonPressed = NOBUTTONPRESSED;
    classtypePressed = NOBUTTONPRESSED;
    addPressed = NOBUTTONPRESSED;

    selectClothesIdNumInt = INTNUMBERINIT;
    selectDaydressIdNumInt = INTNUMBERINIT;
    daydressColSelectInt = DAYDRESSLISTWIDGETITEMNOSELECT;
}
