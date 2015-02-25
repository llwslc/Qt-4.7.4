#include "adminsystem.h"
#include "ui_adminsystem.h"

adminSystem::adminSystem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adminSystem)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);

    /*0 商品信息
      1 仓库管理
      2 会员管理
      3 打卡记录
      4 员工管理 */
    tagFlag = 0;

    on_pushButton_clicked(); //刷新仓库
}

adminSystem::~adminSystem()
{
    delete ui;
}

void adminSystem::on_pushButton_clicked()
{
    //商品管理
    ui->groupBox_2->setTitle("商品管理");
    tagFlag = 0;

    currentView = ui->tableView;

    currentTableModel->setTable("goods");
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->pushButton->setEnabled(true); //添加按钮可用

    ui->label->clear(); //清空label
    ui->label_2->clear(); //清空label
}

void adminSystem::on_pushButton_2_clicked()
{
    //仓库管理
    ui->groupBox_2->setTitle("仓库管理");
    tagFlag = 1;

    currentView = ui->tableView;

    currentTableModel->setTable("depot");
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->label->clear(); //清空label
    ui->label_2->clear(); //清空label
}

void adminSystem::on_pushButton_3_clicked()
{
    //会员管理
    ui->groupBox_2->setTitle("会员管理");
    tagFlag = 2;

    currentView = ui->tableView;

    currentTableModel->setTable("member");
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->label->clear(); //清空label
    ui->label_2->clear(); //清空label
}

void adminSystem::on_pushButton_4_clicked()
{
    //打卡记录
    ui->groupBox_2->setTitle("打卡记录");
    tagFlag = 3;

    currentView = ui->tableView;

    currentTableModel->setTable("punch");
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->label->clear(); //清空label
    ui->label_2->clear(); //清空label
}

void adminSystem::on_pushButton_5_clicked()
{
    //营业额记录
    tWindows.show();
}

void adminSystem::on_pushButton_6_clicked()
{
    //员工管理
    ui->groupBox_2->setTitle("打卡记录");
    tagFlag = 4;

    currentView = ui->tableView;

    currentTableModel->setTable("person");
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->label->clear(); //清空label
    ui->label_2->clear(); //清空label
}

void adminSystem::on_pushButton_7_clicked()
{
    //添加信息
    int rowNum, id;
    QString sourcePath, targetPath;

    rowNum = currentTableModel->rowCount(); //获得表的行数
    id = currentTableModel->record(rowNum - 1).value(0).toInt() + 1;

    currentView->setEditTriggers(QAbstractItemView::DoubleClicked);  //使其可编辑
    currentTableModel->insertRow(rowNum); //添加一行
    currentTableModel->setData(currentTableModel->index(rowNum, 0), id);

    switch(tagFlag)
    {
    case 0:
        sourcePath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg)"));
        if(sourcePath.length() == 0) {
            QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
            on_pushButton_clicked();
            return;
        } else {
            QMessageBox::information(NULL, tr("Path"), tr("You selected ") + sourcePath);
            ui->pushButton_7->setEnabled(false); //添加按钮置灰
        }

        targetPath = "goods/" + QString::number(id, 10) + ".jpg";

        currentTableModel->setData(currentTableModel->index(rowNum, 4), targetPath);

        break;
    case 1:
        sourcePath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg)"));
        if(sourcePath.length() == 0) {
            QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
            on_pushButton_2_clicked();
            return;
        } else {
            QMessageBox::information(NULL, tr("Path"), tr("You selected ") + sourcePath);
            ui->pushButton_7->setEnabled(false); //添加按钮置灰
        }

        targetPath = "depot/" + QString::number(id, 10) + ".jpg";

        currentTableModel->setData(currentTableModel->index(rowNum, 4), targetPath);
        break;
    case 2:
        sourcePath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg)"));
        if(sourcePath.length() == 0) {
            QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
            on_pushButton_3_clicked();
            return;
        } else {
            QMessageBox::information(NULL, tr("Path"), tr("You selected ") + sourcePath);
            ui->pushButton_7->setEnabled(false); //添加按钮置灰
        }

        targetPath = "member/" + QString::number(id, 10) + ".jpg";

        currentTableModel->setData(currentTableModel->index(rowNum, 3), targetPath);
        break;
    case 3:
        break;
    case 4:
        break;
    default:
        break;
    }

    copyFileToPath(sourcePath, targetPath, true); //覆盖式复制

    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(targetPath));
}

