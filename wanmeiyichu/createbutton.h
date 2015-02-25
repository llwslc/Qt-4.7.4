#ifndef CREATEBUTTON_H
#define CREATEBUTTON_H

#include "common.h"
#include "drawcontrols.h"

#define NOBUTTONLEFTX -500                //按钮不存在左侧起始X位置
#define NOBUTTONLEFTY 15                  //按钮不存在左侧起始Y位置
#define NOBUTTONRIGHTX 1300               //按钮不存在右侧侧起始Y位置
#define NOBUTTONRIGHTY 15                 //按钮不存在右侧起始Y位置
#define NOBUTTONTOPX 295                  //按钮不存在上侧起始X位置
#define NOBUTTONTOPY -500                 //按钮不存在上侧起始Y位置
#define NOBUTTONBOTTOMX 295               //按钮不存在下侧侧起始Y位置
#define NOBUTTONBOTTOMY 1300              //按钮不存在下侧起始Y位置

#define MAINBUTTONX 130                   //主界面功能按钮起始X位置
#define MAINBUTTONY 15                    //主界面功能按钮起始Y位置
#define MAINBUTTONWIDTH 135               //主界面功能按钮宽度
#define MAINBUTTONHEIGHT 135              //主界面功能按钮高度
#define MAINBUTTONSPACE 10                //主界面功能按钮间隔

#define MYCLOTHESBUTTONXX 295              //我的衣橱按钮起始X位置
#define MYCLOTHESBUTTONXY 15               //我的衣橱按钮起始Y位置
#define MYCLOTHESBUTTONXWIDTH 240          //我的衣橱按钮宽度
#define MYCLOTHESBUTTONXHEIGHT 150         //我的衣橱按钮高度1
#define MYCLOTHESBUTTONXHEIGHTER 250       //我的衣橱按钮高度2
#define MYCLOTHESBUTTONXSPACE 10           //我的衣橱按钮间隔

#define FASHIONBUTTONX 295                 //风格搭配按钮起始X位置
#define FASHIONBUTTONY 15                  //风格搭配按钮起始Y位置
#define FASHIONBUTTONWIDTH 240             //风格搭配按钮宽度
#define FASHIONBUTTONHEIGHT 106            //风格搭配按钮高度1
#define FASHIONBUTTONHEIGHTER 135          //风格搭配按钮高度2
#define FASHIONBUTTONSPACE 10              //风格搭配按钮间隔

#define NOBUTTONPRESSED -1                 //没有按钮按下

#define MYCLOTHESPRESSED 0                 //我的衣橱按钮按下
#define FASHIONPRESSED 1                   //我的搭配按钮按下
#define DAYDRESSPRESSED 2                  //每日装扮按钮按下
#define SETTINGPRESSED 3                   //主页按钮按下

#define CLOTHESBUTTONPRESSED 0             //衣服按钮按下
#define BAGBUTTONRESSED 1                  //包包按钮按下
#define SHOEBUTTONRESSED 2                 //鞋帽按钮按下
#define DECOBUTTONRESSED 3                 //饰品按钮按下
#define COSBUTTONRESSED 4                  //化妆品按钮按下
#define LABELBUTTONRESSED 5                //其他按钮按下

#define SPRINGBUTTONRESSED 0               //春季按钮按下
#define SUMMERBUTTONRESSED 1               //夏季按钮按下
#define AUTUMNBUTTONRESSED 2               //秋季按钮按下
#define WINTERBUTTONRESSED 3               //冬季按钮按下

#define WORKPLACEBUTTONRESSED 0            //职场按钮按下
#define BANQUETBUTTONRESSED 1              //宴会按钮按下
#define LEISUREBUTTONRESSED 2              //休闲按钮按下
#define SPORTBUTTONRESSED 3                //运动按钮按下
#define OTHERBUTTONRESSED 4                //其他按钮按下

#define LISTWIDGETNOSELECT -1              //列表没有选择

#define ADDDELBUTTONX 295                  //添加删除按钮起始X位置
#define ADDDELBUTTONY 495                  //添加删除按钮起始X位置
#define ADDDELBUTTONWIDTH 240              //添加删除按钮宽度
#define ADDDELBUTTONHEIGHT 90              //添加删除按钮高度
#define ADDDELBUTTONSPACE 10               //添加删除按钮间隔

#define CLOSEBUTTONX 749                   //关闭按钮起始X位置
#define CLOSEBUTTONY 15                    //关闭按钮起始Y位置
#define CLOSEBUTTONWIDTH 36                //关闭按钮宽度
#define CLOSEBUTTONHEIGHT 36               //关闭按钮高度

extern imageButton *myclothesButton;       //我的衣橱
extern imageButton *fashionButton;         //风格搭配
extern imageButton *daydressButton;        //每日装扮
extern imageButton *settingButton;         //主页

extern imageButton *clothesButton;         //衣服
extern imageButton *bagButton;             //包包
extern imageButton *shoeButton;            //鞋帽
extern imageButton *decoButton;            //饰品
extern imageButton *cosButton;             //化妆品
extern imageButton *labelButton;           //其他

extern imageButton *springButton;          //春季
extern imageButton *summerButton;          //夏季
extern imageButton *autumnButton;          //秋季
extern imageButton *winterButton;          //冬季
extern imageButton *workplaceButton;       //职场
extern imageButton *banquetButton;         //宴会
extern imageButton *leisureButton;         //休闲
extern imageButton *sportButton;           //运动
extern imageButton *otherButton;           //其他

extern buttonsClicked *secondLayerButton;  //第二层按钮点击

extern imageButton *addButton;             //添加按钮
extern imageButton *delButton;             //删除按钮

extern int mainPressed;                    //主界面按钮选择
extern int typePressed;                    //类型选择
extern int seasonPressed;                  //季节选择
extern int classtypePressed;               //场合选择
extern int addPressed;                     //添加按钮选择

extern imageButton *closeButton;           //主界面关闭按钮

void createMainButtonFunc(QWidget *parent);

#define PICBUTTONX 485                     //图片按钮起始X位置
#define PICBUTTONY 15                      //图片按钮起始Y位置
#define PICBUTTONWIDTH 300                 //图片按钮宽度
#define PICBUTTONHEIGHT 400                //图片按钮高度

#define MODIFYBUTTONX 497                  //修改按钮起始X位置
#define MODIFYBUTTONY 430                  //修改按钮起始Y位置
#define MODIFYBUTTONWIDTH 133              //修改按钮宽度
#define MODIFYBUTTONHEIGHT 50              //修改按钮高度
#define MODIFYBUTTONSPACE 10               //修改按钮间隔距离

extern imageButton *picButton;             //图片按钮
extern imageButton *modifyButton;          //修改按钮
extern imageButton *cancelButton;          //取消按钮

void createClothesButtonFunc(QWidget *parent);

#define EXITBUTTONX 749                    //关闭按钮起始X位置
#define EXITBUTTONY 15                     //关闭按钮起始X位置
#define EXITBUTTONWIDTH 36                 //关闭按钮宽度
#define EXITBUTTONHEIGHT 36                //关闭按钮高度
extern imageButton *exitButton;            //关闭按钮
void createFilterButtonFunc(QWidget *parent);

#endif // CREATEBUTTON_H
