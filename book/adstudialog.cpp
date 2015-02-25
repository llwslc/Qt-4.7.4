#include "adstudialog.h"
#include "ui_adstudialog.h"

adStuDialog::adStuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adStuDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    currentTableModel->setTable("students");
    currentTableModel->setSort(0, Qt::AscendingOrder);
    currentTableModel->select();

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("编号"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("姓名"));
    currentTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("密码"));
    currentTableModel->setHeaderData(3, Qt::Horizontal, QObject::tr("证件编号"));
    currentTableModel->setHeaderData(4, Qt::Horizontal, QObject::tr("联系方式"));
    currentTableModel->setHeaderData(5, Qt::Horizontal, QObject::tr("状态"));
    currentTableModel->setHeaderData(6, Qt::Horizontal, QObject::tr("照片"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->comboBox->setCurrentIndex(0);

    connect(&adModifyStuw, SIGNAL(modifyStu()), this, SLOT(updateStuTable()));
}

adStuDialog::~adStuDialog()
{
    delete ui;
}

void adStuDialog::showEvent(QShowEvent *)
{
    //显示窗体
    currentTableModel->setTable("students");
    currentTableModel->setSort(0, Qt::AscendingOrder);
    currentTableModel->select();

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("编号"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("姓名"));
    currentTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("密码"));
    currentTableModel->setHeaderData(3, Qt::Horizontal, QObject::tr("证件编号"));
    currentTableModel->setHeaderData(4, Qt::Horizontal, QObject::tr("联系方式"));
    currentTableModel->setHeaderData(5, Qt::Horizontal, QObject::tr("状态"));
    currentTableModel->setHeaderData(6, Qt::Horizontal, QObject::tr("照片"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->comboBox->setCurrentIndex(0);
}

void adStuDialog::on_pushButton_4_clicked()
{
    //头像
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

void adStuDialog::on_pushButton_clicked()
{
    //创建借阅证
    QSqlQuery query;
    int idNum = 0;

    if(ui->lineEdit->text().trimmed().length() == 0)
    {
        QMessageBox::information(NULL, "Warring", "添加失败!姓名不能为空.");
        return;
    }

    if(ui->lineEdit_3->text().trimmed().length() == 0)
    {
        QMessageBox::information(NULL, "Warring", "添加失败!证件编号不能为空.");
        return;
    }

    if(ui->lineEdit_4->text().trimmed().length() == 0)
    {
        QMessageBox::information(NULL, "Warring", "添加失败!联系方式不能为空.");
        return;
    }

    query.exec("select studentsid,stucode,phone from students");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
        if(query.value(1).toString() == ui->lineEdit_3->text().trimmed())
        {
            QMessageBox::information(NULL, "Warring", "添加失败!证件编号重复.");
            return;
        }
        if(query.value(2).toString() == ui->lineEdit_4->text().trimmed())
        {
            QMessageBox::information(NULL, "Warring", "添加失败!手机号码重复.");
            return;
        }
    }

    idNum++;

    QString targetPath = "user/" + QString::number(idNum, 10) + ".jpg";
    copyFileToPath(picPath, targetPath, true); //覆盖式复制

    query.exec("insert into students values('" + QString::number(idNum, 10) + "', '"
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

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "添加成功!");

    emit addStu();
}

void adStuDialog::on_pushButton_2_clicked()
{
    //注销借阅证
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();

    query.exec("update students set status = 1" + QString(" where studentsid = '") + idNum + "'");

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->comboBox->setCurrentIndex(0);

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "注销成功!");

    emit addStu();
}

void adStuDialog::on_pushButton_3_clicked()
{
    //修改借阅证
#if 0
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();

    query.exec("delete from students where studentsid = '" + idNum + "'");

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

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "修改成功!");
#endif
    adModifyStuw.show();

    emit addStu();
}

void adStuDialog::on_tableView_clicked(const QModelIndex &index)
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
        ui->comboBox->setCurrentIndex(query.value(5).toInt());
        ui->label->setScaledContents(true);
        ui->label->setPixmap(QPixmap(query.value(6).toString()));
    }
}

void adStuDialog::updateStuTable()
{
    //刷新
    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    currentTableModel->setTable("students");
    currentTableModel->setSort(0, Qt::AscendingOrder);
    currentTableModel->select();

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("编号"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("姓名"));
    currentTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("密码"));
    currentTableModel->setHeaderData(3, Qt::Horizontal, QObject::tr("证件编号"));
    currentTableModel->setHeaderData(4, Qt::Horizontal, QObject::tr("联系方式"));
    currentTableModel->setHeaderData(5, Qt::Horizontal, QObject::tr("状态"));
    currentTableModel->setHeaderData(6, Qt::Horizontal, QObject::tr("照片"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->comboBox->setCurrentIndex(0);
}
