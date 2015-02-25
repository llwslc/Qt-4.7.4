#include "ordersdialog.h"
#include "ui_ordersdialog.h"

/*
您的申请已经获得批准。感谢您选择爱查快递为您提供的快递查询接口（API）服务。

我们分配给您使用的身份Key密匙为：9BD58D8642F528E792E4BF8EAA845AC8

每日调用上限为：1000次

备注：提供给您的KEY只限您和贵公司专用，请勿公开和外传。否者将取消您的API使用资格。

使用我们提供的快递查询API接口即代表同意爱查快递网的版权及免责条款。

调用方法和接口请参考我们网站上提供的详细说明。

-----------------------------------------

1、如有任何问题请及时与我们联络。

2、请您在页面下端加上“查询服务由爱查快递提供”字样（链接地址：http://www.ickd.cn）。

3、请在您网站的友情链接处加入我们的链接，对于未经许可自私撤下链接的我们将取消您的API资格（我们会定期检查链接的情况）。

相关链接：快递查询API说明（http://www.ickd.cn/api/doc.html），所支持的快递公司列表（http://www.ickd.cn/api/list.php），ShopEx和EcShop网店系统插件（http://www.ickd.cn/api/plugins.html）

------------------------------------------------------

API调用参考：

http://api.ickd.cn/?id=9BD58D8642F528E792E4BF8EAA845AC8&com=快递公司英文代码&nu=快递单号&type=html|text|json（具体参数见说明文档）

http://api.ickd.cn/?com=[]&nu=[]&id=[]&type=[]&encode=[]&ord=[]&lang=[]

*/

ordersDialog::ordersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ordersDialog)
{
    ui->setupUi(this);

    networkAccessManager = new QNetworkAccessManager(this);
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(Finish(QNetworkReply *)));

    model = new QStandardItemModel;
    model->setColumnCount(3);
    model->setHeaderData(0,Qt::Horizontal,"日期");
    model->setHeaderData(1,Qt::Horizontal,"地点");
    model->setHeaderData(2,Qt::Horizontal,"状态");
    ui->tableView->setShowGrid(true);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->verticalHeader()->setResizeMode(QHeaderView::Stretch);


    initComboBox();

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
}

ordersDialog::~ordersDialog()
{
    delete ui;
}

void ordersDialog::showEvent(QShowEvent *)
{
    initComboBox();

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
}

void ordersDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/jpg/3.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void ordersDialog::on_pushButton_clicked()
{
    //查询
    if(ui->lineEdit->text().length() == 0)
    {
        QMessageBox::information(NULL, "error", "express num is empty");
        return;
    }

    QString expressCodes;
    QSqlQuery query;
    query.exec("select codes from expresscom where expresscomid = '" + QString::number(ui->comboBox->currentIndex(), 10) + "'");
    while(query.next())
        expressCodes = query.value(0).toString();

    QString html = QString("http://api.ickd.cn/?id=9BD58D8642F528E792E4BF8EAA845AC8&com=" + expressCodes + "&nu=" + ui->lineEdit->text().trimmed() + "&type=text");

    qDebug() << html << endl;
    networkAccessManager->get(QNetworkRequest(QUrl(html)));
}

void ordersDialog::on_pushButton_3_clicked()
{
    //保存
    QSqlQuery query;
    int idNum = 0;

    query.exec("select ordersid from orders");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    query.exec("insert into orders values('" + QString::number(idNum, 10) + "', '"
               + ui->lineEdit->text().trimmed() + "', '"
               + QString::number(ui->comboBox->currentIndex(), 10) + "')");

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);

    initComboBox();
}

void ordersDialog::on_pushButton_2_clicked()
{
    //查询
    if(ui->comboBox_2->currentIndex() == 0)
    {
        QMessageBox::information(NULL, "error", "express num is empty");
        return;
    }

    QString expressCodes;
    QSqlQuery query;
    query.exec("select codes from expresscom where expresscomid = '" + QString::number(ui->comboBox->currentIndex(), 10) + "'");
    while(query.next())
        expressCodes = query.value(0).toString();

    QString html = QString("http://api.ickd.cn/?id=9BD58D8642F528E792E4BF8EAA845AC8&com=" + expressCodes + "&nu=" + ui->comboBox_2->currentText() + "&type=text");

    qDebug() << html << endl;
    networkAccessManager->get(QNetworkRequest(QUrl(html)));
}

void ordersDialog::on_pushButton_4_clicked()
{
    //删除
    QSqlQuery query;
    query.exec("delete from orders where ordernum = '" + ui->comboBox_2->currentText() + "'");

    initComboBox();
}


void ordersDialog::on_comboBox_2_currentIndexChanged(int index)
{
    //已有单号选择
    QSqlQuery query;

    query.exec("select express from orders where ordernum = '" + ui->comboBox_2->currentText() + "'");
    while(query.next())
    {
        ui->comboBox->setCurrentIndex(query.value(0).toInt());
    }
}

void ordersDialog::Finish(QNetworkReply *networkReply)
{
    //下载完成
    QTextCodec *codec=QTextCodec::codecForName("GBK");
    QString all=codec->toUnicode(networkReply->readAll());
    networkReply->deleteLater();

    model->clear();
    model->setColumnCount(3);
    model->setHeaderData(0,Qt::Horizontal,"日期");
    model->setHeaderData(1,Qt::Horizontal,"地点");
    model->setHeaderData(2,Qt::Horizontal,"状态");
    QStringList list=all.split("\n");
    foreach (QString temp, list) {
        QString time = temp.left(temp.indexOf("  "));
        temp = temp.mid(temp.indexOf("  ") + 2);
        QString place = temp.left(temp.indexOf(" "));
        temp = temp.mid(temp.indexOf(" ") + 1);
        QStandardItem *timeitem = new QStandardItem(time);
        QStandardItem *placeitem = new QStandardItem(place);
        QStandardItem *state = new QStandardItem(temp);
        QList<QStandardItem*> item;
        item << timeitem << placeitem << state;
        model->appendRow(item);
    }

    model->removeRow(model->rowCount()-1);

    qDebug() << all << model->rowCount() << endl;

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

void ordersDialog::initComboBox()
{
    //初始化下拉框
    QSqlQuery query;
    ui->comboBox->clear();
    ui->comboBox_2->clear();

    ui->comboBox_2->addItem("");

    query.exec("select name from expresscom");
    while(query.next())
        ui->comboBox->addItem(query.value(0).toString());

    query.exec("select ordernum from orders");
    while(query.next())
        ui->comboBox_2->addItem(query.value(0).toString());
}
