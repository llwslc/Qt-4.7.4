#include "newaddressdialog.h"
#include "ui_newaddressdialog.h"

newAddressDialog::newAddressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newAddressDialog)
{
    ui->setupUi(this);

    addressidString = QString("0");
    personidString = QString("0");
    picPath = ":/images/avatar.png";
}

newAddressDialog::~newAddressDialog()
{
    delete ui;
}

void newAddressDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/images/bg.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void newAddressDialog::showEvent(QShowEvent *)
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->pushButton_3->setStyleSheet(QString("QPushButton{border-image:url(:/images/avatar.png)0, 0, 0, 0;}"));
}

void newAddressDialog::on_pushButton_clicked()
{
    //添加
    QSqlQuery query;
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

    query.exec("insert into address values('" + QString::number(idNum, 10) + "', '"
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

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->pushButton_3->setStyleSheet(QString("QPushButton{border-image:url(:/images/avatar.png)0, 0, 0, 0;}"));

    QMessageBox::information(NULL, "success", "添加成功!");

    emit newSignal();
}

void newAddressDialog::on_pushButton_2_clicked()
{
    //取消
    this->close();
}

void newAddressDialog::on_pushButton_3_clicked()
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
