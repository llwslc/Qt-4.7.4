#ifndef OTHEROBJECT_H
#define OTHEROBJECT_H

#include "common.h"
#include "drawcontrols.h"

#define DIGICLOCKTIMEX 330                   //钟表时间起始X位置
#define DIGICLOCKTIMEY 125                   //钟表时间起始Y位置
#define DIGICLOCKPOINTY 140                  //钟表隔位点起始Y位置
#define DIGICLOCKTIMEWIDTH 9                 //钟表时间宽度1
#define DIGICLOCKTIMEWIDTHER 52              //钟表时间宽度2
#define DIGICLOCKTIMEHEIGHT 48               //钟表时间高度1
#define DIGICLOCKTIMEHEIGHTER 79             //钟表时间高度2
#define DIGICLOCKTIMESPACE 5                 //钟表时间间隔距离
#define DIGICLOCKTIMEBKGX 300                //钟表时间背景起始X位置
#define DIGICLOCKTIMEBKGY 175                //钟表时间背景起始Y位置
#define DIGICLOCKTIMEBKGWIDTH 420            //钟表时间背景宽度
#define DIGICLOCKTIMEBKGHEIGHT 34            //钟表时间背景高度
#define DIGICLOCKDATEBKGX 375                //钟表日期背景起始X位置
#define DIGICLOCKDATEBKGY 210                //钟表日期背景起始Y位置
#define DIGICLOCKDATEBKGWIDTH 270            //钟表日期背景宽度
#define DIGICLOCKDATEBKGHEIGHT 35            //钟表日期背景高度

extern imageButton *digiClockHourHigh;       //钟表小时高位
extern imageButton *digiClockHourLow;        //钟表小时低位
extern imageButton *digiClockMinuteHigh;     //钟表分钟高位
extern imageButton *digiClockMinuteLow;      //钟表分钟低位
extern imageButton *digiClockSecondHigh;     //钟表秒数高位
extern imageButton *digiClockSecondLow;      //钟表秒数低位
extern imageButton *digiClockPointsHigh;     //钟表隔位点高位
extern imageButton *digiClockPointsLow;      //钟表隔位点低位
extern imageButton *digiClockTimeBkg;        //钟表时间背景
extern imageButton *digiClockDateBkg;        //钟表日期背景
extern QLabel *digiClockDateBkgText;         //钟表日期背景文字


#define WEATHERBACKGROUNDX 300               //天气预报背景起始X位置
#define WEATHERBACKGROUNDY 305               //天气预报背景起始Y位置
#define WEATHERBACKGROUNDWIDTH 420           //天气预报背景宽度
#define WEATHERBACKGROUNDHEIGHT 220          //天气预报背景高度
#define WEATHERPLACEX 300                    //天气预报地点起始X位置
#define WEATHERPLACEY 305                    //天气预报地点起始Y位置
#define WEATHERPLACEWIDTH 240                //天气预报地点宽度
#define WEATHERPLACEHEIGHT 125               //天气预报地点高度
#define WEATHERTEMPX 300                     //天气预报温度起始X位置
#define WEATHERTEMPY 450                     //天气预报温度起始Y位置
#define WEATHERTEMPWIDTH 240                 //天气预报温度宽度
#define WEATHERTEMPHEIGHT 75                 //天气预报温度高度
#define WEATHERIMAGEX 540                    //天气预报图标起始X位置
#define WEATHERIMAGEY 305                    //天气预报图标起始Y位置
#define WEATHERIMAGEWIDTH 180                //天气预报图标宽度
#define WEATHERIMAGEHEIGHT 160               //天气预报图标高度
#define WEATHERTITLEX 540                    //天气预报天气起始X位置
#define WEATHERTITLEY 460                    //天气预报天气起始Y位置
#define WEATHERTITLEWIDTH 180                //天气预报天气宽度
#define WEATHERTITLEHEIGHT 65                //天气预报天气高度
extern imageButton *weatherBackground;       //天气预报背景
extern imageButton *weatherImage;            //天气图标按钮
extern QLabel *weatherPlace;                 //天气预报地点
extern QLabel *weatherTemp;                  //天气预报温度
extern QLabel *weatherTitle;                 //天气预报天气


#define CLOTHESLISTWIDGETX 295               //衣服图片列表起始X位置
#define CLOTHESLISTWIDGETY 15                //衣服图片列表起始Y位置
#define CLOTHESLISTWIDGETWIDTH 490           //衣服图片列表宽度
#define CLOTHESLISTWIDGETHEIGHT 470          //衣服图片列表高度
#define CLOTHESLISTWIDGETCOLUMNNUM 2         //衣服图片列表列数
#define CLOTHESLISTWIDGETCOLUMNWIDTH 227     //衣服图片列表宽度(490-36)/2-1
#define CLOTHESLISTWIDGETCOLUMNHEIGHT 297    //衣服图片列表高度
#define CLOTHESLISTWIDGETPICWIDTH 220        //单张图片宽度227-2*3-1
#define CLOTHESLISTWIDGETPICHEIGHT 291       //单张图片高度297-2*3
#define CLOTHESLISTWIDGETITEMLEFT 0          //衣服列表左侧
#define CLOTHESLISTWIDGETITEMRIGHT 1         //衣服列表右侧
extern QTableWidget *clothesListWidget;      //衣服图片列表

