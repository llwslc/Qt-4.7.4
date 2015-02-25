#include "admindialog.h"
#include "ui_admindialog.h"

adminDialog::adminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);

    currentView = ui->tableView;

    idNum = -1;

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox->setEnabled(true);
    ui->label->clear();
    comboBox_2DataFill(ui->comboBox->currentIndex());

    on_pushButton_4_clicked(); //刷新食物
}

adminDialog::~adminDialog()
{
    delete ui;
}

void adminDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/png/bj2.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void adminDialog::on_pushButton_clicked()
{
    //添加
    QString sql;
    QSqlQuery query;

    QString targetPath;

    idNum = 0;
    switch(ui->comboBox->currentIndex())
    {
    case 0:
        //food
        //获取主键大小
        sql = "select foodid from food";
        query.exec(sql);
        while(query.next())
        {
            if(idNum < query.value(0).toInt())
                idNum = query.value(0).toInt();
        }

        idNum++;

        //复制图片
        targetPath = "food/" + QString::number(idNum, 10) + ".jpg";
        copyFileToPath(picPath, targetPath, true); //覆盖式复制

        //插入数据库
        sql = "insert into food values ('" + QString::number(idNum, 10)
                + "', '" + ui->lineEdit->text().trimmed()
                + "', '" + ui->lineEdit_2->text().trimmed()
                + "', '" + ui->lineEdit_3->text().trimmed()
                + "', '" + ui->comboBox_2->currentText()
                + "', '" + targetPath
                + "')";
        query.exec(sql);

        break;
    case 1:
        //cookbook
        sql = "select cookbookid from cookbook";
        query.exec(sql);
        while(query.next())
        {
            if(idNum < query.value(0).toInt())
                idNum = query.value(0).toInt();
        }

        idNum++;

        targetPath = "cookbook/" + QString::number(idNum, 10) + ".jpg";
        copyFileToPath(picPath, targetPath, true); //覆盖式复制

        sql = "insert into cookbook values ('" + QString::number(idNum, 10)
                + "', '" + ui->lineEdit->text().trimmed()
                + "', '" + ui->lineEdit_2->text().trimmed()
                + "', '" + ui->lineEdit_3->text().trimmed()
                + "', '" + ui->comboBox_2->currentText()
                + "', '" + targetPath
                + "')";
        query.exec(sql);

        break;
    case 2:
        //sports
        sql = "select sportsid from sports";
        query.exec(sql);
        while(query.next())
        {
            if(idNum < query.value(0).toInt())
                idNum = query.value(0).toInt();
        }

        idNum++;

        targetPath = "sports/" + QString::number(idNum, 10) + ".jpg";
        copyFileToPath(picPath, targetPath, true); //覆盖式复制

        sql = "insert into sports values ('" + QString::number(idNum, 10)
                + "', '" + ui->lineEdit->text().trimmed()
                + "', '" + ui->lineEdit_2->text().trimmed()
                + "', '" + ui->lineEdit_3->text().trimmed()
                + "', '" + ui->comboBox_2->currentText()
                + "', '" + targetPath
                + "')";
        query.exec(sql);

        break;
    default:
        break;
    }

    currentTableModel->select(); //刷新表

    ui->lineEdit->clear(); //清空输入
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->label->clear();
    comboBox_2DataFill(ui->comboBox->currentIndex());
}

