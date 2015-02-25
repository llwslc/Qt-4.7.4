#include "admodifystudialog.h"
#include "ui_admodifystudialog.h"

adModifyStuDialog::adModifyStuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adModifyStuDialog)
{
    ui->setupUi(this);

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->comboBox->setCurrentIndex(0);
}

adModifyStuDialog::~adModifyStuDialog()
{
    delete ui;
}

void adModifyStuDialog::showEvent(QShowEvent *)
{
    //显示窗体
    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->comboBox->setCurrentIndex(0);
}

void adModifyStuDialog::on_pushButton_clicked()
{
    //搜索
    QSqlQuery query;

    query.exec("select * from students where phone = '" + ui->lineEdit_5->text().trimmed() + "'");
    while(query.next())
    {
        ui->lineEdit->setText(query.value(1).toString());
        ui->lineEdit_2->setText(query.value(2).toString());
        ui->lineEdit_3->setText(query.value(3).toString());
        ui->lineEdit_4->setText(query.value(4).toString());
        ui->comboBox->setCurrentIndex(query.value(5).toInt());
        picPath = query.value(6).toString();
        ui->label->setScaledContents(true);
        ui->label->setPixmap(QPixmap(picPath));

        return;
    }

    QMessageBox::information(NULL, "Warring", "手机号码未找到!");
}

void adModifyStuDialog::on_pushButton_2_clicked()
{
    //修改信息
    QSqlQuery query;
    QString idNum;

    if(ui->lineEdit->text().trimmed().length() == 0)
    {
        QMessageBox::information(NULL, "Warring", "修改失败!姓名不能为空.");
        return;
    }

    if(ui->lineEdit_4->text().trimmed().length() == 0)
    {
        QMessageBox::information(NULL, "Warring", "修改失败!联系方式不能为空.");
        return;
    }

    query.exec("select phone from students where stucode <> '" + ui->lineEdit_3->text().trimmed() + "'");
    while(query.next())
    {
        if(query.value(0).toString() == ui->lineEdit_4->text().trimmed())
        {
            QMessageBox::information(NULL, "Warring", "修改失败!手机号码重复.");
            return;
        }
    }

    query.exec("select studentsid from students where stucode = '" + ui->lineEdit_3->text().trimmed() + "'");
    while(query.next())
    {
        idNum = query.value(0).toString();
    }

    query.exec("delete from students where stucode = '" + ui->lineEdit_3->text().trimmed() + "'");

    QString targetPath = "user/" + idNum + ".jpg";
    copyFileToPath(picPath, targetPath, true); //覆盖式复制

    query.exec("insert into students values('" + idNum + "', '"
               + ui->lineEdit->text().trimmed() + "', '"
               + ui->lineEdit_2->text().trimmed() + "', '"
               + ui->lineEdit_3->text().trimmed() + "', '"
               + ui->lineEdit_4->text().trimmed() + "', '"
               + QString::number(ui->comboBox->currentIndex(), 10) + "', '"
               + targetPath + "')");


    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->comboBox->setCurrentIndex(0);

    QMessageBox::information(NULL, "success", "修改成功!");

    emit modifyStu();
}

void adModifyStuDialog::on_pushButton_3_clicked()
{
    //学生照片
    picPath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg)"));
    if(picPath.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
        return;
    } else {
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + picPath);
    }
    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(picPath));
}
