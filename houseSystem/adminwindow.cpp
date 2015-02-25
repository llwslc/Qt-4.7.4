#include "adminwindow.h"
#include "ui_adminwindow.h"

adminWindow::adminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adminWindow)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);

    //刷新楼盘
    on_pushButton_4_clicked();
}

adminWindow::~adminWindow()
{
    delete ui;
}

//菜单栏的有关触发
void adminWindow::on_action_triggered()
{
    //楼盘
    ui->tabWidget->setCurrentIndex(0);   //将光标转到相应选项卡
    on_pushButton_4_clicked();           //并执行相应的刷新
}

void adminWindow::on_action_2_triggered()
{
    //产权
    ui->tabWidget->setCurrentIndex(1);   //将光标转到相应选项卡
    on_pushButton_6_clicked();           //并执行相应的刷新
}

void adminWindow::on_action_3_triggered()
{
    //交易
    ui->tabWidget->setCurrentIndex(4);   //将光标转到相应选项卡
    on_pushButton_21_clicked();           //并执行相应的刷新
}

void adminWindow::on_action_4_triggered()
{
    //登记
    ui->tabWidget->setCurrentIndex(2);   //将光标转到相应选项卡
    on_pushButton_11_clicked();           //并执行相应的刷新
}

void adminWindow::on_action_5_triggered()
{
    //档案
    ui->tabWidget->setCurrentIndex(3);   //将光标转到相应选项卡
    on_pushButton_16_clicked();           //并执行相应的刷新
}

void adminWindow::on_action_6_triggered()
{
    //人员
    ui->tabWidget->setCurrentIndex(5);   //将光标转到相应选项卡
    on_pushButton_26_clicked();           //并执行相应的刷新
}

void adminWindow::on_action_7_triggered()
{
    //留言板
    ui->tabWidget->setCurrentIndex(6);   //将光标转到相应选项卡
    on_pushButton_35_clicked();           //并执行相应的刷新
}

void adminWindow::on_action_8_triggered()
{
    //退出登录
    this->hide();
    emit closeWindows();
}
//菜单栏触发结束

//各个页面刷新按钮
void adminWindow::on_pushButton_4_clicked()
{
    //楼盘
    currentView = ui->tableView;

    currentTableModel->setTable("houses");
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->pushButton->setEnabled(true); //添加按钮可用
}

void adminWindow::on_pushButton_6_clicked()
{
    //产权
    currentView = ui->tableView_2;

    currentTableModel->setTable("property");
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->pushButton_8->setEnabled(true); //添加按钮可用
}

void adminWindow::on_pushButton_11_clicked()
{
    //登记
    currentView = ui->tableView_3;

    currentTableModel->setTable("grade");
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->pushButton_13->setEnabled(true); //添加按钮置灰
}

void adminWindow::on_pushButton_16_clicked()
{
    //档案
    currentView = ui->tableView_4;

    currentTableModel->setTable("record");
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->pushButton_18->setEnabled(true); //添加按钮可用
}

void adminWindow::on_pushButton_21_clicked()
{
    //交易
    currentView = ui->tableView_5;

    currentTableModel->setTable("business");
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->pushButton_23->setEnabled(true); //添加按钮可用
}

void adminWindow::on_pushButton_26_clicked()
{
    //人员
    currentView = ui->tableView_6;

    currentTableModel->setTable("person");
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->pushButton_30->setEnabled(true); //添加按钮可用
}

void adminWindow::on_pushButton_35_clicked()
{
    //留言板
    currentView = ui->tableView_7;

    currentTableModel->setTable("message");
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->pushButton_32->setEnabled(true); //添加按钮可用
}

//各个页面刷新按钮 结束

void adminWindow::on_tabWidget_currentChanged(int index)
{
    //切换选项卡
    ui->label->clear(); //清空图片
    ui->label_2->clear();
    ui->label_3->clear();
    ui->label_4->clear();
    ui->label_5->clear();
    ui->label_6->clear();

    switch(index)
    {
    case 0:
        on_pushButton_4_clicked();
        break;
    case 1:
        on_pushButton_6_clicked();
        break;
    case 2:
        on_pushButton_11_clicked();
        break;
    case 3:
        on_pushButton_16_clicked();
        break;
    case 4:
        on_pushButton_21_clicked();
        break;
    case 5:
        on_pushButton_26_clicked();
        break;
    case 6:
        on_pushButton_35_clicked();
        break;
    default:
        break;
    }
}