#define DAYDRESSDATEEDITX 295                //每日装扮日期编辑框起始X位置
#define DAYDRESSDATEEDITY 15                 //每日装扮日期编辑框起始Y位置
#define DAYDRESSDATEEDITWIDTH 220            //每日装扮日期编辑框宽度
#define DAYDRESSDATEEDITHEIGHT 40            //每日装扮日期编辑框高度
extern QDateEdit *daydressDateEdit;          //每日装扮日期编辑框

#define DAYDRESSLISTWIDGETX 295              //每日装扮图片列表起始X位置
#define DAYDRESSLISTWIDGETY 65               //每日装扮图片列表起始Y位置
#define DAYDRESSLISTWIDGETWIDTH 490          //每日装扮图片列表宽度
#define DAYDRESSLISTWIDGETHEIGHT 420         //每日装扮图片列表高度
#define DAYDRESSLISTWIDGETCOLUMNNUM 6        //每日装扮图片列表列数
#define DAYDRESSLISTWIDGETCOLUMNWIDTH 75     //每日装扮图片列表宽度(490-36)/6-1
#define DAYDRESSLISTWIDGETCOLUMNHEIGHT 97    //每日装扮图片列表高度
#define DAYDRESSLISTWIDGETPICWIDTH 70        //单张图片宽度75-2*2-1
#define DAYDRESSLISTWIDGETPICHEIGHT 93       //单张图片高度97-2*2
#define DAYDRESSLISTWIDGETITEMNOSELECT -1    //每日装扮列表未选择列数
#define DAYDRESSLISTWIDGETITEMUPCLOTHESONE 0 //每日装扮列表上装一列数
#define DAYDRESSLISTWIDGETITEMUPCLOTHESTWO 1 //每日装扮列表上装二列数
#define DAYDRESSLISTWIDGETITEMDOWNCLOTHES 2  //每日装扮列表下装列数
#define DAYDRESSLISTWIDGETITEMBAG 3          //每日装扮列表包包列数
#define DAYDRESSLISTWIDGETITEMSHOE 4         //每日装扮列表鞋帽列数
#define DAYDRESSLISTWIDGETITEMDECO 5         //每日装扮列表饰品列数
extern QTableWidget *daydressListWidget;     //每日装扮图片列表

void createMainOtherObjectFunc(QWidget *parent);

#define NAMELINEEDITX 148                    //名称编辑框起始X位置145+3
#define NAMELINEEDITY 18                     //名称编辑框起始Y位置
#define NAMELINEEDITWIDTH 300                //名称编辑框宽度
#define NAMELINEEDITHEIGHT 38                //名称编辑框高度
#define NAMELINEEDITSPACE 15                 //名称编辑框间隔距离
#define NOTETEXTEDITWIDTH 630                //备注文本框宽度
#define NOTETEXTEDITHEIGHT 88                //备注文本框高度

extern int selectClothesIdNumInt;            //选中的衣物编号
extern int selectDaydressIdNumInt;           //选中的每日装扮衣服编号
extern int daydressColSelectInt;             //每日装扮类表选择行号
extern QLineEdit *nameLineEdit;              //名称编辑框
extern noMoveComboBox *typeComboBox;         //类型组合框
extern noMoveComboBox *seasonComboBox;       //季节组合框
extern noMoveComboBox *classtypeComboBox;    //场合组合框
extern QLineEdit *brandLineEdit;             //品牌编辑框
extern QLineEdit *priceLineEdit;             //价格编辑框
extern QDateEdit *timeDateEdit;              //时间编辑框
extern QLineEdit *storePlaceLineEdit;        //存放地编辑框
extern QLineEdit *buyPlaceLineEdit;          //购买地编辑框
extern QTextEdit *noteTextEdit;              //备注文本框
extern QString clothesPicPathString;         //图片途径

void createClothesOtherObjectFunc(QWidget *parent);

#define FILTERLISTWIDGETX 15                 //筛选衣物列表起始X位置
#define FILTERLISTWIDGETY 60                 //筛选衣物列表起始Y位置
#define FILTERLISTWIDGETWIDTH 770            //筛选衣物列表宽度
#define FILTERLISTWIDGETHEIGHT 525           //筛选衣物列表高度
#define FILTERLISTWIDGETCOLUMNNUM 3          //筛选衣物列表列数
#define FILTERLISTWIDGETCOLUMNWIDTH 244      //筛选衣物列表宽度(770-36)/3-1
#define FILTERLISTWIDGETCOLUMNHEIGHT 325     //筛选衣物列表高度
#define FILTERLISTWIDGETPICWIDTH 237         //单张图片宽度244-2*3-1
#define FILTERLISTWIDGETPICHEIGHT 319        //单张图片高度325-2*3
#define FILTERLISTWIDGETITEMONE 0            //衣服列表第一列
#define FILTERLISTWIDGETITEMTWO 1            //衣服列表第二列
#define FILTERLISTWIDGETITEMTHREE 2          //衣服列表第二列
extern QTableWidget *filterListWidget;       //每日装扮筛选衣物列表
void createFilterOtherObjectFunc(QWidget *parent);

#endif // OTHEROBJECT_H
