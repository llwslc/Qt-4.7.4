#include "roompreviewdialog.h"
#include "ui_roompreviewdialog.h"

roomPreviewDialog::roomPreviewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::roomPreviewDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlRelationalTableModel(this);
    currentView = ui->tableView;

    on_pushButton_5_clicked();

    ui->label->clear();
}

roomPreviewDialog::~roomPreviewDialog()
{
    delete ui;
}

void roomPreviewDialog::on_pushButton_clicked()
{
    //新建
    int rowNum = currentTableModel->rowCount(); //获得表的行数
    int id = currentTableModel->record(rowNum - 1).value(0).toInt() + 1;
    currentView->setEditTriggers(QAbstractItemView::DoubleClicked);  //使其可编辑
    currentTableModel->insertRow(rowNum); //添加一行
    currentTableModel->setData(currentTableModel->index(rowNum, 0), id);
    currentTableModel->setData(currentTableModel->index(rowNum, 1), 0);

    QString sourcePath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg)"));
    if(sourcePath.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    } else {
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + sourcePath);
    }

    QString targetPath = "room/" + QString::number(id, 10) + "." + "2.jpg";

    copyFileToPath(sourcePath, targetPath, true); //覆盖式复制
    currentTableModel->setData(currentTableModel->index(rowNum, 2), targetPath);

    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(targetPath));
}

void roomPreviewDialog::on_pushButton_2_clicked()
{
    //修改
    currentView->setEditTriggers(QAbstractItemView::DoubleClicked);  //使其可编辑
}

void roomPreviewDialog::on_pushButton_3_clicked()
{
    //删除
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行
}

void roomPreviewDialog::on_pushButton_4_clicked()
{
    //提交
    currentTableModel->submitAll();

    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    on_pushButton_5_clicked();
}

void roomPreviewDialog::on_pushButton_5_clicked()
{
    //刷新
    currentTableModel->setTable("room");
    currentTableModel->setRelation(1, QSqlRelation("roomstatus", "roomstatusid", "status"));
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setItemDelegate(new QSqlRelationalDelegate(currentView));
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->label->clear();
}

void roomPreviewDialog::on_pushButton_6_clicked()
{
    //上一张
    if (picCol <= 2)
    {
        picCol = 4;
    }
    else
    {
        picCol--;
    }
    QModelIndex indexData = currentTableModel->index(picRow, picCol);   //获得一条记录的一个属性的值

    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(indexData.data().toString()));
}

void roomPreviewDialog::on_pushButton_7_clicked()
{
    //下一张
    if (picCol < 2)
    {
        picCol = 3;
    }
    else if (picCol >= 4)
    {
        picCol = 2;
    }
    else
    {
        picCol++;
    }
    QModelIndex indexData = currentTableModel->index(picRow, picCol);   //获得一条记录的一个属性的值

    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(indexData.data().toString()));
}

void roomPreviewDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    int curCol = currentView->currentIndex().column(); //获取选中的列
    int curRow = currentView->currentIndex().row(); //获取选中的行

    picCol = currentView->currentIndex().column(); //获取选中的列
    picRow = currentView->currentIndex().row(); //获取选中的行

    QModelIndex indexData = currentTableModel->index(curRow, 3);   //获得一条记录的一个属性的值

    if (curCol < 2)
    {
        indexData = currentTableModel->index(curRow, 2);   //获得一条记录的一个属性的值
    }
    else
    {
        indexData = currentTableModel->index(curRow, curCol);   //获得一条记录的一个属性的值
    }

    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(indexData.data().toString()));
}

void roomPreviewDialog::on_tableView_doubleClicked(const QModelIndex &index)
{
    //列表双击
    int curCol = currentView->currentIndex().column(); //获取选中的列
    int curRow = currentView->currentIndex().row(); //获取选中的行
    int id = currentTableModel->record(curRow).value(0).toInt(); //获取选中行的id号
    QModelIndex indexData = currentTableModel->index(curRow, curCol);   //获得一条记录的一个属性的值

    QString sourcePath, targetPath;

    if (currentView->editTriggers() == QAbstractItemView::DoubleClicked) //如果是可编辑的模式
    {
        switch (curCol)
        {
        case 0:
        case 1:
            break;
        case 2:
        case 3:
        case 4:
            ui->label->setScaledContents(true);
            ui->label->setPixmap(QPixmap(indexData.data().toString()));

            sourcePath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg)"));
            if(sourcePath.length() == 0) {
                QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
            } else {
                QMessageBox::information(NULL, tr("Path"), tr("You selected ") + sourcePath);
            }

            targetPath = "room/" + QString::number(id, 10) + "." + QString::number(curCol, 10) + ".jpg";

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