//各个页面添加按钮
void adminWindow::on_pushButton_clicked()
{
    //楼盘
    int rowNum = currentTableModel->rowCount(); //获得表的行数
    int id = currentTableModel->record(rowNum - 1).value(0).toInt() + 1;

    currentView->setEditTriggers(QAbstractItemView::DoubleClicked);  //使其可编辑
    currentTableModel->insertRow(rowNum); //添加一行
    currentTableModel->setData(currentTableModel->index(rowNum, 0), id);

    QString sourcePath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg)"));
    if(sourcePath.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
        on_pushButton_4_clicked();
    } else {
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + sourcePath);
        ui->pushButton->setEnabled(false); //添加按钮置灰
    }

    QString targetPath = "house/" + QString::number(id, 10) + "." + "3.jpg";

    qDebug() << targetPath << endl;

    copyFileToPath(sourcePath, targetPath, true); //覆盖式复制
    currentTableModel->setData(currentTableModel->index(rowNum, 3), targetPath);

    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(targetPath));
}

void adminWindow::on_pushButton_8_clicked()
{
    //产权
    int rowNum = currentTableModel->rowCount(); //获得表的行数
    int id = currentTableModel->record(rowNum - 1).value(0).toInt() + 1;

    currentView->setEditTriggers(QAbstractItemView::AllEditTriggers);  //使其可编辑
    currentTableModel->insertRow(rowNum); //添加一行
    currentTableModel->setData(currentTableModel->index(rowNum, 0), id);

    QString sourcePath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg)"));
    if(sourcePath.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
        on_pushButton_6_clicked();
    } else {
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + sourcePath);
        ui->pushButton_8->setEnabled(false); //添加按钮置灰
    }

    QString targetPath = "property/" + QString::number(id, 10) + ".jpg";

    qDebug() << targetPath << endl;

    copyFileToPath(sourcePath, targetPath, true); //覆盖式复制
    currentTableModel->setData(currentTableModel->index(rowNum, 3), targetPath);

    ui->label_2->setScaledContents(true);
    ui->label_2->setPixmap(QPixmap(targetPath));
}

void adminWindow::on_pushButton_13_clicked()
{
    //登记
    int rowNum = currentTableModel->rowCount(); //获得表的行数
    int id = currentTableModel->record(rowNum - 1).value(0).toInt() + 1;

    currentView->setEditTriggers(QAbstractItemView::AllEditTriggers);  //使其可编辑
    currentTableModel->insertRow(rowNum); //添加一行
    currentTableModel->setData(currentTableModel->index(rowNum, 0), id);

    QString sourcePath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg)"));
    if(sourcePath.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
        on_pushButton_11_clicked();
    } else {
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + sourcePath);
        ui->pushButton_13->setEnabled(false); //添加按钮置灰
    }

    QString targetPath = "grade/" + QString::number(id, 10) + ".jpg";

    qDebug() << targetPath << endl;

    copyFileToPath(sourcePath, targetPath, true); //覆盖式复制
    currentTableModel->setData(currentTableModel->index(rowNum, 3), targetPath);

    ui->label_3->setScaledContents(true);
    ui->label_3->setPixmap(QPixmap(targetPath));
}

void adminWindow::on_pushButton_18_clicked()
{
    //档案
    int rowNum = currentTableModel->rowCount(); //获得表的行数
    int id = currentTableModel->record(rowNum - 1).value(0).toInt() + 1;

    currentView->setEditTriggers(QAbstractItemView::AllEditTriggers);  //使其可编辑
    currentTableModel->insertRow(rowNum); //添加一行
    currentTableModel->setData(currentTableModel->index(rowNum, 0), id);
    currentTableModel->setData(currentTableModel->index(rowNum, 1), QDate::currentDate().toString("yyyy.MM.dd"));
    currentTableModel->setData(currentTableModel->index(rowNum, 2), QTime::currentTime().toString("hh:mm:ss"));
    currentTableModel->setData(currentTableModel->index(rowNum, 4), 1);

    QString sourcePath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg)"));
    if(sourcePath.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
        on_pushButton_16_clicked();
    } else {
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + sourcePath);
        ui->pushButton_18->setEnabled(false); //添加按钮置灰
    }

    QString targetPath = "record/" + QString::number(id, 10) + ".jpg";

    qDebug() << targetPath << endl;

    copyFileToPath(sourcePath, targetPath, true); //覆盖式复制
    currentTableModel->setData(currentTableModel->index(rowNum, 5), targetPath);

    ui->label_4->setScaledContents(true);
    ui->label_4->setPixmap(QPixmap(targetPath));
}

