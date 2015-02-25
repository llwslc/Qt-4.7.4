#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->progressBar->setValue(0);

    fileCount = 0;
    singerCount = 0;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    //选择文件夹
    sourcePath = QFileDialog::getExistingDirectory(this, tr("黄玉立.傻逼"), "", QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    if(sourcePath.length() == 0)
    {
        QMessageBox::information(NULL, tr("open"), tr("You didn't select any files."));
    }
    else
    {
        ui->lineEdit->setText(sourcePath);
    }
}

void Dialog::on_pushButton_2_clicked()
{
    //读取歌手
    ui->progressBar->setValue(0);
    QDir *dir = new QDir(sourcePath);
    QFileInfoList fileInfo = dir->entryInfoList();

    fileCount = fileInfo.count();
    qDebug() << fileCount;
    ui->tableWidget->setRowCount(fileCount);

    QString singerStr;
    QString songName;
    int tableCount = 0;

    for(int i=2; i<fileCount; i++)
    {
        songName = fileInfo.at(i).fileName();
        qDebug() << songName;
        singerStr = songName.left(songName.indexOf(" -"));
        qDebug() << singerStr;
        if(ui->tableWidget->findItems(singerStr, Qt::MatchExactly).isEmpty())
            ui->tableWidget->setItem(tableCount++, 0, new QTableWidgetItem(singerStr));
        ui->progressBar->setValue(100*i/(fileCount-1));
    }

    ui->tableWidget->setRowCount(tableCount);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    singerCount = tableCount;
    qDebug() << singerCount;
}

void Dialog::on_pushButton_3_clicked()
{
    //创建文件夹
    ui->progressBar->setValue(0);
    for(int i=0; i<singerCount; i++)
    {
        createFolder(sourcePath + QString("/") + ui->tableWidget->item(i, 0)->text());
        ui->progressBar->setValue(100*i/(singerCount-1));
    }
}

void Dialog::on_pushButton_4_clicked()
{
    //移动文件
    ui->progressBar->setValue(0);
    QDir *dir = new QDir(sourcePath);
    QStringList filter;
    filter << "*.*";

    QFileInfoList fileInfo = dir->entryInfoList(filter);

    fileCount = fileInfo.count();
    qDebug() << singerCount;

    QString singerStr;
    QString songName;
    QString songPath;
    QString targetPath;

    for(int i=2; i<fileCount; i++)
    {
        songName = fileInfo.at(i).fileName();
        songPath = fileInfo.at(i).filePath();
        singerStr = songName.left(songName.indexOf(" -"));
        targetPath = sourcePath + QString("/") + singerStr + QString("/") + songName;
        copyFileToPath(songPath, targetPath, true);
        ui->progressBar->setValue(100*i/(fileCount-1));
    }
}
