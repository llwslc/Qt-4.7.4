#include "adminwidget.h"
#include "ui_adminwidget.h"

adminWidget::adminWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminWidget)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;
    metaInformationResolver = new Phonon::MediaObject(this);
    connect(metaInformationResolver, SIGNAL(metaDataChanged()),
            this, SLOT(mataDataChanged()));

    on_pushButton_clicked();
}

adminWidget::~adminWidget()
{
    delete ui;
}

void adminWidget::on_pushButton_clicked()
{
    //歌曲库
    currentTableModel->setTable("songsLibrary");
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    songOrMember = true;
}

void adminWidget::on_pushButton_2_clicked()
{
    //会员管理
    currentTableModel->setTable("member");
    currentTableModel->select(); //选取整个表的所有行

    songOrMember = false;
}

void adminWidget::on_pushButton_3_clicked()
{
    //添加
    int rowNum = currentTableModel->rowCount(); //获得表的行数
    int id = currentTableModel->record(rowNum - 1).value(0).toInt() + 1;
    currentTableModel->insertRow(rowNum); //添加一行
    currentTableModel->setData(currentTableModel->index(rowNum, 0), id);

    if(songOrMember)
    {
        //歌曲库
        sourcePath = QFileDialog::getOpenFileName(this, tr("Open mp3"), ".", tr("Image Files(*.mp3)"));
        if(sourcePath.length() == 0) {
            QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
        } else {
            QMessageBox::information(NULL, tr("Path"), tr("You selected ") + sourcePath);
        }
       // metaInformationResolver->clear();
        metaInformationResolver->setCurrentSource(sourcePath);
        currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
    }
    else
    {
        currentView->setEditTriggers(QAbstractItemView::DoubleClicked);  //使其可编辑
    }
}

void adminWidget::on_pushButton_4_clicked()
{
    //删除
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行
}

void adminWidget::on_pushButton_5_clicked()
{
    //修改
    currentView->setEditTriggers(QAbstractItemView::DoubleClicked);  //使其可编辑
}

void adminWidget::on_pushButton_6_clicked()
{
    //提交
    currentTableModel->submitAll();
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
}

void adminWidget::mataDataChanged()
{
    QMap<QString, QString> metaData = metaInformationResolver->metaData();

    QString title = metaData.value("TITLE");
    if (title == "")
    {
        title = sourcePath;
        while(title.indexOf("/") != -1)
        {
            title = title.right(title.length()-title.indexOf("/")-1);
        }

        title.remove(".mp3", Qt::CaseInsensitive);
    }
    QString artist = metaData.value("ARTIST");
    if (artist == "")
        artist = "NOARTIST";

    QString targetPath = "songsLibrary/" + title + "-" + artist + ".mp3";
    qDebug() << targetPath << endl;

    int rowNum = currentTableModel->rowCount()-1; //获得表的行数
    currentTableModel->setData(currentTableModel->index(rowNum, 1), title);
    currentTableModel->setData(currentTableModel->index(rowNum, 2), artist);
    currentTableModel->setData(currentTableModel->index(rowNum, 3), 0);
    currentTableModel->setData(currentTableModel->index(rowNum, 4), targetPath);

    copyFileToPath(sourcePath, targetPath, true); //覆盖式复制

    currentTableModel->submitAll();
}

void adminWidget::on_pushButton_7_clicked()
{
    //退出登录
    this->close();
    emit returnDialog();
}

void adminWidget::paintEvent(QPaintEvent *)
{
    //背景图片
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/png/1.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