void adminWindow::on_pushButton_23_clicked()
{
    //交易
    int rowNum = currentTableModel->rowCount(); //获得表的行数
    int id = currentTableModel->record(rowNum - 1).value(0).toInt() + 1;

    currentView->setEditTriggers(QAbstractItemView::AllEditTriggers);  //使其可编辑
    currentTableModel->insertRow(rowNum); //添加一行
    currentTableModel->setData(currentTableModel->index(rowNum, 0), id);

    ui->pushButton_23->setEnabled(false); //添加按钮置灰
}

void adminWindow::on_pushButton_30_clicked()
{
    //人员
    int rowNum = currentTableModel->rowCount(); //获得表的行数
    int id = currentTableModel->record(rowNum - 1).value(0).toInt() + 1;

    currentView->setEditTriggers(QAbstractItemView::AllEditTriggers);  //使其可编辑
    currentTableModel->insertRow(rowNum); //添加一行
    currentTableModel->setData(currentTableModel->index(rowNum, 0), id);

    ui->pushButton_30->setEnabled(false); //添加按钮置灰
}

void adminWindow::on_pushButton_32_clicked()
{
    //留言板
    ui->label_8->setText(adminname);
    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->textEdit->clear();
    ui->pushButton_32->setEnabled(false); //添加按钮置灰
}

//各个页面添加按钮 结束

//各个页面修改按钮
void adminWindow::on_pushButton_3_clicked()
{
    //楼盘
    currentView->setEditTriggers(QAbstractItemView::DoubleClicked);  //使其可编辑
}

void adminWindow::on_pushButton_7_clicked()
{
    //产权
    currentView->setEditTriggers(QAbstractItemView::DoubleClicked);  //使其可编辑
}

void adminWindow::on_pushButton_12_clicked()
{
    //登记
    currentView->setEditTriggers(QAbstractItemView::DoubleClicked);  //使其可编辑
}

void adminWindow::on_pushButton_17_clicked()
{
    //档案
    currentView->setEditTriggers(QAbstractItemView::DoubleClicked);  //使其可编辑
}

void adminWindow::on_pushButton_22_clicked()
{
    //交易
    currentView->setEditTriggers(QAbstractItemView::DoubleClicked);  //使其可编辑
}

void adminWindow::on_pushButton_28_clicked()
{
    //人员
    currentView->setEditTriggers(QAbstractItemView::DoubleClicked);  //使其可编辑
}

void adminWindow::on_pushButton_33_clicked()
{
    //留言板
    currentView->setEditTriggers(QAbstractItemView::DoubleClicked);  //使其可编辑
}
//各个页面修改按钮 结束

//各个页面删除按钮
void adminWindow::on_pushButton_2_clicked()
{
    //楼盘
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行
}

void adminWindow::on_pushButton_10_clicked()
{
    //产权
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行
}

void adminWindow::on_pushButton_15_clicked()
{
    //登记
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行
}

void adminWindow::on_pushButton_20_clicked()
{
    //档案
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行
}

void adminWindow::on_pushButton_25_clicked()
{
    //交易
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行
}

void adminWindow::on_pushButton_29_clicked()
{
    //人员
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行
}

void adminWindow::on_pushButton_34_clicked()
{
    //留言板
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行
}
//各个页面删除按钮 结束

//各个页面上传按钮
void adminWindow::on_pushButton_5_clicked()
{
    //楼盘
    currentTableModel->submitAll();

    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    on_pushButton_4_clicked();
}

void adminWindow::on_pushButton_9_clicked()
{
    //产权
    currentTableModel->submitAll();

    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    on_pushButton_6_clicked();
}

void adminWindow::on_pushButton_14_clicked()
{
    //登记
    currentTableModel->submitAll();

    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    on_pushButton_11_clicked();
}

void adminWindow::on_pushButton_19_clicked()
{
    //档案
    currentTableModel->submitAll();

    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑


    on_pushButton_16_clicked();
}

void adminWindow::on_pushButton_24_clicked()
{
    //交易
    currentTableModel->submitAll();

    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    on_pushButton_21_clicked();
}

void adminWindow::on_pushButton_27_clicked()
{
    //人员
    currentTableModel->submitAll();

    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    on_pushButton_26_clicked();
}

void adminWindow::on_pushButton_31_clicked()
{
    //留言板
    int rowNum = currentTableModel->rowCount(); //获得表的行数
    int idNum = 0;
    QSqlQuery query;
    query.exec("select messageId from message");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    currentTableModel->insertRow(rowNum); //添加一行
    currentTableModel->setData(currentTableModel->index(rowNum, 0), idNum);
    currentTableModel->setData(currentTableModel->index(rowNum, 1), adminname);
    currentTableModel->setData(currentTableModel->index(rowNum, 2), ui->lineEdit->text());
    currentTableModel->setData(currentTableModel->index(rowNum, 3), ui->comboBox->currentIndex());
    currentTableModel->setData(currentTableModel->index(rowNum, 4), ui->textEdit->toPlainText());

    currentTableModel->submitAll();

    ui->label_5->setText(username);
    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->textEdit->clear();

    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    on_pushButton_35_clicked();
}
//各个页面上传按钮 结束

