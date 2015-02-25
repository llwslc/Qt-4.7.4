#include "clotheswindow.h"
#include "ui_clotheswindow.h"

clothesWindow::clothesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clothesWindow)
{
    ui->setupUi(this);
}

clothesWindow::~clothesWindow()
{
    delete ui;
}

void clothesWindow::showEvent(QShowEvent *)
{
    QSqlQuery query;

    this->move(globaWindowsPos);   //调整窗口位置

    if(true == addPressed)
    {
        modifyButton->setButtonPicture(QPixmap(":/images/cloth_add_normal.png"));
        modifyButton->setPressPicture(QPixmap(":/images/cloth_add_pressed.png"));
        modifyButton->setReleasePicture(QPixmap(":/images/cloth_add_normal.png"));

        nameLineEdit->clear();
        if(typePressed != NOBUTTONPRESSED)
            typeComboBox->setCurrentIndex(typePressed);
        else
            typeComboBox->setCurrentIndex(INTNUMBERINIT);
        if(seasonPressed != NOBUTTONPRESSED)
            seasonComboBox->setCurrentIndex(seasonPressed);
        else
            seasonComboBox->setCurrentIndex(INTNUMBERINIT);
        if(classtypePressed != NOBUTTONPRESSED)
            classtypeComboBox->setCurrentIndex(classtypePressed);
        else
            classtypeComboBox->setCurrentIndex(INTNUMBERINIT);
        brandLineEdit->clear();
        priceLineEdit->clear();
        timeDateEdit->setDate(QDate::currentDate());
        storePlaceLineEdit->clear();
        buyPlaceLineEdit->clear();
        noteTextEdit->clear();

        picButton->setButtonPicture(QPixmap(":/images/cloth_pic_normal.png"));
        picButton->setPressPicture(QPixmap(":/images/cloth_pic_pressed.png"));
        picButton->setReleasePicture(QPixmap(":/images/cloth_pic_normal.png"));
    }
    else
    {
        modifyButton->setButtonPicture(QPixmap(":/images/cloth_modify_normal.png"));
        modifyButton->setPressPicture(QPixmap(":/images/cloth_modify_pressed.png"));
        modifyButton->setReleasePicture(QPixmap(":/images/cloth_modify_normal.png"));

        query.exec("select * from clothes where clothesid = '" + QString::number(selectClothesIdNumInt, NUMBERTOSTRINGBASE) + "'");
        while(query.next())
        {
            nameLineEdit->setText(query.value(SQLCLOTHESNAMEINDEX).toString());
            typeComboBox->setCurrentIndex(query.value(SQLCLOTHESTYPEINDEX).toInt());
            seasonComboBox->setCurrentIndex(query.value(SQLCLOTHESSEASONINDEX).toInt());
            classtypeComboBox->setCurrentIndex(query.value(SQLCLOTHESCLASSTYPEINDEX).toInt());
            brandLineEdit->setText(query.value(SQLCLOTHESBRANDINDEX).toString());
            priceLineEdit->setText(query.value(SQLCLOTHESPRICEINDEX).toString());
            timeDateEdit->setDate(QDate::fromString(query.value(SQLCLOTHESTIMEINDEX).toString(), "yyyy.MM.dd"));
            storePlaceLineEdit->setText(query.value(SQLCLOTHESSTOREPLACEINDEX).toString());
            buyPlaceLineEdit->setText(query.value(SQLCLOTHESBUYPLACEINDEX).toString());
            noteTextEdit->setPlainText(query.value(SQLCLOTHESNOTEINDEX).toString());
            clothesPicPathString = query.value(SQLCLOTHESPICPATHINDEX).toString();
        }

        picButton->setButtonPicture(QPixmap(clothesPicPathString).scaled(PICBUTTONWIDTH, PICBUTTONHEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        picButton->setPressPicture(QPixmap(clothesPicPathString).scaled(PICBUTTONWIDTH, PICBUTTONHEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        picButton->setReleasePicture(QPixmap(clothesPicPathString).scaled(PICBUTTONWIDTH, PICBUTTONHEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
}

void clothesWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(BKGPAINTERX, BKGPAINTERY, QPixmap(":/images/cloth_background.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void clothesWindow::mousePressEvent(QMouseEvent *event)
{
    this->windowPos = this->pos();
    this->mousePos = event->globalPos();
    this->dPos = mousePos - windowPos;
}

void clothesWindow::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - this->dPos);
}

void clothesWindow::closeEvent(QCloseEvent *)
{
    globaWindowsPos = this->QWidget::pos(); //获取窗口位置
}

void clothesWindow::picButton_clicked()
{
    //图片按钮
    QString picPath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files(*.jpg)"));
    if(picPath.length() == INTNUMBERINIT)
    {
        //NULL
    }
    else
    {
        clothesPicPathString = picPath;

        picButton->setButtonPicture(QPixmap(clothesPicPathString).scaled(PICBUTTONWIDTH, PICBUTTONHEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        picButton->setPressPicture(QPixmap(clothesPicPathString).scaled(PICBUTTONWIDTH, PICBUTTONHEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        picButton->setReleasePicture(QPixmap(clothesPicPathString).scaled(PICBUTTONWIDTH, PICBUTTONHEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
}

void clothesWindow::modifyButton_clicked()
{
    QSqlQuery query;
    QString targetPath;
    //修改按钮
    if(true == addPressed)
    {
        selectClothesIdNumInt = INTNUMBERINIT;
        query.exec("select clothesid from clothes");
        while(query.next())
        {
            if(selectClothesIdNumInt < query.value(SQLCLOTHESIDNUMINDEX).toInt())
                selectClothesIdNumInt = query.value(SQLCLOTHESIDNUMINDEX).toInt();
        }
        selectClothesIdNumInt++;

        targetPath = "clothes/" + QString::number(selectClothesIdNumInt, NUMBERTOSTRINGBASE) + ".jpg";
        copyFileToPath(clothesPicPathString, targetPath, true); //覆盖式复制

        query.exec("insert into clothes values ('" + QString::number(selectClothesIdNumInt, NUMBERTOSTRINGBASE) //插入数据库
                   + "', '" + nameLineEdit->text()
                   + "', '" + QString::number(typeComboBox->currentIndex(), NUMBERTOSTRINGBASE)
                   + "', '" + QString::number(seasonComboBox->currentIndex(), NUMBERTOSTRINGBASE)
                   + "', '" + QString::number(classtypeComboBox->currentIndex(), NUMBERTOSTRINGBASE)
                   + "', '" + brandLineEdit->text()
                   + "', '" + priceLineEdit->text()
                   + "', '" + timeDateEdit->date().toString("yyyy.MM.dd")
                   + "', '" + storePlaceLineEdit->text()
                   + "', '" + buyPlaceLineEdit->text()
                   + "', '" + noteTextEdit->toPlainText()
                   + "', '" + targetPath
                   + "')");
    }
    else
    {
        query.exec("delete from clothes where clothesid = '" + QString::number(selectClothesIdNumInt, NUMBERTOSTRINGBASE) + "'");

        targetPath = "clothes/" + QString::number(selectClothesIdNumInt, NUMBERTOSTRINGBASE) + ".jpg";
        copyFileToPath(clothesPicPathString, targetPath, true); //覆盖式复制

        query.exec("insert into clothes values ('" + QString::number(selectClothesIdNumInt, NUMBERTOSTRINGBASE) //插入数据库
                   + "', '" + nameLineEdit->text()
                   + "', '" + QString::number(typeComboBox->currentIndex(), NUMBERTOSTRINGBASE)
                   + "', '" + QString::number(seasonComboBox->currentIndex(), NUMBERTOSTRINGBASE)
                   + "', '" + QString::number(classtypeComboBox->currentIndex(), NUMBERTOSTRINGBASE)
                   + "', '" + brandLineEdit->text()
                   + "', '" + priceLineEdit->text()
                   + "', '" + timeDateEdit->date().toString("yyyy.MM.dd")
                   + "', '" + storePlaceLineEdit->text()
                   + "', '" + buyPlaceLineEdit->text()
                   + "', '" + noteTextEdit->toPlainText()
                   + "', '" + targetPath
                   + "')");
    }

    emit modifyClothes();
}

void clothesWindow::cancelButton_clicked()
{
    //取消按钮
    this->close();
}
