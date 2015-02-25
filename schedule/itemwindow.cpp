#include "itemwindow.h"
#include "ui_itemwindow.h"

itemWindow::itemWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::itemWindow)
{
    ui->setupUi(this);

    if(false == itemDelButtonFlag)
    {
        ui->pushButton_7->hide(); //删除按钮隐藏
        ui->pushButton_8->hide(); //保存按钮隐藏

        ui->lineEdit->clear();
        ui->dateEdit->setDateTime(QDateTime::currentDateTime()); //设置为当前时间
        ui->comboBox->setCurrentIndex(0);
        ui->comboBox_2->setCurrentIndex(0);
        ui->textEdit->clear();
    }
    else
    {
        ui->pushButton_6->hide(); //新增按钮隐藏
        fillTable();
    }
}

itemWindow::~itemWindow()
{
    delete ui;
}

void itemWindow::on_pushButton_5_clicked()
{
    //返回
    this->close();
}

void itemWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/png/bk.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void itemWindow::on_pushButton_6_clicked()
{
    //新增
    QString titleStr; //标题
    QString dateStr;  //日期
    int sortInt;      //分类
    int dittoInt;     //重复
    QString remarkStr;//备注

    titleStr = ui->lineEdit->text().trimmed();
    qDebug() << titleStr << endl;
    dateStr = ui->dateEdit->dateTime().toString("yyyy.MM.dd");
    qDebug() << dateStr << endl;
    sortInt = ui->comboBox->currentIndex();
    qDebug() << sortInt << endl;
    dittoInt = ui->comboBox_2->currentIndex();
    qDebug() << dittoInt << endl;
    remarkStr = ui->textEdit->toPlainText();
    qDebug() << remarkStr << endl;

    QString sql;
    QSqlQuery query;
    int idNum = 0;

    //根据标题,判断是否重复
    sql = "select noteid from note where title = '" + titleStr + "'";
    query.exec(sql);
    if (query.next())
    {
        //标题重复
        QMessageBox::warning(this,tr("Warning"),tr("Title already exists!"),QMessageBox::Yes);
    }
    else
    {

        //获取主键大小
        sql = "select noteid from note";
        query.exec(sql);
        while(query.next())
        {
            if(idNum < query.value(0).toInt())
                idNum = query.value(0).toInt();
        }

        idNum++;

        sql = "insert into note values ('" + QString::number(idNum, 10)
                + "', '" + titleStr + "', '" + dateStr + "', '"
                + QString::number(sortInt, 10) + "', '" + QString::number(dittoInt, 10) + "', '" + remarkStr + "')";

        query.exec(sql);

        //插入倒数日表格
        idNum = 0;
        int dayResult = 0;
        //获取主键大小
        sql = "select dayid from day";
        query.exec(sql);
        while(query.next())
        {
            if(idNum < query.value(0).toInt())
                idNum = query.value(0).toInt();
        }

        idNum++;
        dayResult = datedef(dateStr, dittoInt);
        qDebug() << "剩余天数:" << dayResult << endl;

        sql = "insert into day values ('" + QString::number(idNum, 10)
                + "', '" + titleStr + "', '" + QString::number(dayResult, 10) + "', '"
                + QString::number(sortInt, 10) + "')";
        query.exec(sql);

        this->close();
    }
}

void itemWindow::on_pushButton_7_clicked()
{
    //根据标题删除
    QString sql;
    QSqlQuery query;

    sql = "delete from note where title = '" + ui->lineEdit->text().trimmed() + "'";
    query.exec(sql);

    sql = "delete from day where title = '" + ui->lineEdit->text().trimmed() + "'";
    query.exec(sql);

    this->close();
}

void itemWindow::on_pushButton_8_clicked()
{
    //保存
    QString titleStr; //标题
    QString dateStr;  //日期
    int sortInt;      //分类
    int dittoInt;     //重复
    QString remarkStr;//备注

    titleStr = ui->lineEdit->text().trimmed();
    dateStr = ui->dateEdit->dateTime().toString("yyyy.MM.dd");
    sortInt = ui->comboBox->currentIndex();
    dittoInt = ui->comboBox_2->currentIndex();
    remarkStr = ui->textEdit->toPlainText();

    QString sql;
    QSqlQuery query;

    //删掉原来的记录
    sql = "delete from note where noteid = '" + QString::number(noteid, 10) + "'";
    query.exec(sql);
    sql = "delete from day where dayid = '" + QString::number(dayid, 10) + "'";
    query.exec(sql);

    //插入新的修改数据
    sql = "insert into note values ('" + QString::number(noteid, 10)
            + "', '" + titleStr + "', '" + dateStr + "', '"
            + QString::number(sortInt, 10) + "', '" + QString::number(dittoInt, 10) + "', '" + remarkStr + "')";

    query.exec(sql);

    int dayResult = 0;
    dayResult = datedef(dateStr, dittoInt);
    sql = "insert into day values ('" + QString::number(dayid, 10)
            + "', '" + titleStr + "', '" + QString::number(dayResult, 10) + "', '"
            + QString::number(sortInt, 10) + "')";
    query.exec(sql);

    this->close();
}

void itemWindow::fillTable()
{
    //填充信息
    QString sql;
    QSqlQuery query;

    dayid = 0;
    noteid = 0;

    //获取主键大小
    qDebug() << viewTitle << endl;

    sql = "select dayid from day where title = '" + viewTitle + "'";
    query.exec(sql);
    while (query.next())
    {
        dayid = query.value(0).toInt();
    }
    qDebug() << dayid << endl;

    sql = "select noteid from note where title = '" + viewTitle + "'";
    query.exec(sql);
    while (query.next())
    {
        noteid = query.value(0).toInt();
    }
    qDebug() << noteid << endl;

    sql = "select * from note where noteid = '" + QString::number(noteid, 10) + "'";
    query.exec(sql);

    while (query.next())
    {
        ui->lineEdit->setText(query.value(1).toString());
        ui->dateEdit->setDateTime(QDateTime::fromString(query.value(2).toString(), "yyyy.MM.dd"));
        ui->comboBox->setCurrentIndex(query.value(3).toInt());
        ui->comboBox_2->setCurrentIndex(query.value(4).toInt());
        ui->textEdit->setText(query.value(5).toString());
    }
}

void itemWindow::closeEvent(QCloseEvent *e)
{
    //窗口关闭消息
    windowsPos = this->QWidget::pos(); //获取窗口位置
}
