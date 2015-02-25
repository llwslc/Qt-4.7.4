#include "studialog.h"
#include "ui_studialog.h"

stuDialog::stuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stuDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    on_pushButton_5_clicked();

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
}

stuDialog::~stuDialog()
{
    delete ui;
}

void stuDialog::showEvent(QShowEvent *)
{
    currentTableModel->setTable("students");
    currentTableModel->select();
    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
}

//拷贝文件
bool stuDialog::copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist)
{
    toDir.replace("\\","/");
    if (sourceDir == toDir){
        return true;
    }
    if (!QFile::exists(sourceDir)){
        return false;
    }
    QDir *createfile = new QDir;
    bool exist = createfile->exists(toDir);
    if (exist){
        if(coverFileIfExist){
            createfile->remove(toDir);
        }
    }//end if

    if(!QFile::copy(sourceDir, toDir))
    {
        return false;
    }
    return true;
}

void stuDialog::on_pushButton_6_clicked()
{
    //姓名搜索
    currentTableModel->setFilter("name like '%" + ui->lineEdit->text().trimmed() + "%'");
    currentTableModel->select();
}

void stuDialog::on_pushButton_7_clicked()
{
    //身份证搜索
    currentTableModel->setFilter("idcard = '" + ui->lineEdit_2->text().trimmed() + "'");
    currentTableModel->select();
}

void stuDialog::on_pushButton_8_clicked()
{
    //专业搜索
    currentTableModel->setFilter("spec like '%" + ui->lineEdit_3->text().trimmed() + "%'");
    currentTableModel->select();
}

void stuDialog::on_pushButton_9_clicked()
{
    //班级搜索
    currentTableModel->setFilter("classid like '%" + ui->lineEdit_4->text().trimmed() + "%'");
    currentTableModel->select();
}

void stuDialog::on_pushButton_10_clicked()
{
    //学号搜索
    currentTableModel->setFilter("schid like '%" + ui->lineEdit_5->text().trimmed() + "%'");
    currentTableModel->select();
}

void stuDialog::on_pushButton_clicked()
{
    //添加头像
    picPath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg)"));
    if(picPath.length() == 0)
    {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
        return;
    }
    else
    {
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + picPath);
    }

    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(picPath));
}

void stuDialog::on_pushButton_2_clicked()
{
    //添加
    QSqlQuery query;
    int idNum = 0;

    query.exec("select studentsid from students");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    QString targetPath = "student/" + QString::number(idNum, 10) + ".jpg";
    copyFileToPath(picPath, targetPath, true); //覆盖式复制

    query.exec("insert into students values('" + QString::number(idNum, 10) + "', '"
               + ui->lineEdit->text().trimmed() + "', '"
               + ui->lineEdit_2->text().trimmed() + "', '"
               + ui->lineEdit_3->text().trimmed() + "', '"
               + ui->lineEdit_4->text().trimmed() + "', '"
               + ui->lineEdit_5->text().trimmed() + "', '"
               + targetPath + "')");

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "add success!");

    emit modifyStu();
}

void stuDialog::on_pushButton_3_clicked()
{
    //修改
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();
    query.exec("delete from students where studentsid = '" + idNum + "'");

    QString targetPath = "student/" + idNum + ".jpg";
    copyFileToPath(picPath, targetPath, true); //覆盖式复制

    query.exec("insert into students values('" + idNum + "', '"
               + ui->lineEdit->text().trimmed() + "', '"
               + ui->lineEdit_2->text().trimmed() + "', '"
               + ui->lineEdit_3->text().trimmed() + "', '"
               + ui->lineEdit_4->text().trimmed() + "', '"
               + ui->lineEdit_5->text().trimmed() + "', '"
               + targetPath + "')");

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "modefy success!");

    emit modifyStu();
}

void stuDialog::on_pushButton_4_clicked()
{
    //删除
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();

    QMessageBox::information(NULL, "success", "delete success!");

    emit modifyStu();
}

void stuDialog::on_pushButton_5_clicked()
{
    //刷新
    currentTableModel->setTable("students");
    currentTableModel->select();
    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
}

void stuDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();

    query.exec("select * from students where studentsid = '" + idNum + "'");
    while(query.next())
    {
        ui->lineEdit->setText(query.value(1).toString());
        ui->lineEdit_2->setText(query.value(2).toString());
        ui->lineEdit_3->setText(query.value(3).toString());
        ui->lineEdit_4->setText(query.value(4).toString());
        ui->lineEdit_5->setText(query.value(5).toString());
        ui->label->setScaledContents(true);
        ui->label->setPixmap(QPixmap(query.value(6).toString()));
    }
}
