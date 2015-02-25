#include "scoredialog.h"
#include "ui_scoredialog.h"

scoreDialog::scoreDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scoreDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    on_pushButton_6_clicked();

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->lineEdit_3->clear();

    initDialog();
}

scoreDialog::~scoreDialog()
{
    delete ui;
}

void scoreDialog::showEvent(QShowEvent *)
{
    on_pushButton_6_clicked();

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->lineEdit_3->clear();

    initDialog();
}

void scoreDialog::on_pushButton_clicked()
{
    //科目查询
    currentTableModel->setFilter("subjucts like '%" + ui->lineEdit->text().trimmed() + "%'");
    currentTableModel->select();
}

void scoreDialog::on_pushButton_2_clicked()
{
    //学号查询
    currentTableModel->setFilter("schid like '%" + ui->lineEdit_2->text().trimmed() + "%'");
    currentTableModel->select();
}

void scoreDialog::on_pushButton_6_clicked()
{
    //刷新
    currentTableModel->setTable("scores");
    currentTableModel->select();
    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->lineEdit_3->clear();
}

void scoreDialog::on_pushButton_3_clicked()
{
    //添加
    QSqlQuery query;
    int idNum = 0;

    query.exec("select scoresid from scores");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    query.exec("insert into scores values('" + QString::number(idNum, 10) + "', '"
               + ui->comboBox->currentText() + "', '"
               + ui->comboBox_2->currentText() + "', '"
               + ui->lineEdit_3->text().trimmed() + "')");

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->lineEdit_3->clear();

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "add success!");
}

void scoreDialog::on_pushButton_4_clicked()
{
    //修改
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();
    query.exec("delete from scores where scoresid = '" + idNum + "'");

    query.exec("insert into scores values('" + idNum + "', '"
               + ui->comboBox->currentText() + "', '"
               + ui->comboBox_2->currentText() + "', '"
               + ui->lineEdit_3->text().trimmed() + "')");

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->lineEdit_3->clear();

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "modefy success!");
}

void scoreDialog::on_pushButton_5_clicked()
{
    //删除
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->lineEdit_3->clear();

    QMessageBox::information(NULL, "success", "delete success!");
}

void scoreDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();

    query.exec("select * from scores where scoresid = '" + idNum + "'");
    while(query.next())
    {
        ui->comboBox->setCurrentIndex(ui->comboBox->findText(query.value(1).toString()));
        ui->comboBox_2->setCurrentIndex(ui->comboBox_2->findText(query.value(2).toString()));
        ui->lineEdit_3->setText(query.value(3).toString());
    }
}

void scoreDialog::initDialog()
{
    //初始化下拉列表
    QSqlQuery query;
    ui->comboBox->clear();
    ui->comboBox_2->clear();

    ui->comboBox->addItem("");
    ui->comboBox_2->addItem("");

    query.exec("select name from subjucts");
    while(query.next())
        ui->comboBox->addItem(query.value(0).toString());

    query.exec("select schid from students");
    while(query.next())
        ui->comboBox_2->addItem(query.value(0).toString());
}