void adminSystem::on_pushButton_8_clicked()
{
    //删除信息
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行
}

void adminSystem::on_pushButton_9_clicked()
{
    //修改信息
    currentView->setEditTriggers(QAbstractItemView::DoubleClicked);  //使其可编辑
}

void adminSystem::on_pushButton_10_clicked()
{
    //提交信息
    currentTableModel->submitAll();

    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    on_pushButton_11_clicked();
}

void adminSystem::on_pushButton_11_clicked()
{
    //刷新信息
    currentView = ui->tableView;

    switch(tagFlag)
    {
    case 0:
        currentTableModel->setTable("goods");
        break;
    case 1:
        currentTableModel->setTable("depot");
        break;
    case 2:
        currentTableModel->setTable("member");
        break;
    case 3:
        currentTableModel->setTable("punch");
        break;
    case 4:
        currentTableModel->setTable("person");
        break;
    default:
        break;
    }
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->pushButton_7->setEnabled(true); //添加按钮可用
}


void adminSystem::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    QString labelInfo;
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QModelIndex indexData;
    switch(tagFlag)
    {
    case 0:
        indexData = currentTableModel->index(curRow, 4);   //获得一条记录的一个属性的值
        labelInfo = " 商品名称 : " + currentTableModel->index(curRow, 1).data().toString()
                + "\n\n 商品单价 : " + currentTableModel->index(curRow, 2).data().toString()
                + "\n\n 剩余个数 : " + currentTableModel->index(curRow, 3).data().toString();
        break;
    case 1:
        indexData = currentTableModel->index(curRow, 4);   //获得一条记录的一个属性的值
        labelInfo = " 商品名称 : " + currentTableModel->index(curRow, 1).data().toString()
                + "\n\n 商品进价 : " + currentTableModel->index(curRow, 2).data().toString()
                + "\n\n 剩余个数 : " + currentTableModel->index(curRow, 3).data().toString();
        break;
    case 2:
        indexData = currentTableModel->index(curRow, 3);   //获得一条记录的一个属性的值
        labelInfo = " 会员编号 : " + currentTableModel->index(curRow, 0).data().toString()
                + "\n\n 会员姓名 : " + currentTableModel->index(curRow, 1).data().toString()
                + "\n\n 消费额度 : " + currentTableModel->index(curRow, 2).data().toString();
        break;
    case 3:
        break;
    case 4:
        break;
    default:
        break;
    }
    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(indexData.data().toString()));

    ui->label_2->setText(labelInfo);
}



void adminSystem::on_tableView_doubleClicked(const QModelIndex &index)
{
    //列表双击
    int curCol = currentView->currentIndex().column(); //获取选中的列
    int curRow = currentView->currentIndex().row(); //获取选中的行
    int id = currentTableModel->record(curRow).value(0).toInt(); //获取选中行的id号
    int picFlag = false;
    QModelIndex indexData = currentTableModel->index(curRow, curCol);   //获得一条记录的一个属性的值
    qDebug() << indexData.data() << endl;

    QString sourcePath, targetPath;

    if (currentView->editTriggers() == QAbstractItemView::DoubleClicked) //如果是可编辑的模式
    {
        switch(tagFlag)
        {
        case 0:
            if (curCol == 4)
            {
                picFlag = true;
            }
            targetPath = "goods/" + QString::number(id, 10) + ".jpg";
            break;
        case 1:
            if (curCol == 4)
            {
                picFlag = true;
            }
            targetPath = "depot/" + QString::number(id, 10) + ".jpg";
            break;
        case 2:
            if (curCol == 3)
            {
                picFlag = true;
            }
            targetPath = "member/" + QString::number(id, 10) + ".jpg";
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            break;
        }

        if (picFlag == true)
        {
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

void adminSystem::on_pushButton_12_clicked()
{
    //退出登录
    this->close();
    emit exitLogin();
}

void adminSystem::paintEvent(QPaintEvent *)
{
    //背景图片
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/png/1.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

