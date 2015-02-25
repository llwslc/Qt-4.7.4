#include "modaddressdialog.h"
#include "ui_modaddressdialog.h"

modAddressDialog::modAddressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modAddressDialog)
{
    ui->setupUi(this);

    addressidString = QString("0");
    personidString = QString("0");

    picPath = ":/images/avatar.png";
}

modAddressDialog::~modAddressDialog()
{
    delete ui;
}

void modAddressDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/images/bg.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void modAddressDialog::showEvent(QShowEvent *)
{
    QSqlQuery query;
    query.exec("select * from address where addressid = '" + addressidString + "'");
    while(query.next())
    {
        personidString = query.value(1).toString();
        picPath = query.value(2).toString();
        ui->lineEdit->setText(query.value(3).toString());
        ui->lineEdit_2->setText(query.value(4).toString());
        ui->lineEdit_3->setText(query.value(5).toString());
        ui->comboBox->setCurrentIndex(query.value(6).toInt());
        ui->dateEdit->setDate(QDate::fromString(query.value(7).toString(), "yyyy.MM.dd"));
        ui->lineEdit_4->setText(query.value(8).toString());
        ui->lineEdit_5->setText(query.value(9).toString());
        ui->lineEdit_6->setText(query.value(10).toString());
        if(picPath == "")
        {
            ui->pushButton_3->setStyleSheet(QString("QPushButton{border-image:url(:/images/avatar.png)0, 0, 0, 0;}"));
        }
        else
        {
            ui->pushButton_3->setStyleSheet(QString("QPushButton{border-image:url(" + picPath + ");}"));
        }
    }
}

void modAddressDialog::on_pushButton_clicked()
{
    //修改
    QSqlQuery query;
    query.exec("delete from address where addressid = '" + addressidString + "'");
    int idNum = 0;
    query.exec("select addressid from address");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }
    idNum++;

    QString targetPath;
    if(picPath == ":/images/avatar.png")
    {
        targetPath = picPath;
    }
    else
    {
        targetPath = "user/" + QString::number(idNum) + ".jpg";
        copyFileToPath(picPath, targetPath, true); //覆盖式复制
    }

    query.exec("insert into address values('" + addressidString + "', '"
               + personidString + "', '"
               + targetPath + "', '"
               + ui->lineEdit->text().trimmed() + "', '"
               + ui->lineEdit_2->text().trimmed() + "', '"
               + ui->lineEdit_3->text().trimmed() + "', '"
               + QString::number(ui->comboBox->currentIndex(), 10) + "', '"
               + ui->dateEdit->date().toString("yyyy.MM.dd") + "', '"
               + ui->lineEdit_4->text().trimmed() + "', '"
               + ui->lineEdit_5->text().trimmed() + "', '"
               + ui->lineEdit_6->text().trimmed() + "')");

    QMessageBox::information(NULL, "success", "修改成功!");

    emit modSignal();
}

void modAddressDialog::on_pushButton_2_clicked()
{
    //取消
    this->close();
}

void modAddressDialog::on_pushButton_3_clicked()
{
    //头像
    picPath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg)"));
    if(picPath.length() == 0) {
        picPath = ":/images/avatar.png";
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
        return;
    } else {
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + picPath);
    }

    ui->pushButton_3->setStyleSheet(QString("QPushButton{border-image:url(" + picPath + ");}"));
}
