#include "createbutton.h"

imageButton *myclothesButton;
imageButton *fashionButton;
imageButton *daydressButton;
imageButton *settingButton;

imageButton *clothesButton;
imageButton *bagButton;
imageButton *shoeButton;
imageButton *decoButton;
imageButton *cosButton;
imageButton *labelButton;

imageButton *springButton;
imageButton *summerButton;
imageButton *autumnButton;
imageButton *winterButton;
imageButton *workplaceButton;
imageButton *banquetButton;
imageButton *leisureButton;
imageButton *sportButton;
imageButton *otherButton;

buttonsClicked *secondLayerButton;

imageButton *addButton;
imageButton *delButton;

int mainPressed;
int typePressed;
int seasonPressed;
int classtypePressed;
int addPressed;

imageButton *closeButton;

void createMainButtonFunc(QWidget *parent)
{
    myclothesButton = new imageButton(parent);
    fashionButton = new imageButton(parent);
    daydressButton = new imageButton(parent);
    settingButton = new imageButton(parent);

    clothesButton = new imageButton(parent);
    bagButton = new imageButton(parent);
    shoeButton = new imageButton(parent);
    decoButton = new imageButton(parent);
    cosButton = new imageButton(parent);
    labelButton = new imageButton(parent);

    springButton = new imageButton(parent);
    summerButton = new imageButton(parent);
    autumnButton = new imageButton(parent);
    winterButton = new imageButton(parent);
    workplaceButton = new imageButton(parent);
    banquetButton = new imageButton(parent);
    leisureButton = new imageButton(parent);
    sportButton = new imageButton(parent);
    otherButton = new imageButton(parent);

    addButton = new imageButton(parent);
    delButton = new imageButton(parent);

    secondLayerButton = new buttonsClicked(parent);

    closeButton = new imageButton(parent);

    int buttonX = INTNUMBERINIT;
    int buttonY = INTNUMBERINIT;

    //我的衣橱
    buttonX = MAINBUTTONX;
    buttonY = MAINBUTTONY;
    myclothesButton->setButtonPicture(QPixmap(":/images/main_btn_mycloth_normal.png"));
    myclothesButton->setPressPicture(QPixmap(":/images/main_btn_mycloth_pressed.png"));
    myclothesButton->setReleasePicture(QPixmap(":/images/main_btn_mycloth_normal.png"));
    myclothesButton->set_X_Y_width_height(buttonX, buttonY, MAINBUTTONWIDTH, MAINBUTTONHEIGHT);

    //风格搭配
    buttonX = MAINBUTTONX;
    buttonY = buttonY + MAINBUTTONHEIGHT + MAINBUTTONSPACE;
    fashionButton->setButtonPicture(QPixmap(":/images/main_btn_fashion_normal.png"));
    fashionButton->setPressPicture(QPixmap(":/images/main_btn_fashion_pressed.png"));
    fashionButton->setReleasePicture(QPixmap(":/images/main_btn_fashion_normal.png"));
    fashionButton->set_X_Y_width_height(buttonX, buttonY, MAINBUTTONWIDTH, MAINBUTTONHEIGHT);

    //每日装扮
    buttonX = MAINBUTTONX;
    buttonY = buttonY + MAINBUTTONHEIGHT + MAINBUTTONSPACE;
    daydressButton->setButtonPicture(QPixmap(":/images/main_btn_daydress_normal.png"));
    daydressButton->setPressPicture(QPixmap(":/images/main_btn_daydress_pressed.png"));
    daydressButton->setReleasePicture(QPixmap(":/images/main_btn_daydress_normal.png"));
    daydressButton->set_X_Y_width_height(buttonX, buttonY, MAINBUTTONWIDTH, MAINBUTTONHEIGHT);

    //主页
    buttonX = MAINBUTTONX;
    buttonY = buttonY + MAINBUTTONHEIGHT + MAINBUTTONSPACE;
    settingButton->setButtonPicture(QPixmap(":/images/main_btn_setting_normal.png"));
    settingButton->setPressPicture(QPixmap(":/images/main_btn_setting_pressed.png"));
    settingButton->setReleasePicture(QPixmap(":/images/main_btn_setting_normal.png"));
    settingButton->set_X_Y_width_height(buttonX, buttonY, MAINBUTTONWIDTH, MAINBUTTONHEIGHT);

    //我的衣橱->衣服
    buttonX = MYCLOTHESBUTTONXX;
    buttonY = MYCLOTHESBUTTONXY;
    clothesButton->setButtonPicture(QPixmap(":/images/cloth_cate_cloth_normal.png"));
    clothesButton->setPressPicture(QPixmap(":/images/cloth_cate_cloth_pressed.png"));
    clothesButton->setReleasePicture(QPixmap(":/images/cloth_cate_cloth_normal.png"));
    clothesButton->set_X_Y_width_height(buttonX, buttonY, MYCLOTHESBUTTONXWIDTH, MYCLOTHESBUTTONXHEIGHTER);

    //我的衣橱->包包
    buttonX = MYCLOTHESBUTTONXX;
    buttonY = buttonY + MYCLOTHESBUTTONXHEIGHTER + MYCLOTHESBUTTONXSPACE;
    bagButton->setButtonPicture(QPixmap(":/images/cloth_cate_bag_normal.png"));
    bagButton->setPressPicture(QPixmap(":/images/cloth_cate_bag_pressed.png"));
    bagButton->setReleasePicture(QPixmap(":/images/cloth_cate_bag_normal.png"));
    bagButton->set_X_Y_width_height(buttonX, buttonY, MYCLOTHESBUTTONXWIDTH, MYCLOTHESBUTTONXHEIGHT);

    //我的衣橱->鞋帽
    buttonX = MYCLOTHESBUTTONXX;
    buttonY = buttonY + MYCLOTHESBUTTONXHEIGHT + MYCLOTHESBUTTONXSPACE;
    shoeButton->setButtonPicture(QPixmap(":/images/cloth_cate_shoe_normal.png"));
    shoeButton->setPressPicture(QPixmap(":/images/cloth_cate_shoe_pressed.png"));
    shoeButton->setReleasePicture(QPixmap(":/images/cloth_cate_shoe_normal.png"));
    shoeButton->set_X_Y_width_height(buttonX, buttonY, MYCLOTHESBUTTONXWIDTH, MYCLOTHESBUTTONXHEIGHT);

    //我的衣橱->饰品
    buttonX = MYCLOTHESBUTTONXX + MYCLOTHESBUTTONXWIDTH + MYCLOTHESBUTTONXSPACE;
    buttonY = MYCLOTHESBUTTONXY;
    decoButton->setButtonPicture(QPixmap(":/images/cloth_cate_deco_normal.png"));
    decoButton->setPressPicture(QPixmap(":/images/cloth_cate_deco_pressed.png"));
    decoButton->setReleasePicture(QPixmap(":/images/cloth_cate_deco_normal.png"));
    decoButton->set_X_Y_width_height(buttonX, buttonY, MYCLOTHESBUTTONXWIDTH, MYCLOTHESBUTTONXHEIGHT);

    //我的衣橱->化妆品
    buttonX = MYCLOTHESBUTTONXX + MYCLOTHESBUTTONXWIDTH + MYCLOTHESBUTTONXSPACE;
    buttonY = buttonY + MYCLOTHESBUTTONXHEIGHT + MYCLOTHESBUTTONXSPACE;
    cosButton->setButtonPicture(QPixmap(":/images/cloth_cate_cos_normal.png"));
    cosButton->setPressPicture(QPixmap(":/images/cloth_cate_cos_pressed.png"));
    cosButton->setReleasePicture(QPixmap(":/images/cloth_cate_cos_normal.png"));
    cosButton->set_X_Y_width_height(buttonX, buttonY, MYCLOTHESBUTTONXWIDTH, MYCLOTHESBUTTONXHEIGHT);

    //我的衣橱->自定义
    buttonX = MYCLOTHESBUTTONXX + MYCLOTHESBUTTONXWIDTH + MYCLOTHESBUTTONXSPACE;
    buttonY = buttonY + MYCLOTHESBUTTONXHEIGHT + MYCLOTHESBUTTONXSPACE;
    labelButton->setButtonPicture(QPixmap(":/images/cloth_cate_label_normal.png"));
    labelButton->setPressPicture(QPixmap(":/images/cloth_cate_label_pressed.png"));
    labelButton->setReleasePicture(QPixmap(":/images/cloth_cate_label_normal.png"));
    labelButton->set_X_Y_width_height(buttonX, buttonY, MYCLOTHESBUTTONXWIDTH, MYCLOTHESBUTTONXHEIGHTER);

    //风格搭配->春季
    buttonX = FASHIONBUTTONX;
    buttonY = FASHIONBUTTONY;
    springButton->setButtonPicture(QPixmap(":/images/match_spring.png"));
    springButton->setPressPicture(QPixmap(":/images/match_spring_pressed.png"));
    springButton->setReleasePicture(QPixmap(":/images/match_spring.png"));
    springButton->set_X_Y_width_height(buttonX, buttonY, FASHIONBUTTONWIDTH, FASHIONBUTTONHEIGHT);

    //风格搭配->秋季
    buttonX = FASHIONBUTTONX;
    buttonY = buttonY + FASHIONBUTTONHEIGHT + FASHIONBUTTONSPACE;
    autumnButton->setButtonPicture(QPixmap(":/images/match_autumn.png"));
    autumnButton->setPressPicture(QPixmap(":/images/match_autumn_pressed.png"));
    autumnButton->setReleasePicture(QPixmap(":/images/match_autumn.png"));
    autumnButton->set_X_Y_width_height(buttonX, buttonY, FASHIONBUTTONWIDTH, FASHIONBUTTONHEIGHT);

    //风格搭配->职场
    buttonX = FASHIONBUTTONX;
    buttonY = buttonY + FASHIONBUTTONHEIGHT + FASHIONBUTTONSPACE;
    workplaceButton->setButtonPicture(QPixmap(":/images/match_workplace.png"));
    workplaceButton->setPressPicture(QPixmap(":/images/match_workplace_pressed.png"));
    workplaceButton->setReleasePicture(QPixmap(":/images/match_workplace.png"));
    workplaceButton->set_X_Y_width_height(buttonX, buttonY, FASHIONBUTTONWIDTH, FASHIONBUTTONHEIGHT);

    //风格搭配->休闲
    buttonX = FASHIONBUTTONX;
    buttonY = buttonY + FASHIONBUTTONHEIGHT + FASHIONBUTTONSPACE;
    leisureButton->setButtonPicture(QPixmap(":/images/match_leisure.png"));
    leisureButton->setPressPicture(QPixmap(":/images/match_leisure_pressed.png"));
    leisureButton->setReleasePicture(QPixmap(":/images/match_leisure.png"));
    leisureButton->set_X_Y_width_height(buttonX, buttonY, FASHIONBUTTONWIDTH, FASHIONBUTTONHEIGHT);

    //风格搭配->运动
    buttonX = FASHIONBUTTONX;
    buttonY = buttonY + FASHIONBUTTONHEIGHT + FASHIONBUTTONSPACE;
    sportButton->setButtonPicture(QPixmap(":/images/match_sport.png"));
    sportButton->setPressPicture(QPixmap(":/images/match_sport_pressed.png"));
    sportButton->setReleasePicture(QPixmap(":/images/match_sport.png"));
    sportButton->set_X_Y_width_height(buttonX, buttonY, FASHIONBUTTONWIDTH, FASHIONBUTTONHEIGHT);

    //风格搭配->夏季
    buttonX = FASHIONBUTTONX + FASHIONBUTTONWIDTH + FASHIONBUTTONSPACE;
    buttonY = FASHIONBUTTONY;
    summerButton->setButtonPicture(QPixmap(":/images/match_summer.png"));
    summerButton->setPressPicture(QPixmap(":/images/match_summer_pressed.png"));
    summerButton->setReleasePicture(QPixmap(":/images/match_summer.png"));
    summerButton->set_X_Y_width_height(buttonX, buttonY, FASHIONBUTTONWIDTH, FASHIONBUTTONHEIGHTER);

    //风格搭配->冬季
    buttonX = FASHIONBUTTONX + FASHIONBUTTONWIDTH + FASHIONBUTTONSPACE;
    buttonY = buttonY + FASHIONBUTTONHEIGHTER + FASHIONBUTTONSPACE;
    winterButton->setButtonPicture(QPixmap(":/images/match_winter.png"));
    winterButton->setPressPicture(QPixmap(":/images/match_winter_pressed.png"));
    winterButton->setReleasePicture(QPixmap(":/images/match_winter.png"));
    winterButton->set_X_Y_width_height(buttonX, buttonY, FASHIONBUTTONWIDTH, FASHIONBUTTONHEIGHTER);

    //风格搭配->宴会
    buttonX = FASHIONBUTTONX + FASHIONBUTTONWIDTH + FASHIONBUTTONSPACE;
    buttonY = buttonY + FASHIONBUTTONHEIGHTER + FASHIONBUTTONSPACE;
    banquetButton->setButtonPicture(QPixmap(":/images/match_banquet.png"));
    banquetButton->setPressPicture(QPixmap(":/images/match_banquet_pressed.png"));
    banquetButton->setReleasePicture(QPixmap(":/images/match_banquet.png"));
    banquetButton->set_X_Y_width_height(buttonX, buttonY, FASHIONBUTTONWIDTH, FASHIONBUTTONHEIGHTER);

    //风格搭配->其他
    buttonX = FASHIONBUTTONX + FASHIONBUTTONWIDTH + FASHIONBUTTONSPACE;
    buttonY = buttonY + FASHIONBUTTONHEIGHTER + FASHIONBUTTONSPACE;
    otherButton->setButtonPicture(QPixmap(":/images/match_other.png"));
    otherButton->setPressPicture(QPixmap(":/images/match_other_pressed.png"));
    otherButton->setReleasePicture(QPixmap(":/images/match_other.png"));
    otherButton->set_X_Y_width_height(buttonX, buttonY, FASHIONBUTTONWIDTH, FASHIONBUTTONHEIGHTER);

    //添加
    buttonX = ADDDELBUTTONX;
    buttonY = ADDDELBUTTONY;
    addButton->setButtonPicture(QPixmap(":/images/cloth_add_normal.png"));
    addButton->setPressPicture(QPixmap(":/images/cloth_add_pressed.png"));
    addButton->setReleasePicture(QPixmap(":/images/cloth_add_normal.png"));
    addButton->set_X_Y_width_height(buttonX, buttonY, ADDDELBUTTONWIDTH, ADDDELBUTTONHEIGHT);

    //删除
    buttonX = buttonX + ADDDELBUTTONWIDTH + ADDDELBUTTONSPACE;
    buttonY = ADDDELBUTTONY;
    delButton->setButtonPicture(QPixmap(":/images/cloth_del_normal.png"));
    delButton->setPressPicture(QPixmap(":/images/cloth_del_pressed.png"));
    delButton->setReleasePicture(QPixmap(":/images/cloth_del_normal.png"));
    delButton->set_X_Y_width_height(buttonX, buttonY, ADDDELBUTTONWIDTH, ADDDELBUTTONHEIGHT);

    //关闭按钮
    closeButton->setButtonPicture(QPixmap(":/images/main_btn_close_normal.png"));
    closeButton->setPressPicture(QPixmap(":/images/main_btn_close_pressed.png"));
    closeButton->setReleasePicture(QPixmap(":/images/main_btn_close_normal.png"));
    closeButton->set_X_Y_width_height(CLOSEBUTTONX, CLOSEBUTTONY, CLOSEBUTTONWIDTH, CLOSEBUTTONHEIGHT);
}


