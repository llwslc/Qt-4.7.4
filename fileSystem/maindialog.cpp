#include "maindialog.h"
#include "ui_maindialog.h"

mainDialog::mainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;


    QSqlQuery query;
    query.exec("delete from filepath");

    currentTableModel->setTable("filepath");
    currentTableModel->removeColumn(3);
    currentTableModel->removeColumn(2);
    currentTableModel->removeColumn(0);
    currentTableModel->select();
    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("文件"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    currentView->setColumnWidth(0, currentView->width());
    QHeaderView* headerView = currentView->verticalHeader();
    headerView->setHidden(true);

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();

    musicString = "'MP3', 'WAV', 'WMA'";
    picString = "'BMP', 'PCX', 'TIFF', 'GIF', 'JPEG', 'JPG', 'TGA', 'EXIF', 'FPX', 'SVG', 'PSD', 'CDR', 'PCD', 'DXF', 'UFO', 'EPS', 'AI', 'PNG', 'HDRI', 'RAW'";
    movieString = "'MP4', '3GP', 'AVI', 'MKV', 'WMV', 'MPG', 'VOB', 'FLV', 'SWF', 'MOV', 'RM', 'RMVB'";
}

mainDialog::~mainDialog()
{
    delete ui;
}

void mainDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/images/bg.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void mainDialog::on_pushButton_2_clicked()
{
    //选择目录
    QString fileDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    if(fileDir.length() == 0)
    {
        return;
    }
    else
    {
        ui->lineEdit->setText(fileDir);
    }

    QDir *dir = new QDir(fileDir);
    QFileInfoList fileInfo = dir->entryInfoList(QDir::Files);

    QSqlQuery query;
    query.exec("delete from filepath");

    for(int i=0; i<fileInfo.count(); i++)
    {
        query.exec("insert into filepath values('" + QString::number(i) +
                   "', '" + fileInfo.at(i).fileName() +
                   "', '" + fileInfo.at(i).suffix() +
                   "', '" + fileInfo.at(i).filePath() + "')");
    }
    currentTableModel->setTable("filepath");
    currentTableModel->removeColumn(3);
    currentTableModel->removeColumn(2);
    currentTableModel->removeColumn(0);
    currentTableModel->select();
    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("文件"));
}

void mainDialog::on_pushButton_3_clicked()
{
    //音乐文件
    currentTableModel->setTable("filepath");
    currentTableModel->removeColumn(3);
    currentTableModel->removeColumn(2);
    currentTableModel->removeColumn(0);
    currentTableModel->setFilter("suffix in (" + musicString + ")");
    currentTableModel->select();
    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("文件"));
}

void mainDialog::on_pushButton_4_clicked()
{
    //图片文件
    currentTableModel->setTable("filepath");
    currentTableModel->removeColumn(3);
    currentTableModel->removeColumn(2);
    currentTableModel->removeColumn(0);
    currentTableModel->setFilter("suffix in (" + picString + ")");
    currentTableModel->select();
    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("文件"));
}

void mainDialog::on_pushButton_5_clicked()
{
    //视频文件
    currentTableModel->setTable("filepath");
    currentTableModel->removeColumn(3);
    currentTableModel->removeColumn(2);
    currentTableModel->removeColumn(0);
    currentTableModel->setFilter("suffix in (" + movieString + ")");
    currentTableModel->select();
    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("文件"));
}

void mainDialog::on_pushButton_6_clicked()
{
    //其他文件
    currentTableModel->setTable("filepath");
    currentTableModel->removeColumn(3);
    currentTableModel->removeColumn(2);
    currentTableModel->removeColumn(0);
    currentTableModel->setFilter("suffix not in (" + musicString
                                 + ", " + picString
                                 + ", " + movieString + ")");
    currentTableModel->select();
    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("文件"));
}

void mainDialog::on_pushButton_7_clicked()
{
    //全部文件
    currentTableModel->setTable("filepath");
    currentTableModel->removeColumn(3);
    currentTableModel->removeColumn(2);
    currentTableModel->removeColumn(0);
    currentTableModel->select();
    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("文件"));
}

void mainDialog::on_pushButton_8_clicked()
{
    //拷贝当前文件
    QString fileDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    if(fileDir.length() == 0)
    {
        return;
    }

    int count = currentTableModel->rowCount();
    QSqlQuery query;
    for(int i=0; i<count; i++)
    {
        query.exec("select fullpath, filepath from filepath where filepath = ('" + currentTableModel->index(i, 0).data().toString() + "')");
        while(query.next())
        {
            copyFileToPath(query.value(0).toString(), fileDir + "\\" + query.value(1).toString(), true);
        }
    }
    QMessageBox::warning(this, tr("Success"), tr("copy over"));
    currentTableModel->select();
}

void mainDialog::on_pushButton_clicked()
{
    //登录人员管理
    userw.show();
}

void mainDialog::on_pushButton_9_clicked()
{
    //搜索
    currentTableModel->setTable("filepath");
    currentTableModel->removeColumn(3);
    currentTableModel->removeColumn(2);
    currentTableModel->removeColumn(0);
    currentTableModel->setFilter("filepath like '%" + ui->lineEdit_2->text().trimmed() + "%'");
    currentTableModel->select();
    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("文件"));
}
