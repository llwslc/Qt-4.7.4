#include "maindialog.h"
#include "ui_maindialog.h"

mainDialog::mainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    personidString = QString("0");

    connect(&logonw, SIGNAL(registerSignal()), this, SLOT(init()));
    connect(&neww, SIGNAL(newSignal()), this, SLOT(init()));
    connect(&modw, SIGNAL(modSignal()), this, SLOT(init()));

    ui->pushButton->setStyleSheet(QString("QPushButton{border-image:url(:/images/button1.png)0, 0, 0, 0;}\n"
                                          "QPushButton:hover{border-image:url(:/images/button2.png)0, 0, 0, 0;}\n"
                                          "QPushButton:pressed{border-image:url(:/images/button3.png)0, 0, 0, 0;}"));
    ui->pushButton_2->setStyleSheet(QString("QPushButton{border-image:url(:/images/button1.png)0, 0, 0, 0;}\n"
                                            "QPushButton:hover{border-image:url(:/images/button2.png)0, 0, 0, 0;}\n"
                                            "QPushButton:pressed{border-image:url(:/images/button3.png)0, 0, 0, 0;}"));
    ui->pushButton_3->setStyleSheet(QString("QPushButton{border-image:url(:/images/button1.png)0, 0, 0, 0;}\n"
                                            "QPushButton:hover{border-image:url(:/images/button2.png)0, 0, 0, 0;}\n"
                                            "QPushButton:pressed{border-image:url(:/images/button3.png)0, 0, 0, 0;}"));
    ui->pushButton_4->setStyleSheet(QString("QPushButton{border-image:url(:/images/button1.png)0, 0, 0, 0;}\n"
                                            "QPushButton:hover{border-image:url(:/images/button2.png)0, 0, 0, 0;}\n"
                                            "QPushButton:pressed{border-image:url(:/images/button3.png)0, 0, 0, 0;}"));
    ui->pushButton_5->setStyleSheet(QString("QPushButton{border-image:url(:/images/button1.png)0, 0, 0, 0;}\n"
                                            "QPushButton:hover{border-image:url(:/images/button2.png)0, 0, 0, 0;}\n"
                                            "QPushButton:pressed{border-image:url(:/images/button3.png)0, 0, 0, 0;}"));

    init();

    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();
    ui->lineEdit_3->hide();
    currentView->hide();
}

mainDialog::~mainDialog()
{
    delete ui;
}

void mainDialog::init()
{
    //初始化
    currentTableModel->setTable("address");
    currentTableModel->setFilter("personid = '" + personidString + "'");
    currentTableModel->removeColumn(0);
    currentTableModel->removeColumn(0);
    currentTableModel->removeColumn(0);
    currentTableModel->select();

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("姓名"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("电话"));
    currentTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("固话"));
    currentTableModel->setHeaderData(3, Qt::Horizontal, QObject::tr("性别"));
    currentTableModel->setHeaderData(4, Qt::Horizontal, QObject::tr("生日"));
    currentTableModel->setHeaderData(5, Qt::Horizontal, QObject::tr("QQ"));
    currentTableModel->setHeaderData(6, Qt::Horizontal, QObject::tr("住址"));
    currentTableModel->setHeaderData(7, Qt::Horizontal, QObject::tr("备注"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
}

void mainDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/images/bg.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void mainDialog::on_pushButton_clicked()
{
    //查询
    QSqlQuery query;
    QString sql;

    sql = "select * from person where name = '" + ui->lineEdit->text().trimmed()
            + "' and passwd = '"+ ui->lineEdit_2->text() + "'";
    query.exec(sql);

    if (query.next())
    {
        //登录成功
        personidString = query.value(0).toString();

        currentTableModel->setTable("address");
        currentTableModel->setFilter("personid = '" + personidString + "'");
        currentTableModel->removeColumn(0);
        currentTableModel->removeColumn(0);
        currentTableModel->removeColumn(0);
        currentTableModel->select();

        currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("姓名"));
        currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("电话"));
        currentTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("固话"));
        currentTableModel->setHeaderData(3, Qt::Horizontal, QObject::tr("性别"));
        currentTableModel->setHeaderData(4, Qt::Horizontal, QObject::tr("生日"));
        currentTableModel->setHeaderData(5, Qt::Horizontal, QObject::tr("QQ"));
        currentTableModel->setHeaderData(6, Qt::Horizontal, QObject::tr("住址"));
        currentTableModel->setHeaderData(7, Qt::Horizontal, QObject::tr("备注"));

        currentView->setModel(currentTableModel);
        currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();

        ui->pushButton_3->show();
        ui->pushButton_4->show();
        ui->pushButton_5->show();
        ui->lineEdit_3->show();
        currentView->show();
    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),tr("user name or password error!"),QMessageBox::Yes);

        ui->lineEdit->clear();      //清空用户名输入框
        ui->lineEdit_2->clear();    //清空密码输入框
        return;
    }

    QPropertyAnimation *ani = new QPropertyAnimation(currentView, "pos");
    ani->setDuration(1000);
    ani->setStartValue(QPoint(this->width(), 121));
    ani->setEndValue(QPoint(10, 121));
    ani->setEasingCurve(QEasingCurve::OutBounce);
    ani->start();

    ani = new QPropertyAnimation(ui->pushButton_3, "pos");
    ani->setDuration(1000);
    ani->setStartValue(QPoint(this->width(), 60));
    ani->setEndValue(QPoint(460, 60));
    ani->setEasingCurve(QEasingCurve::OutBounce);
    ani->start();

    ani = new QPropertyAnimation(ui->pushButton_4, "pos");
    ani->setDuration(1000);
    ani->setStartValue(QPoint(this->width(), 60));
    ani->setEndValue(QPoint(580, 60));
    ani->setEasingCurve(QEasingCurve::OutBounce);
    ani->start();

    ani = new QPropertyAnimation(ui->pushButton_5, "pos");
    ani->setDuration(1000);
    ani->setStartValue(QPoint(this->width(), 481));
    ani->setEndValue(QPoint(552, 481));
    ani->setEasingCurve(QEasingCurve::OutBounce);
    ani->start();

    ani = new QPropertyAnimation(ui->lineEdit_3, "pos");
    ani->setDuration(1000);
    ani->setStartValue(QPoint(this->width(), 481));
    ani->setEndValue(QPoint(11, 481));
    ani->setEasingCurve(QEasingCurve::OutBounce);
    ani->start();
}

