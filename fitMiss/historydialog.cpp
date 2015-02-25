#include "historydialog.h"
#include "ui_historydialog.h"

historyDialog::historyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::historyDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);

    currentView = ui->tableView;

    ui->dateEdit->setDate(QDate::currentDate());
}

historyDialog::~historyDialog()
{
    delete ui;
}

void historyDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/png/bj51.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
void historyDialog::on_pushButton_clicked()
{
    //查询
    QString weightStr;
    int intakeInt = 0;
    int sportInt = 0;
    QString sql;
    QSqlQuery query;

    sql = "select weight from weightrecord where date = '" + ui->dateEdit->date().toString("dd.MM.yyyy") + "'";
    query.exec(sql);
    while(query.next())
    {
        weightStr = query.value(0).toString();
    }
    ui->label->setText("体重 : " + weightStr + " KG");

    sql = "select calories, calvariable, category from calrecord where date = '" + ui->dateEdit->date().toString("dd.MM.yyyy") + "'";
    query.exec(sql);
    while(query.next())
    {
        if(query.value(2).toInt() == 2)
        {
            //sports
            sportInt += query.value(0).toInt()*query.value(1).toInt();
        }
        else
        {
            intakeInt += query.value(0).toInt()*query.value(1).toInt()/100;
        }
    }

    ui->label_2->setText("摄入 : " + QString::number(intakeInt, 10) + " 千卡");
    ui->label_3->setText("运动 : " + QString::number(sportInt, 10) + " 千卡");

    currentTableModel->setTable("calrecord");
    currentTableModel->setFilter("date = '" + ui->dateEdit->date().toString("dd.MM.yyyy") + "'");
    currentTableModel->removeColumn(0);

    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
}
