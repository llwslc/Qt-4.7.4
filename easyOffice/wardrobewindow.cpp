#include "wardrobewindow.h"
#include "ui_wardrobewindow.h"

wardrobeWindow::wardrobeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wardrobeWindow)
{
    ui->setupUi(this);

    clothesSelect = true;

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    currentTableModel->setTable("clothes");
    currentTableModel->setSort(0, Qt::AscendingOrder);
    currentTableModel->select(); //选取整个表的所有行
    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox_3->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->textEdit->clear();

    on_pushButton_clicked();
}

wardrobeWindow::~wardrobeWindow()
{
    delete ui;
}

void wardrobeWindow::on_pushButton_clicked()
{
    //我的衣柜
    clothesSelect = true;
    tableWidgetData();
    currentTableModel->setTable("clothes");
    currentTableModel->setSort(0, Qt::AscendingOrder);
    currentTableModel->select();

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox_3->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->textEdit->clear();
}

void wardrobeWindow::on_pushButton_2_clicked()
{
    //我的搭配
    clothesSelect = false;
    tableWidgetData();
    currentTableModel->setTable("clothes");
    currentTableModel->setSort(0, Qt::AscendingOrder);
    currentTableModel->select();

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox_3->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->textEdit->clear();
}

void wardrobeWindow::on_pushButton_3_clicked()
{
    //每日搭配
    //matchDlg.show();
}

void wardrobeWindow::on_pushButton_4_clicked()
{
    //添加衣物
    int rowNum = currentTableModel->rowCount(); //获得表的行数
    int idNum = 0;
    QSqlQuery query;
    query.exec("select clothesid from clothes");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    QString targetPath = "supplies/" + QString::number(idNum, 10) + ".jpg";
    copyFileToPath(picPath, targetPath, true); //覆盖式复制

    currentTableModel->insertRow(rowNum); //添加一行
    currentTableModel->setData(currentTableModel->index(rowNum, 0), idNum);
    currentTableModel->setData(currentTableModel->index(rowNum, 1), ui->lineEdit->text());
    currentTableModel->setData(currentTableModel->index(rowNum, 2), ui->comboBox->currentIndex());
    currentTableModel->setData(currentTableModel->index(rowNum, 3), ui->comboBox_2->currentIndex());
    currentTableModel->setData(currentTableModel->index(rowNum, 4), ui->comboBox_3->currentIndex());
    currentTableModel->setData(currentTableModel->index(rowNum, 5), ui->lineEdit_2->text());
    currentTableModel->setData(currentTableModel->index(rowNum, 6), ui->lineEdit_3->text());
    currentTableModel->setData(currentTableModel->index(rowNum, 7), ui->dateEdit->date().toString("yyyy.MM.dd"));
    currentTableModel->setData(currentTableModel->index(rowNum, 8), ui->lineEdit_4->text());
    currentTableModel->setData(currentTableModel->index(rowNum, 9), ui->lineEdit_5->text());
    currentTableModel->setData(currentTableModel->index(rowNum, 10), ui->textEdit->toPlainText());
    currentTableModel->setData(currentTableModel->index(rowNum, 11), targetPath);

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->textEdit->clear();

    currentTableModel->submitAll();
}

void wardrobeWindow::on_pushButton_5_clicked()
{
    //修改衣物
    QString sql;
    QSqlQuery query;

    sql = "delete from clothes where clothesid = '" + QString::number(clothesSelectId, 10) + "'";
    query.exec(sql);

    //复制图片
    QString targetPath = "clothes/" + QString::number(clothesSelectId, 10) + ".jpg";
    copyFileToPath(picPath, targetPath, true); //覆盖式复制

    //插入数据库
    sql = "insert into clothes values ('" + QString::number(clothesSelectId, 10)
            + "', '" + ui->lineEdit->text()
            + "', '" + QString::number(ui->comboBox->currentIndex(), 10)
            + "', '" + QString::number(ui->comboBox_2->currentIndex(), 10)
            + "', '" + QString::number(ui->comboBox_3->currentIndex(), 10)
            + "', '" + ui->lineEdit_2->text()
            + "', '" + ui->lineEdit_3->text()
            + "', '" + ui->dateEdit->date().toString("yyyy.MM.dd")
            + "', '" + ui->lineEdit_4->text()
            + "', '" + ui->lineEdit_5->text()
            + "', '" + ui->textEdit->toPlainText()
            + "', '" + targetPath
            + "')";
    query.exec(sql);

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->textEdit->clear();

    currentTableModel->submitAll();

    currentTableModel->select();
}

void wardrobeWindow::on_pushButton_6_clicked()
{
    //删除衣物
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行
    currentTableModel->submitAll();
}

void wardrobeWindow::on_pushButton_7_clicked()
{
    //上传图片
    picPath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg)"));
    if(picPath.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    } else {
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + picPath);
    }

    ui->label->setScaledContents(true);
    ui->label->setPixmap(picPath);
}