void adminDialog::on_pushButton_2_clicked()
{
    //修改
    QString sql;
    QSqlQuery query;
    QString targetPath;

    switch(ui->comboBox->currentIndex())
    {
    case 0:
        //food
        //先删掉该id号的数据
        sql = "delete from food where foodid = '" + QString::number(idNum, 10) + "'";
        query.exec(sql);

        //图片修改
        targetPath = "food/" + QString::number(idNum, 10) + ".jpg";
        copyFileToPath(picPath, targetPath, true); //覆盖式复制

        //插入数据库
        sql = "insert into food values ('" + QString::number(idNum, 10)
                + "', '" + ui->lineEdit->text().trimmed()
                + "', '" + ui->lineEdit_2->text().trimmed()
                + "', '" + ui->lineEdit_3->text().trimmed()
                + "', '" + ui->comboBox_2->currentText()
                + "', '" + targetPath
                + "')";
        query.exec(sql);

        break;
    case 1:
        //cookbook
        sql = "delete from cookbook where cookbookid = '" + QString::number(idNum, 10) + "'";
        query.exec(sql);

        targetPath = "cookbook/" + QString::number(idNum, 10) + ".jpg";
        copyFileToPath(picPath, targetPath, true); //覆盖式复制

        sql = "insert into cookbook values ('" + QString::number(idNum, 10)
                + "', '" + ui->lineEdit->text().trimmed()
                + "', '" + ui->lineEdit_2->text().trimmed()
                + "', '" + ui->lineEdit_3->text().trimmed()
                + "', '" + ui->comboBox_2->currentText()
                + "', '" + targetPath
                + "')";
        query.exec(sql);

        break;
    case 2:
        //sports
        sql = "delete from sports where sportsid = '" + QString::number(idNum, 10) + "'";
        query.exec(sql);

        targetPath = "sports/" + QString::number(idNum, 10) + ".jpg";
        copyFileToPath(picPath, targetPath, true); //覆盖式复制

        sql = "insert into sports values ('" + QString::number(idNum, 10)
                + "', '" + ui->lineEdit->text().trimmed()
                + "', '" + ui->lineEdit_2->text().trimmed()
                + "', '" + ui->lineEdit_3->text().trimmed()
                + "', '" + ui->comboBox_2->currentText()
                + "', '" + targetPath
                + "')";
        query.exec(sql);

        break;
    default:
        break;
    }

    currentTableModel->select(); //刷新表

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->label->clear();
    comboBox_2DataFill(ui->comboBox->currentIndex());
}

void adminDialog::on_pushButton_3_clicked()
{
    //删除
    QString sql;
    QSqlQuery query;

    switch(ui->comboBox->currentIndex())
    {
    case 0:
        //food
        //删掉该id号的数据
        sql = "delete from food where foodid = '" + QString::number(idNum, 10) + "'";
        query.exec(sql);
        break;
    case 1:
        //cookbook
        sql = "delete from cookbook where cookbookid = '" + QString::number(idNum, 10) + "'";
        query.exec(sql);
        break;
    case 2:
        //sports
        sql = "delete from sports where sportsid = '" + QString::number(idNum, 10) + "'";
        query.exec(sql);
        break;
    default:
        break;
    }

    currentTableModel->select(); //刷新表

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->label->clear();
    comboBox_2DataFill(ui->comboBox->currentIndex());
}

void adminDialog::on_pushButton_7_clicked()
{
    //图片
    switch(ui->comboBox->currentIndex())
    {
    case 0:
        //food
        picPath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg)"));
        break;
    case 1:
        //cookbook
        picPath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg)"));
        break;
    case 2:
        //sports
        picPath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg)"));
        break;
    default:
        break;
    }

    if(picPath.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    } else {
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + picPath);
    }

    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(picPath));
}

void adminDialog::on_pushButton_4_clicked()
{
    //食物
    currentTableModel->setTable("food");
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->comboBox->setEnabled(true);
}

void adminDialog::on_pushButton_5_clicked()
{
    //食谱
    currentTableModel->setTable("cookbook");
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->comboBox->setEnabled(true);
}

void adminDialog::on_pushButton_6_clicked()
{
    //运动
    currentTableModel->setTable("sports");
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->label_4->setText("千卡/小时");
    ui->comboBox->setEnabled(true);
}

void adminDialog::on_comboBox_currentIndexChanged(int index)
{
    //分类变化
    int comboBoxIndex = ui->comboBox->currentIndex();
    comboBox_2DataFill(comboBoxIndex);
}

void adminDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    QString currentTableName = currentTableModel->tableName();
    int comboBoxIndex = 0;
    if(currentTableName == QString("food"))
    {
        comboBoxIndex = 0;
    }
    else if(currentTableName == QString("cookbook"))
    {
        comboBoxIndex = 1;
    }
    else if(currentTableName == QString("sports"))
    {
        comboBoxIndex = 2;
    }
    else
    {
    }
    ui->comboBox->setCurrentIndex(comboBoxIndex);
    ui->comboBox->setEnabled(false);
    comboBox_2DataFill(comboBoxIndex);

    int curRow = currentView->currentIndex().row(); //获取选中的行
    idNum = currentTableModel->index(curRow, 0).data().toInt();

    ui->lineEdit->setText(currentTableModel->index(curRow, 1).data().toString());
    ui->lineEdit_2->setText(currentTableModel->index(curRow, 2).data().toString());
    ui->lineEdit_3->setText(currentTableModel->index(curRow, 3).data().toString());

    ui->comboBox_2->setCurrentIndex(ui->comboBox_2->findText(currentTableModel->index(curRow, 4).data().toString()));

    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(currentTableModel->index(curRow, 5).data().toString()));

    picPath = currentTableModel->index(curRow, 5).data().toString();
}