imageButton *picButton;
imageButton *modifyButton;
imageButton *cancelButton;

void createClothesButtonFunc(QWidget *parent)
{
    picButton = new imageButton(parent);
    modifyButton = new imageButton(parent);
    cancelButton = new imageButton(parent);


    int buttonX = INTNUMBERINIT;
    int buttonY = INTNUMBERINIT;
    //图片按钮
    buttonX = PICBUTTONX;
    buttonY = PICBUTTONY;
    picButton->setButtonPicture(QPixmap(":/images/cloth_pic_normal.png"));
    picButton->setPressPicture(QPixmap(":/images/cloth_pic_pressed.png"));
    picButton->setReleasePicture(QPixmap(":/images/cloth_pic_normal.png"));
    picButton->set_X_Y_width_height(buttonX, buttonY, PICBUTTONWIDTH, PICBUTTONHEIGHT);
    //修改按钮
    buttonX = MODIFYBUTTONX;
    buttonY = MODIFYBUTTONY;
    modifyButton->setButtonPicture(QPixmap(":/images/cloth_modify_normal.png"));
    modifyButton->setPressPicture(QPixmap(":/images/cloth_modify_pressed.png"));
    modifyButton->setReleasePicture(QPixmap(":/images/cloth_modify_normal.png"));
    modifyButton->set_X_Y_width_height(buttonX, buttonY, MODIFYBUTTONWIDTH, MODIFYBUTTONHEIGHT);
    //取消按钮
    buttonX = buttonX + MODIFYBUTTONWIDTH + MODIFYBUTTONSPACE;
    buttonY = MODIFYBUTTONY;
    cancelButton->setButtonPicture(QPixmap(":/images/cloth_cancel_normal.png"));
    cancelButton->setPressPicture(QPixmap(":/images/cloth_cancel_pressed.png"));
    cancelButton->setReleasePicture(QPixmap(":/images/cloth_cancel_normal.png"));
    cancelButton->set_X_Y_width_height(buttonX, buttonY, MODIFYBUTTONWIDTH, MODIFYBUTTONHEIGHT);
}

imageButton *exitButton;
void createFilterButtonFunc(QWidget *parent)
{
    exitButton = new imageButton(parent);

    //退出按钮
    exitButton->setButtonPicture(QPixmap(":/images/main_btn_close_normal.png"));
    exitButton->setPressPicture(QPixmap(":/images/main_btn_close_pressed.png"));
    exitButton->setReleasePicture(QPixmap(":/images/main_btn_close_normal.png"));
    exitButton->set_X_Y_width_height(EXITBUTTONX, EXITBUTTONY, EXITBUTTONWIDTH, EXITBUTTONHEIGHT);
}