void wardrobeWindow::on_tableWidget_clicked(const QModelIndex &index)
{
    //单击左侧列表
    int curRow = ui->tableWidget->currentItem()->row();  //获取选中的行
    switch(clothesSelect)
    {
    case true:
        currentTableModel->setFilter("type ='" + QString::number(curRow, 10) + "'");
        ui->comboBox->setCurrentIndex(curRow);
        break;
    case false:
        if(curRow < 4)
        {
            currentTableModel->setFilter("season ='" + QString::number(curRow, 10) + "'");
            ui->comboBox_2->setCurrentIndex(curRow);
            ui->comboBox_3->setCurrentIndex(0);
        }
        else
        {
            currentTableModel->setFilter("classtype ='" + QString::number(curRow-4, 10) + "'");
            ui->comboBox_2->setCurrentIndex(0);
            ui->comboBox_3->setCurrentIndex(curRow-4);
        }
        break;
    default:
        break;
    }

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->textEdit->clear();
}

void wardrobeWindow::on_tableView_clicked(const QModelIndex &index)
{
    //单击右侧列表
    int curRow = currentView->currentIndex().row(); //获取选中的行
    clothesSelectId = currentTableModel->index(curRow, 0).data().toInt();   //获得ID号

    ui->lineEdit->setText(currentTableModel->index(curRow, 1).data().toString());
    ui->comboBox->setCurrentIndex(currentTableModel->index(curRow, 2).data().toInt());
    ui->comboBox_2->setCurrentIndex(currentTableModel->index(curRow, 3).data().toInt());
    ui->comboBox_3->setCurrentIndex(currentTableModel->index(curRow, 4).data().toInt());
    ui->lineEdit_2->setText(currentTableModel->index(curRow, 5).data().toString());
    ui->lineEdit_3->setText(currentTableModel->index(curRow, 6).data().toString());
    ui->dateEdit->setDate(QDate::fromString(currentTableModel->index(curRow, 7).data().toString(), "yyyy.MM.dd"));
    ui->lineEdit_4->setText(currentTableModel->index(curRow, 8).data().toString());
    ui->lineEdit_5->setText(currentTableModel->index(curRow, 9).data().toString());
    ui->textEdit->setPlainText(currentTableModel->index(curRow, 10).data().toString());
    picPath = currentTableModel->index(curRow, 11).data().toString();

    ui->label->setScaledContents(true);
    ui->label->setPixmap(picPath);
}

void wardrobeWindow::tableWidgetData()
{
    //左侧列表数据填充
    int i = 0;
    ui->tableWidget->setRowCount(100); //设置一个较大的行号

    switch(clothesSelect)
    {
    case true:
        ui->tableWidget->setItem(i++, 0, new QTableWidgetItem(QString("文具用品")));
        ui->tableWidget->setItem(i++, 0, new QTableWidgetItem(QString("办公耗材")));
        ui->tableWidget->setItem(i++, 0, new QTableWidgetItem(QString("日杂百货")));
        ui->tableWidget->setItem(i++, 0, new QTableWidgetItem(QString("办公设备")));
        ui->tableWidget->setItem(i++, 0, new QTableWidgetItem(QString("办公家具")));
        ui->tableWidget->setItem(i++, 0, new QTableWidgetItem(QString("财务用品")));
        break;
    case false:
        ui->tableWidget->setItem(i++, 0, new QTableWidgetItem(QString("春季")));
        ui->tableWidget->setItem(i++, 0, new QTableWidgetItem(QString("夏季")));
        ui->tableWidget->setItem(i++, 0, new QTableWidgetItem(QString("秋季")));
        ui->tableWidget->setItem(i++, 0, new QTableWidgetItem(QString("冬季")));
        ui->tableWidget->setItem(i++, 0, new QTableWidgetItem(QString("职场")));
        ui->tableWidget->setItem(i++, 0, new QTableWidgetItem(QString("休闲")));
        ui->tableWidget->setItem(i++, 0, new QTableWidgetItem(QString("运动")));
        ui->tableWidget->setItem(i++, 0, new QTableWidgetItem(QString("宴会")));
        ui->tableWidget->setItem(i++, 0, new QTableWidgetItem(QString("其他")));
        break;
    default:
        break;
    }

    //设置为正常的列
    ui->tableWidget->setRowCount(i);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);  //单选

    //去掉tableWidget自带的行号
    QHeaderView* headerView = ui->tableWidget->verticalHeader();
    headerView->setHidden(true);
}

void wardrobeWindow::on_pushButton_8_clicked()
{
    //推荐搭配
    //randDlg.show();
}

void wardrobeWindow::on_pushButton_9_clicked()
{
    //仓库查询
    warw.show();
}

void wardrobeWindow::on_pushButton_10_clicked()
{
    //价格统计
    cashw.show();
}

void wardrobeWindow::on_pushButton_11_clicked()
{
    //人员管理
    userw.show();
}