void adminDialog::comboBox_2DataFill(const int comboBoxIndex)
{
    //细分类 选项填充

    //先清空
    ui->comboBox_2->clear();

    switch(comboBoxIndex)
    {
    case 0:
        //food
        ui->comboBox_2->addItem("谷类");
        ui->comboBox_2->addItem("薯类淀粉");
        ui->comboBox_2->addItem("干豆");
        ui->comboBox_2->addItem("蔬菜");
        ui->comboBox_2->addItem("菌藻");
        ui->comboBox_2->addItem("水果");
        ui->comboBox_2->addItem("坚果种子");
        ui->comboBox_2->addItem("畜肉");
        ui->comboBox_2->addItem("禽肉");
        ui->comboBox_2->addItem("乳类");
        ui->comboBox_2->addItem("蛋类");
        ui->comboBox_2->addItem("鱼虾蟹贝");
        ui->comboBox_2->addItem("婴幼儿食品");
        ui->comboBox_2->addItem("小吃甜饼");
        ui->comboBox_2->addItem("速食食品");
        ui->comboBox_2->addItem("软饮料");
        ui->comboBox_2->addItem("酒精饮料");
        ui->comboBox_2->addItem("糖蜜饯");
        ui->comboBox_2->addItem("油脂");
        ui->comboBox_2->addItem("调味品");
        ui->comboBox_2->addItem("药食及其它");

        ui->label_4->setText("千卡/百克");
        break;
    case 1:
        //cookbook
        ui->comboBox_2->addItem("私家菜");
        ui->comboBox_2->addItem("家常菜");
        ui->comboBox_2->addItem("北京菜");
        ui->comboBox_2->addItem("天津菜");
        ui->comboBox_2->addItem("湖南菜");
        ui->comboBox_2->addItem("江苏菜");
        ui->comboBox_2->addItem("东北菜");
        ui->comboBox_2->addItem("山东菜");
        ui->comboBox_2->addItem("上海菜");
        ui->comboBox_2->addItem("清真菜");
        ui->comboBox_2->addItem("四川菜");
        ui->comboBox_2->addItem("福建菜");
        ui->comboBox_2->addItem("湖北菜");
        ui->comboBox_2->addItem("广州菜");
        ui->comboBox_2->addItem("浙江菜");
        ui->comboBox_2->addItem("河南菜");
        ui->comboBox_2->addItem("素斋菜");
        ui->comboBox_2->addItem("山西菜");
        ui->comboBox_2->addItem("陕西菜");
        ui->comboBox_2->addItem("甘肃菜");
        ui->comboBox_2->addItem("广东菜");
        ui->comboBox_2->addItem("安徽菜");
        ui->comboBox_2->addItem("江西菜");
        ui->comboBox_2->addItem("滇黔菜");
        ui->comboBox_2->addItem("台湾菜");
        ui->comboBox_2->addItem("海南菜");
        ui->comboBox_2->addItem("新疆菜");
        ui->comboBox_2->addItem("广西菜");
        ui->comboBox_2->addItem("宁夏菜");
        ui->comboBox_2->addItem("青海菜");
        ui->comboBox_2->addItem("法国菜");

        ui->label_4->setText("千卡/百克");
        break;
    case 2:
        //sports
        ui->comboBox_2->addItem("休闲娱乐");
        ui->comboBox_2->addItem("走路");
        ui->comboBox_2->addItem("调节训练");
        ui->comboBox_2->addItem("舞蹈");
        ui->comboBox_2->addItem("自行车运动");
        ui->comboBox_2->addItem("水上运动");
        ui->comboBox_2->addItem("日常运动");
        ui->comboBox_2->addItem("工作");
        ui->comboBox_2->addItem("家务");
        ui->comboBox_2->addItem("园艺运动");
        ui->comboBox_2->addItem("其他");
        ui->comboBox_2->addItem("体育运动");
        ui->comboBox_2->addItem("跑步");

        ui->label_4->setText("千卡/小时");
        break;
    default:
        break;
    }
}