void mainDialog::on_pushButton_2_clicked()
{
    //注册
    logonw.show();
}

void mainDialog::on_pushButton_3_clicked()
{
    //添加
    neww.personidString = personidString;
    neww.show();
}

void mainDialog::on_pushButton_4_clicked()
{
    //删除
    QSqlQuery query;
    int curRow = currentView->currentIndex().row();
    if(curRow == -1)
    {
        return;
    }
    query.exec("delete from address where personid = '" + personidString + "'"
               + " and aname = '" + currentTableModel->index(curRow, 0).data().toString() + "'" +
               + " and aphone = '" + currentTableModel->index(curRow, 1).data().toString() + "'" +
               + " and atelephone = '" + currentTableModel->index(curRow, 2).data().toString() + "'" +
               + " and aage = '" + currentTableModel->index(curRow, 3).data().toString() + "'" +
               + " and abirth = '" + currentTableModel->index(curRow, 4).data().toString() + "'" +
               + " and aqq = '" + currentTableModel->index(curRow, 5).data().toString() + "'" +
               + " and aaddress = '" + currentTableModel->index(curRow, 6).data().toString() + "'" +
               + " and anote = '" + currentTableModel->index(curRow, 7).data().toString() + "'" +
               + ""
               );

    init();
    QMessageBox::information(NULL, "success", "删除成功!");
}

void mainDialog::on_tableView_doubleClicked(const QModelIndex &index)
{
    //修改
    QSqlQuery query;
    int curRow = currentView->currentIndex().row();
    if(curRow == -1)
    {
        return;
    }
    query.exec("select * from address where personid = '" + personidString + "'"
               + " and aname = '" + currentTableModel->index(curRow, 0).data().toString() + "'" +
               + " and aphone = '" + currentTableModel->index(curRow, 1).data().toString() + "'" +
               + " and atelephone = '" + currentTableModel->index(curRow, 2).data().toString() + "'" +
               + " and aage = '" + currentTableModel->index(curRow, 3).data().toString() + "'" +
               + " and abirth = '" + currentTableModel->index(curRow, 4).data().toString() + "'" +
               + " and aqq = '" + currentTableModel->index(curRow, 5).data().toString() + "'" +
               + " and aaddress = '" + currentTableModel->index(curRow, 6).data().toString() + "'" +
               + " and anote = '" + currentTableModel->index(curRow, 7).data().toString() + "'" +
               + ""
               );
    while(query.next())
    {
        modw.addressidString = query.value(0).toString();
    }
    modw.personidString = personidString;
    modw.show();
}

void mainDialog::on_pushButton_5_clicked()
{
    //按照名字查询
    currentTableModel->setTable("address");
    currentTableModel->setFilter("personid = '" + personidString + "' and aname like '%" + ui->lineEdit_3->text() + "%'");
    currentTableModel->removeColumn(0);
    currentTableModel->removeColumn(0);
    currentTableModel->removeColumn(0);
    currentTableModel->select();

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("姓名"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("电话"));
    currentTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("固话"));
    currentTableModel->setHeaderData(3, Qt::Horizontal, QObject::tr("性别"));
    currentTableModel->setHeaderData(4, Qt::Horizontal, QObject::tr("生日"));
    currentTableModel->setHeaderData(5, Qt::Horizontal, QObject::tr("QQ"));
    currentTableModel->setHeaderData(6, Qt::Horizontal, QObject::tr("住址"));
    currentTableModel->setHeaderData(7, Qt::Horizontal, QObject::tr("备注"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