//各个页面列表单击
void adminWindow::on_tableView_clicked(const QModelIndex &index)
{
    //楼盘
    int curCol = currentView->currentIndex().column(); //获取选中的列
    int curRow = currentView->currentIndex().row(); //获取选中的行

    QModelIndex indexData = currentTableModel->index(curRow, 3);   //获得一条记录的一个属性的值

    if (curCol < 3)
    {
        indexData = currentTableModel->index(curRow, 3);   //获得一条记录的一个属性的值
    }
    else
    {
        indexData = currentTableModel->index(curRow, curCol);   //获得一条记录的一个属性的值
    }
    qDebug() << indexData.data() << endl;

    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(indexData.data().toString()));
}

void adminWindow::on_tableView_2_clicked(const QModelIndex &index)
{
    //产权
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QModelIndex indexData = currentTableModel->index(curRow, 3);   //获得一条记录的一个属性的值
    qDebug() << indexData.data() << endl;

    ui->label_2->setScaledContents(true);
    ui->label_2->setPixmap(QPixmap(indexData.data().toString()));
}

void adminWindow::on_tableView_3_clicked(const QModelIndex &index)
{
    //登记
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QModelIndex indexData = currentTableModel->index(curRow, 3);   //获得一条记录的一个属性的值
    qDebug() << indexData.data() << endl;

    ui->label_3->setScaledContents(true);
    ui->label_3->setPixmap(QPixmap(indexData.data().toString()));
}

void adminWindow::on_tableView_4_clicked(const QModelIndex &index)
{
    //档案
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QModelIndex indexData = currentTableModel->index(curRow, 5);   //获得一条记录的一个属性的值
    qDebug() << indexData.data() << endl;

    ui->label_4->setScaledContents(true);
    ui->label_4->setPixmap(QPixmap(indexData.data().toString()));
}

void adminWindow::on_tableView_5_clicked(const QModelIndex &index)
{
    //交易
}

void adminWindow::on_tableView_6_clicked(const QModelIndex &index)
{
    //人员
}

void adminWindow::on_tableView_7_clicked(const QModelIndex &index)
{
    //留言板
    int curRow = currentView->currentIndex().row(); //获取选中的行
    ui->label_8->setText(currentTableModel->index(curRow, 1).data().toString());
    ui->lineEdit->setText(currentTableModel->index(curRow, 2).data().toString());
    ui->comboBox->setCurrentIndex(currentTableModel->index(curRow, 3).data().toInt());
    ui->textEdit->setPlainText(currentTableModel->index(curRow, 4).data().toString());
}
//各个页面列表单击 结束

//各个页面列表双击
void adminWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    //楼盘
    int curCol = currentView->currentIndex().column(); //获取选中的列

    int curRow = currentView->currentIndex().row(); //获取选中的行
    int id = currentTableModel->record(curRow).value(0).toInt(); //获取选中行的id号
    QModelIndex indexData = currentTableModel->index(curRow, curCol);   //获得一条记录的一个属性的值
    qDebug() << indexData.data() << endl;

    QString sourcePath, targetPath;

    if (currentView->editTriggers() == QAbstractItemView::DoubleClicked) //如果是可编辑的模式
    {
        switch (curCol)
        {
        case 0:
        case 1:
        case 2:
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            ui->label->setScaledContents(true);
            ui->label->setPixmap(QPixmap(indexData.data().toString()));

            sourcePath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg)"));
            if(sourcePath.length() == 0) {
                QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
            } else {
                QMessageBox::information(NULL, tr("Path"), tr("You selected ") + sourcePath);
            }

            targetPath = "house/" + QString::number(id, 10) + "." + QString::number(curCol, 10) + ".jpg";

            qDebug() << targetPath << endl;

            copyFileToPath(sourcePath, targetPath, true); //覆盖式复制
            currentTableModel->setData(currentTableModel->index(curRow, curCol), targetPath);

            ui->label->setScaledContents(true);
            ui->label->setPixmap(QPixmap(targetPath));
            break;
        default:
            break;
        }
    }
    else
    {
        ;
    }
}

