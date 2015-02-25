#include "gamedialog.h"
#include "ui_gamedialog.h"

gameDialog::gameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gameDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    on_pushButton_4_clicked();

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->dateEdit->setDate(QDate::currentDate());
}

gameDialog::~gameDialog()
{
    delete ui;
}

void gameDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/jpg/3.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void gameDialog::on_pushButton_clicked()
{
    //添加
    QSqlQuery query;
    int idNum = 0;

    query.exec("select gameid from game");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    query.exec("insert into game values('" + QString::number(idNum, 10) + "', '"
               + ui->lineEdit->text().trimmed() + "', '"
               + ui->dateEdit->date().toString("yyyy.MM.dd") + "', '"
               + ui->lineEdit_2->text().trimmed() + "', '"
               + ui->lineEdit_3->text().trimmed() + "', '"
               + ui->lineEdit_4->text().trimmed() + "')");

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->dateEdit->setDate(QDate::currentDate());

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "add success!");

    emit addGame();
}

void gameDialog::on_pushButton_2_clicked()
{
    //修改
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();
    query.exec("delete from game where gameid = '" + idNum + "'");

    query.exec("insert into game values('" + idNum + "', '"
               + ui->lineEdit->text().trimmed() + "', '"
               + ui->dateEdit->date().toString("yyyy.MM.dd") + "', '"
               + ui->lineEdit_2->text().trimmed() + "', '"
               + ui->lineEdit_3->text().trimmed() + "', '"
               + ui->lineEdit_4->text().trimmed() + "')");

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->dateEdit->setDate(QDate::currentDate());

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "modefy success!");

    emit addGame();
}

void gameDialog::on_pushButton_3_clicked()
{
    //删除
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->dateEdit->setDate(QDate::currentDate());

    QMessageBox::information(NULL, "success", "delete success!");

    emit addGame();
}

void gameDialog::on_pushButton_4_clicked()
{
    //刷新
    currentTableModel->setTable("game");
    currentTableModel->select();

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("编号"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("项目"));
    currentTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("日期"));
    currentTableModel->setHeaderData(3, Qt::Horizontal, QObject::tr("地点"));
    currentTableModel->setHeaderData(4, Qt::Horizontal, QObject::tr("人数"));
    currentTableModel->setHeaderData(5, Qt::Horizontal, QObject::tr("预计支出"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void gameDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();

    query.exec("select * from game where gameid = '" + idNum + "'");
    while(query.next())
    {
        ui->lineEdit->setText(query.value(1).toString());
        ui->dateEdit->setDate(QDate::fromString(query.value(2).toString(), "yyyy.MM.dd"));
        ui->lineEdit_2->setText(query.value(3).toString());
        ui->lineEdit_3->setText(query.value(4).toString());
        ui->lineEdit_4->setText(query.value(5).toString());
    }
}
