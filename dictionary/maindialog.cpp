#include "maindialog.h"
#include "ui_maindialog.h"

mainDialog::mainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainDialog)
{
    ui->setupUi(this);

    networkAccessManager = new QNetworkAccessManager(this);
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(Finish(QNetworkReply *)));


    dictionTableModel = new QSqlTableModel(this);
    dictionView = ui->tableView_2;

    myWordTableModel = new QSqlTableModel(this);
    myWordView = ui->tableView;

    dictionTableModel->setTable("dictionary");
    dictionTableModel->removeColumn(0);
    dictionTableModel->select();
    dictionView->setModel(dictionTableModel);
    dictionView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView* headerView = dictionView->verticalHeader();
    headerView->setHidden(true);

    myWordTableModel->setTable("myword");
    myWordTableModel->setFilter("userid = '" + userid + "'");
    myWordTableModel->removeColumn(0);
    myWordTableModel->removeColumn(0);
    myWordTableModel->select();
    myWordView->setModel(myWordTableModel);
    myWordView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    headerView = myWordView->verticalHeader();
    headerView->setHidden(true);

    ui->lineEdit->clear();
}

mainDialog::~mainDialog()
{
    delete ui;
}

void mainDialog::showEvent(QShowEvent *)
{
    //显示
    myWordTableModel->setFilter("userid = '" + userid + "'");
    myWordTableModel->select();
}

void mainDialog::on_tableView_doubleClicked(const QModelIndex &index)
{
    //生词
    int curRow = index.row(); //获取选中的行
    myWordString = myWordTableModel->index(curRow, 0).data().toString();
    QString html = QString("http://hanyu.dict.cn/" + myWordString);
    ui->webView->setUrl(QUrl(html));
}

void mainDialog::on_tableView_2_doubleClicked(const QModelIndex &index)
{
    //词典
    int curRow = index.row(); //获取选中的行
    myWordString = dictionTableModel->index(curRow, 0).data().toString();
    QString html = QString("http://hanyu.dict.cn/" + myWordString);
    ui->webView->setUrl(QUrl(html));
}

void mainDialog::Finish(QNetworkReply *networkReply)
{
    //查询完成
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString all = codec->toUnicode(networkReply->readAll());
    networkReply->deleteLater();

    qDebug() << all << endl;
}

void mainDialog::on_pushButton_clicked()
{
    //查询
    myWordString = ui->lineEdit->text();
    QString html = QString("http://hanyu.dict.cn/" + myWordString);

    qDebug() << html << endl;
    //networkAccessManager->get(QNetworkRequest(QUrl(html)));

    ui->webView->setUrl(QUrl(html));
}

void mainDialog::on_pushButton_2_clicked()
{
    //添加到生词
    QSqlQuery query;
    int idNum = 0;

    query.exec("select myword from myword");
    while(query.next())
    {
        if(myWordString == query.value(0).toString())
        {
            QMessageBox::information(NULL, "fail", "word repeat!");
            return;
        }
    }

    query.exec("select mywordid from myword");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    query.exec("insert into myword values('" + QString::number(idNum, 10) + "', '"
               + userid + "', '"
               + myWordString + "')");

    myWordTableModel->setFilter("userid = '" + userid + "'");
    myWordTableModel->select();
    QMessageBox::information(NULL, "success", "add success!");
}

void mainDialog::on_pushButton_3_clicked()
{
    //删除该生词
    QSqlQuery query;
    query.exec("delete from myword where myword = '" + myWordString + "'");

    myWordTableModel->setFilter("userid = '" + userid + "'");
    myWordTableModel->select();

    QMessageBox::information(NULL, "success", "delete success!");
}

void mainDialog::on_pushButton_4_clicked()
{
    //学习词典
    int idNum = qrand() % 500 + 1;
    QSqlQuery query;

    query.exec("select myword from dictionary where dictionaryid = " + QString::number(idNum, 10));
    while(query.next())
    {
        myWordString = query.value(0).toString();
    }

    QString html = QString("http://hanyu.dict.cn/" + myWordString);

    ui->webView->setUrl(QUrl(html));
}
