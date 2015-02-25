#include "keepersystem.h"
#include "ui_keepersystem.h"

keeperSystem::keeperSystem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::keeperSystem)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);

    on_pushButton_5_clicked();
}

keeperSystem::~keeperSystem()
{
    delete ui;
}

void keeperSystem::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    QString labelInfo;
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QModelIndex indexData = currentTableModel->index(curRow, 4);   //获得一条记录的一个属性的值
    labelInfo = " 商品名称 : " + currentTableModel->index(curRow, 1).data().toString()
            + "\n\n 商品单价 : " + currentTableModel->index(curRow, 2).data().toString()
            + "\n\n 剩余个数 : " + currentTableModel->index(curRow, 3).data().toString();

    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(indexData.data().toString()));

    ui->label_2->setText(labelInfo);
}

void keeperSystem::on_tableView_doubleClicked(const QModelIndex &index)
{
    //列表双击
    int curCol = currentView->currentIndex().column(); //获取选中的列
    int curRow = currentView->currentIndex().row(); //获取选中的行
    int id = currentTableModel->record(curRow).value(0).toInt(); //获取选中行的id号

    QModelIndex indexData = currentTableModel->index(curRow, curCol);   //获得一条记录的一个属性的值
    qDebug() << indexData.data() << endl;

    QString sourcePath, targetPath;

    if (currentView->editTriggers() == QAbstractItemView::DoubleClicked) //如果是可编辑的模式
    {
        if (curCol == 4)
        {
            targetPath = "depot/" + QString::number(id, 10) + ".jpg";
            ui->label->setScaledContents(true);
            ui->label->setPixmap(QPixmap(indexData.data().toString()));

            sourcePath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg)"));
            if(sourcePath.length() == 0) {
                QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
            } else {
                QMessageBox::information(NULL, tr("Path"), tr("You selected ") + sourcePath);
            }

            copyFileToPath(sourcePath, targetPath, true); //覆盖式复制
            currentTableModel->setData(currentTableModel->index(curRow, curCol), targetPath);

            ui->label->setScaledContents(true);
            ui->label->setPixmap(QPixmap(targetPath));
        }
    }
    else
    {
        ;
    }
}

void keeperSystem::on_pushButton_clicked()
{
    //添加
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

    QString targetPath = "depot/" + QString::number(id, 10) + ".jpg";

    qDebug() << targetPath << endl;

    copyFileToPath(sourcePath, targetPath, true); //覆盖式复制
    currentTableModel->setData(currentTableModel->index(rowNum, 4), targetPath);

    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(targetPath));
    ui->label_2->clear();
}

void keeperSystem::on_pushButton_2_clicked()
{
    //删除
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行
}

void keeperSystem::on_pushButton_3_clicked()
{
    //修改
    currentView->setEditTriggers(QAbstractItemView::DoubleClicked);  //使其可编辑
}

void keeperSystem::on_pushButton_4_clicked()
{
    //提交
    currentTableModel->submitAll();

    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    on_pushButton_5_clicked();
}

void keeperSystem::on_pushButton_5_clicked()
{
    //刷新
    currentView = ui->tableView;

    currentTableModel->setTable("depot");
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->pushButton->setEnabled(true); //添加按钮可用

    ui->label->clear(); //清空label
    ui->label_2->clear(); //清空label
}

void keeperSystem::on_pushButton_6_clicked()
{
    //退出登录
    this->close();
    emit exitLogin();
}

void keeperSystem::paintEvent(QPaintEvent *)
{
    //背景图片
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/png/2.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
