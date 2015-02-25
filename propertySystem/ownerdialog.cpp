#include "ownerdialog.h"
#include "ui_ownerdialog.h"

ownerDialog::ownerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ownerDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    currentTableModel->setTable("ownerinfo");
    currentTableModel->select();
    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
}

ownerDialog::~ownerDialog()
{
    delete ui;
}

void ownerDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/jpg/3.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void ownerDialog::on_pushButton_clicked()
{
    //添加
    QSqlQuery query;
    int idNum = 0;
    QString name = ui->lineEdit->text().trimmed();
    bool nameFlag = false;

    query.exec("select ownerinfoid from ownerinfo");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    query.exec("select name from ownerinfo");
    while(query.next())
    {
        if(name == query.value(0).toString())
        {
            QMessageBox::information(NULL, "fail", "name repeat!");
            nameFlag = true;
            break;
        }
    }

    if(nameFlag == false)
    {
        query.exec("insert into ownerinfo values('"
                   + QString::number(idNum, 10) + "', '"
                   + ui->lineEdit->text().trimmed() + "', '"
                   + ui->lineEdit_2->text().trimmed() + "', '"
                   + ui->lineEdit_3->text().trimmed() + "', '"
                   + ui->lineEdit_4->text().trimmed() + "', '"
                   + ui->lineEdit_5->text().trimmed() + "', '"
                   + ui->lineEdit_6->text().trimmed() + "', '"
                   + ui->lineEdit_7->text().trimmed() + "')");

        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();

        currentTableModel->select();
        QMessageBox::information(NULL, "success", "user add success!");
    }
}

void ownerDialog::on_pushButton_2_clicked()
{
    //修改
    QSqlQuery query;
    QString name = ui->lineEdit->text().trimmed();
    bool nameFlag = false;
    QString namePre;

    query.exec("select name from ownerinfo");
    while(query.next())
    {
        if(name == query.value(0).toString())
        {
            QMessageBox::information(NULL, "fail", "name repeat!");
            nameFlag = true;
            break;
        }
        namePre = query.value(0).toString();
    }

    if(nameFlag == false)
    {
        int curRow = currentView->currentIndex().row(); //获取选中的行
        currentTableModel->removeRow(curRow); //删除该行

        query.exec("insert into ownerinfo values('"
                   + selectid + "', '"
                   + ui->lineEdit->text().trimmed() + "', '"
                   + ui->lineEdit_2->text().trimmed() + "', '"
                   + ui->lineEdit_3->text().trimmed() + "', '"
                   + ui->lineEdit_4->text().trimmed() + "', '"
                   + ui->lineEdit_5->text().trimmed() + "', '"
                   + ui->lineEdit_6->text().trimmed() + "', '"
                   + ui->lineEdit_7->text().trimmed() + "')");

        query.exec("update waterchanges set name = '" + ui->lineEdit->text().trimmed() + "' where name = '" + namePre + "'");
        query.exec("update electricitychanges set name = '" + ui->lineEdit->text().trimmed() + "' where name = '" + namePre + "'");
        query.exec("update gaschanges set name = '" + ui->lineEdit->text().trimmed() + "' where name = '" + namePre + "'");

        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();

        currentTableModel->select();
        QMessageBox::information(NULL, "success", "user modify success!");
    }
}

void ownerDialog::on_pushButton_3_clicked()
{
    //删除
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
}

void ownerDialog::on_pushButton_5_clicked()
{
    //刷新
    currentTableModel->setTable("ownerinfo");
    currentTableModel->select();
    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
}

void ownerDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    int curRow = currentView->currentIndex().row(); //获取选中的行

    selectid = currentTableModel->index(curRow, 0).data().toString();
    ui->lineEdit->setText(currentTableModel->index(curRow, 1).data().toString());
    ui->lineEdit_2->setText(currentTableModel->index(curRow, 2).data().toString());
    ui->lineEdit_3->setText(currentTableModel->index(curRow, 3).data().toString());
    ui->lineEdit_4->setText(currentTableModel->index(curRow, 4).data().toString());
    ui->lineEdit_5->setText(currentTableModel->index(curRow, 5).data().toString());
    ui->lineEdit_6->setText(currentTableModel->index(curRow, 6).data().toString());
    ui->lineEdit_7->setText(currentTableModel->index(curRow, 7).data().toString());
}
