#include "optionswindow.h"
#include "ui_optionswindow.h"

optionsWindow::optionsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::optionsWindow)
{
    ui->setupUi(this);

    int ruleInt;
    QString sql;
    QSqlQuery query;

    sql = "select rule from orderoption where orderoptionid = '1'";
    query.exec(sql);
    while(query.next())
    {
        ruleInt = query.value(0).toInt();
    }

    ui->comboBox->setCurrentIndex(ruleInt);
}

optionsWindow::~optionsWindow()
{
    delete ui;
}

void optionsWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/png/bk.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void optionsWindow::on_pushButton_clicked()
{
    //返回
    this->close();
}

void optionsWindow::on_pushButton_2_clicked()
{
    //保存
    int ruleInt;
    QString sql;
    QSqlQuery query;

    ruleInt = ui->comboBox->currentIndex();

    sql = "update orderoption set rule = '" + QString::number(ruleInt, 10) + "' where orderoptionid = '1'";
    query.exec(sql);

    this->close();
}

void optionsWindow::on_pushButton_3_clicked()
{
    //备份
    QString dateStr = QDateTime::currentDateTime().toString("hh.mm.ss.dd-MM-yyyy");
    QString backupPath = QString("dataBackup/") + dateStr + ".db";

    copyFileToPath("daysMatter.db", backupPath, true);

    QMessageBox::information(NULL, tr("Path"), tr("database backup path is ") + backupPath);
}

void optionsWindow::on_pushButton_4_clicked()
{
    //导入
    QString sourcePath;
    sourcePath = QFileDialog::getOpenFileName(this, tr("Open database"), "dataBackup", tr("database Files(*.db)"));
    if(sourcePath.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    } else {
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + sourcePath);
    }

    copyFileToPath(sourcePath, "backup.db", true);

    QMessageBox::information(NULL, tr("Restart"), tr("datebase will change when you restart this program!"));
}

void optionsWindow::closeEvent(QCloseEvent *e)
{
    //窗口关闭消息
    windowsPos = this->QWidget::pos(); //获取窗口位置
}