void adminWindow::on_tableView_2_doubleClicked(const QModelIndex &index)
{
    //产权
    int curCol = currentView->currentIndex().column(); //获取选中的列

    int curRow = currentView->currentIndex().row(); //获取选中的行
    int id = currentTableModel->record(curRow).value(0).toInt(); //获取选中行的id号
    QModelIndex indexData = currentTableModel->index(curRow, curCol);   //获得一条记录的一个属性的值
    qDebug() << indexData.data() << endl;

    QString sourcePath, targetPath;

    if (currentView->editTriggers() == QAbstractItemView::DoubleClicked) //如果是可编辑的模式
    {
        switch (curCol)
        {
        case 0:
        case 1:
        case 2:
            break;
        case 3:
            ui->label->setScaledContents(true);
            ui->label->setPixmap(QPixmap(indexData.data().toString()));

            sourcePath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg)"));
            if(sourcePath.length() == 0) {
                QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
            } else {
                QMessageBox::information(NULL, tr("Path"), tr("You selected ") + sourcePath);
            }

            targetPath = "house/" + QString::number(id, 10) + "." + QString::number(curCol, 10) + ".jpg";

            qDebug() << targetPath << endl;

            copyFileToPath(sourcePath, targetPath, true); //覆盖式复制
            currentTableModel->setData(currentTableModel->index(curRow, curCol), targetPath);

            ui->label->setScaledContents(true);
            ui->label->setPixmap(QPixmap(targetPath));
            break;
        default:
            break;
        }
    }
    else
    {
        ;
    }
}

void adminWindow::on_tableView_3_doubleClicked(const QModelIndex &index)
{
    //登记
    int curCol = currentView->currentIndex().column(); //获取选中的列

    int curRow = currentView->currentIndex().row(); //获取选中的行
    int id = currentTableModel->record(curRow).value(0).toInt(); //获取选中行的id号
    QModelIndex indexData = currentTableModel->index(curRow, curCol);   //获得一条记录的一个属性的值
    qDebug() << indexData.data() << endl;

    QString sourcePath, targetPath;

    if (currentView->editTriggers() == QAbstractItemView::DoubleClicked) //如果是可编辑的模式
    {
        switch (curCol)
        {
        case 0:
        case 1:
        case 2:
            break;
        case 3:
            ui->label->setScaledContents(true);
            ui->label->setPixmap(QPixmap(indexData.data().toString()));

            sourcePath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg)"));
            if(sourcePath.length() == 0) {
                QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
            } else {
                QMessageBox::information(NULL, tr("Path"), tr("You selected ") + sourcePath);
            }

            targetPath = "house/" + QString::number(id, 10) + "." + QString::number(curCol, 10) + ".jpg";

            qDebug() << targetPath << endl;

            copyFileToPath(sourcePath, targetPath, true); //覆盖式复制
            currentTableModel->setData(currentTableModel->index(curRow, curCol), targetPath);

            ui->label->setScaledContents(true);
            ui->label->setPixmap(QPixmap(targetPath));
            break;
        default:
            break;
        }
    }
    else
    {
        ;
    }
}

void adminWindow::on_tableView_4_doubleClicked(const QModelIndex &index)
{
    //档案
    int curCol = currentView->currentIndex().column(); //获取选中的列

    int curRow = currentView->currentIndex().row(); //获取选中的行
    int id = currentTableModel->record(curRow).value(0).toInt(); //获取选中行的id号
    QModelIndex indexData = currentTableModel->index(curRow, curCol);   //获得一条记录的一个属性的值
    qDebug() << indexData.data() << endl;

    QString sourcePath, targetPath;

    if (currentView->editTriggers() == QAbstractItemView::DoubleClicked) //如果是可编辑的模式
    {
        switch (curCol)
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            break;
        case 5:
            ui->label->setScaledContents(true);
            ui->label->setPixmap(QPixmap(indexData.data().toString()));

            sourcePath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg)"));
            if(sourcePath.length() == 0) {
                QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
            } else {
                QMessageBox::information(NULL, tr("Path"), tr("You selected ") + sourcePath);
            }

            targetPath = "house/" + QString::number(id, 10) + "." + QString::number(curCol, 10) + ".jpg";

            qDebug() << targetPath << endl;

            copyFileToPath(sourcePath, targetPath, true); //覆盖式复制
            currentTableModel->setData(currentTableModel->index(curRow, curCol), targetPath);

            ui->label->setScaledContents(true);
            ui->label->setPixmap(QPixmap(targetPath));
            break;
        default:
            break;
        }
    }
    else
    {
        ;
    }
}

void adminWindow::on_tableView_5_doubleClicked(const QModelIndex &index)
{
    //交易
}

void adminWindow::on_tableView_6_doubleClicked(const QModelIndex &index)
{
    //人员
}
//各个页面列表双击 结束
