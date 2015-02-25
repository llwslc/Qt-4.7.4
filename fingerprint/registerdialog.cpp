#include "registerdialog.h"
#include "ui_registerdialog.h"

registerDialog::registerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerDialog)
{
    ui->setupUi(this);

    QDesktopWidget* desktop = QApplication::desktop();
    this->move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
    this->setWindowTitle("指纹录入管理");

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    qFinger = new qFingerprint(this);
    connect(qFinger, SIGNAL(OnImageReceived()), this, SLOT(finishImageReceived()));
    connect(qFinger, SIGNAL(OnFeatureInfo(int)), this, SLOT(finishFeatureInfo(int)));
    connect(qFinger, SIGNAL(OnEnroll(QString)), this, SLOT(finishEnroll(QString)));

    init();
}

registerDialog::~registerDialog()
{
    delete ui;
}

void registerDialog::showEvent(QShowEvent *)
{
    init();
    on_pushButton_clicked();
}

void registerDialog::paintEvent(QPaintEvent *)
{}

void registerDialog::closeEvent(QCloseEvent *)
{
    qFinger->EndEngine();
    emit OnClose();
}

void registerDialog::init()
{
    isLineToFinger = false;

    currentTableModel->setTable("users");
    currentTableModel->select();

    currentTableModel->setHeaderData(0, Qt::Horizontal, QString("编号"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QString("姓名"));
    currentTableModel->setHeaderData(2, Qt::Horizontal, QString("身份证"));
    currentTableModel->setHeaderData(3, Qt::Horizontal, QString("权限"));
    currentTableModel->setHeaderData(4, Qt::Horizontal, QString("指纹特征"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->comboBox->clear();
    ui->comboBox->addItem("员工");
    ui->comboBox->addItem("采购员");
    ui->comboBox->addItem("保管员");
    ui->comboBox->addItem("主管");
    ui->comboBox->setCurrentIndex(0);

    ui->lineEdit->setEnabled(false);
    ui->lineEdit_1->setEnabled(false);
    ui->lineEdit_1->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    QRegExp regExp("(^\\d{18}$)|(^\\d{17}(\\d|X|x)$)");
    QRegExpValidator *pRevalidotor = new QRegExpValidator(regExp, 0);
    ui->lineEdit_3->setValidator(pRevalidotor);
    ui->lineEdit_4->clear();
    ui->plainTextEdit->setReadOnly(true);
    ui->plainTextEdit->clear();

    ui->label_2->clear();
    ui->label_2->setScaledContents(true);
    ui->label_3->clear();
    ui->label_3->setText("指纹质量 : ");
    ui->label_10->clear();
}

void registerDialog::on_lineEdit_4_textChanged(const QString &arg1)
{
    //搜索框输入改变
    currentTableModel->setFilter("username like '%" + arg1 + "%'");
}

void registerDialog::on_pushButton_clicked()
{
    //连接指纹仪
    int result = -1;
    QString strSN = "指纹仪器未连接!";
    result = qFinger->InitEngine();
    if(result == 0)
    {
        strSN = qFinger->SensorSN();
        isLineToFinger = true;
    }
    else
    {
        qFinger->EndEngine();
        isLineToFinger = false;
        QMessageBox::information(NULL, "error.", "初始化指纹仪失败!");
    }
    ui->lineEdit->setText(QString(strSN));

}

void registerDialog::on_pushButton_3_clicked()
{
    //开始登记指纹
    if(isLineToFinger == false)
    {
        QMessageBox::information(NULL, "error.", "指纹仪未连接!");
    }
    else
    {
        if(qFinger->IsRegister())
        {
            qFinger->CancelEnroll();
        }
        qFinger->BeginEnroll();
        ui->label_10->clear();
        ui->label_10->setText("还需按压次数 : 3 次");
    }
}

void registerDialog::on_pushButton_8_clicked()
{
    //取消登记指纹
    if(isLineToFinger == false)
    {
        QMessageBox::information(NULL, "error.", "指纹仪未连接!");
    }
    else
    {
        qFinger->CancelEnroll();
    }
}

void registerDialog::on_pushButton_4_clicked()
{
    //添加信息
    QSqlQuery query;
    QString sql;
    int idNum = 0;
    QString oldUsername = "";
    QString oldUserzw = "";
    QString username = ui->lineEdit_2->text().trimmed();
    QString idcard = ui->lineEdit_3->text().trimmed();
    QString role = QString::number(ui->comboBox->currentIndex(), 10);
    QString userzw = ui->plainTextEdit->toPlainText();

    if(username == "")
    {
        QMessageBox::information(NULL, "error.", "没有填写姓名!");
        return;
    }

    if(idcard == "")
    {
        QMessageBox::information(NULL, "error.", "没有填写身份证!");
        return;
    }

    sql = "select usersid from users where userzw = '" + userzw + "'";
    query.exec(sql);
    while(query.next())
    {
        QMessageBox::information(NULL, "error.", "指纹重复,请重新录入指纹!");
        return;
    }

    sql = "select usersid from users where idcard = '" + idcard + "' and role = '" + role + "'";
    query.exec(sql);
    while(query.next())
    {
        QMessageBox::information(NULL, "error.", "身份证重复,该权限下此员工已经存在!");
        return;
    }

    sql = "select username, userzw from users where idcard = '" + idcard + "'";
    query.exec(sql);
    while(query.next())
    {
        oldUsername = query.value(0).toString();
        oldUserzw = query.value(1).toString();

        if(oldUsername != username)
        {
            QMessageBox::information(NULL, "error.", "与以往录入的身份证对应的姓名不同! 原姓名 : " + oldUsername);
            return;
        }

        if(oldUserzw == userzw)
        {
            QMessageBox::information(NULL, "error.", "不同权限下需要不同的指纹,请重新录入另一个手指指纹!");
            return;
        }
    }

    query.exec("select usersid from users");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    sql = "insert into users values('" + QString::number(idNum, 10) + "', '" + username + "', '" + idcard + "', '" + role + "', '" + userzw + "')";
    query.exec(sql);

    ui->lineEdit_1->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->plainTextEdit->clear();

    currentTableModel->select();
    ui->label_10->clear();

    if(userzw != "")
    {
        QVariant fingerTempVar;
        fingerTempVar = qFinger->DecodeTemplate(userzw);
        insertFingerTempMap(idNum, fingerTempVar);
    }
}

void registerDialog::on_pushButton_5_clicked()
{
    //修改信息
    QSqlQuery query;
    QString sql;
    QString oldUsername = "";
    QString oldRole = "";
    QString idNum = ui->lineEdit_1->text().trimmed();
    QString username = ui->lineEdit_2->text().trimmed();
    QString idcard = ui->lineEdit_3->text().trimmed();
    QString role = QString::number(ui->comboBox->currentIndex(), 10);
    QString userzw = ui->plainTextEdit->toPlainText();

    if(username == "")
    {
        QMessageBox::information(NULL, "error.", "没有填写姓名!");
        return;
    }

    if(idcard == "")
    {
        QMessageBox::information(NULL, "error.", "没有填写身份证!");
        return;
    }

    sql = "select usersid from users where idcard = '" + idcard + "' and role = '" + role + "' and usersid <> '" + idNum + "'";
    query.exec(sql);
    while(query.next())
    {
        QMessageBox::information(NULL, "error.", "身份证重复,该用户已经存在!");
        return;
    }

    sql = "select username, role from users where idcard = '" + idcard + "'";
    query.exec(sql);
    while(query.next())
    {
        oldUsername = query.value(0).toString();
        oldRole = query.value(1).toString();

        if(oldUsername != username)
        {
            QMessageBox::information(NULL, "error.", "与以往录入的身份证对应的姓名不同! 原姓名 : " + oldUsername);
            return;
        }

        if(oldRole != role)
        {
            sql = "select stockslogid from stockslog where buyerid = '" + idNum + "' or keeperid = '" + idNum + "' or leaderid = '" + idNum + "'";
            query.exec(sql);
            while(query.next())
            {
                QMessageBox::information(NULL, "error.", "已有入库登记记录,无法修改权限,请重新添加!");
                return;
            }

            sql = "select borrowlogid from borrowlog where keeperid = '" + idNum + "' or userid = '" + idNum + "'";
            query.exec(sql);
            while(query.next())
            {
                QMessageBox::information(NULL, "error.", "已有借还物品记录,无法修改权限,请重新添加!");
                return;
            }
        }
    }


    sql = "update users set username = '" + username + "' , idcard = '" + idcard + "' , role = '" + role + "' , userzw = '" + userzw + "' where usersid = '" + idNum + "'";
    query.exec(sql);

    ui->lineEdit_1->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->plainTextEdit->clear();
    currentTableModel->select();
    ui->label_10->clear();

    if(userzw != "")
    {
        int userid = idNum.toInt();
        QVariant fingerTempVar;
        fingerTempVar = qFinger->DecodeTemplate(userzw);
        modifyFingerTempMap(userid, fingerTempVar);
    }
}

void registerDialog::on_pushButton_6_clicked()
{
    //删除信息
    QSqlQuery query;
    QString sql;
    QString idNum = ui->lineEdit_1->text().trimmed();
    QString username = ui->lineEdit_2->text().trimmed();
    QString idcard = ui->lineEdit_3->text().trimmed();
    QString role = QString::number(ui->comboBox->currentIndex(), 10);
    QString userzw = ui->plainTextEdit->toPlainText();

    if(idNum == "")
    {
        QMessageBox::information(NULL, "error.", "没有选择要删除的人员!");
        return;
    }

    if(username == false)
    {
        QMessageBox::information(NULL, "error.", "没有填写姓名!");
        return;
    }

    if(idcard == false)
    {
        QMessageBox::information(NULL, "error.", "没有填写身份证!");
        return;
    }

    sql = "select stockslogid from stockslog where buyerid = '" + idNum + "' or keeperid = '" + idNum + "' or leaderid = '" + idNum + "'";
    query.exec(sql);
    while(query.next())
    {
        QMessageBox::information(NULL, "error.", "已有入库登记记录,无法删除!");
        return;
    }

    sql = "select borrowlogid from borrowlog where keeperid = '" + idNum + "' or userid = '" + idNum + "'";
    query.exec(sql);
    while(query.next())
    {
        QMessageBox::information(NULL, "error.", "已有借还物品记录,无法删除!");
        return;
    }

    sql = "delete from users where username = '" + username + "' and idcard = '" + idcard + "' and role = '" + role + "' and usersid = '" + idNum + "'";
    query.exec(sql);

    ui->lineEdit_1->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->plainTextEdit->clear();
    currentTableModel->select();
    ui->label_10->clear();

    if(userzw != "")
    {
        int userid = idNum.toInt();
        removeFingerTempMap(userid);
    }
}

void registerDialog::on_pushButton_7_clicked()
{
    //刷新信息
    init();
}

void registerDialog::on_tableView_clicked(const QModelIndex &index)
{
    //点击列表
    int curRow = index.row(); //获取选中的行

    ui->lineEdit_1->setText(currentTableModel->index(curRow, 0).data().toString());
    ui->lineEdit_2->setText(currentTableModel->index(curRow, 1).data().toString());
    ui->lineEdit_3->setText(currentTableModel->index(curRow, 2).data().toString());
    ui->comboBox->setCurrentIndex(currentTableModel->index(curRow, 3).data().toInt());
    ui->plainTextEdit->setPlainText(currentTableModel->index(curRow, 4).data().toString());
}

void registerDialog::finishImageReceived()
{
    //指纹图像完成
    qFinger->SaveBitmap();
    ui->label_2->setPixmap(QPixmap(fingerBmpPath));
}

void registerDialog::finishFeatureInfo(int Aquality)
{
    //指纹质量报告
    switch(Aquality)
    {
    case 0:
        ui->label_3->setText("指纹质量 : 合格");
        break;
    case 1:
        ui->label_3->setText("指纹质量 : 特征点不够");
        break;
    case 2:
        ui->label_3->setText("指纹质量 : 无法取到指纹特征");
        break;
    default:
        ui->label_3->setText("指纹质量 : ");
        break;
    }

    if(qFinger->IsRegister())
    {
        ui->label_10->clear();
        ui->label_10->setText("还需按压次数 : " + QString::number(qFinger->EnrollIndex()-1, 10) + " 次");
    }
}

void registerDialog::finishEnroll(QString ATemplate)
{
    //登记完成
    if(ATemplate == "false")
    {
        QMessageBox::information(NULL, "error.", "登记失败,请重新登记.");
    }
    else
    {
        //指纹对比
        QVariant fingerTempVar = qFinger->DecodeTemplate(ATemplate);
        QMapIterator<int, QVariant> i(fingerTemplateMap);
        while (i.hasNext())
        {
            i.next();
            if(qFinger->VerFinger(fingerTempVar, i.value()))
            {
                QMessageBox::information(NULL, "error.", "已经登记过的手指,请更换手指登记.");
                return;
            }
        }
        ui->label_10->clear();
        ui->label_10->setText("登记成功!");
        ui->plainTextEdit->setPlainText(ATemplate);
    }
}
