#ifndef STMATION_H
#define STMATION_H

#include "common.h"
#include "createbutton.h"
#include "otherobject.h"

extern QState *myclothesState;                   //我的衣橱
extern QState *fashionState;                     //风格搭配
extern QState *daydressStatue;                   //每日装扮
extern QState *settingState;                     //主页
extern QState *clothesState;                     //第二层按钮

extern QStateMachine *stateMachine;              //状态机

extern QSignalTransition *myclothesToClothesST;  //我的衣橱到第二层转换动画
extern QSignalTransition *myclothesToFashionST;  //我的衣橱到风格搭配
extern QSignalTransition *myclothesToDaydressST; //我的衣橱到每日装扮
extern QSignalTransition *myclothesToSettingST;  //我的衣橱到主页

extern QSignalTransition *fashionToClothesST;    //风格搭配到第二层转换动画
extern QSignalTransition *fashionToMyclothST;    //风格搭配到我的衣橱
extern QSignalTransition *fashionToDaydressST;   //风格搭配到每日装扮
extern QSignalTransition *fashionToSettingST;    //风格搭配到主页

extern QSignalTransition *daydressToMyclothesST; //每日装扮到我的衣橱
extern QSignalTransition *daydressToFashionST;   //每日装扮到风格搭配
extern QSignalTransition *daydressToSettingST;   //每日装扮到主页

extern QSignalTransition *settingToMyclothesST;  //主页到我的衣橱
extern QSignalTransition *settingToFashionST;    //主页到风格搭配
extern QSignalTransition *settingToDaydressST;   //主页到每日装扮

extern QSignalTransition *clothesToMyclothesST;   //第二层转换到我的衣橱动画
extern QSignalTransition *clothesToFashionST;     //第二层转换到风格搭配
extern QSignalTransition *clothesToDaydressST;    //第二层转换到每日装扮
extern QSignalTransition *clothesToSettingST;     //第二层转换到主页

void createMainStateFunc();

void createMainSettingStateFunc();
void createMainMyclothesStateFunc();
void createMainFashionStateFunc();
void createMainDayDressStateFunc();
void createMainClothesStateFunc();
void createMainSignalTransitionFunc();
void createMainPropertyAnimationFunc();

#endif // STMATION_H
