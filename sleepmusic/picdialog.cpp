#include "picdialog.h"
#include "ui_picdialog.h"

picDialog::picDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::picDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    currentTableModel->setTable("pic");
    currentTableModel->select();
    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

picDialog::~picDialog()
{
    delete ui;
}

void picDialog::showEvent(QShowEvent *)
{
    ui->label->clear();
}

void picDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/frame.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void picDialog::on_pushButton_clicked()
{
    //添加图片
    QString sourcePath = QFileDialog::getOpenFileName(this, tr("Open pic"), ".", tr("Image Files(*.jpg)"));
    if(sourcePath.length() == 0)
    {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
        return;
    }
    else
    {
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + sourcePath);
    }

    QString title = sourcePath;
    while(title.indexOf("/") != -1)
    {
        title = title.right(title.length()-title.indexOf("/")-1);
    }

    title.remove(".jpg", Qt::CaseInsensitive);

    QSqlQuery query;
    query.exec("select name from pic");
    while(query.next())
    {
        if(title == query.value(0).toString())
        {
            QMessageBox::information(NULL, tr("repeat"), tr("pic title repeat!"));
            return;
        }
    }

    QString targetPath = "pic/" + title + ".jpg";

    int rowNum = currentTableModel->rowCount(); //获得表的行数
    int id = currentTableModel->record(rowNum - 1).value(0).toInt() + 1;
    currentTableModel->insertRow(rowNum); //添加一行
    currentTableModel->setData(currentTableModel->index(rowNum, 0), id);
    currentTableModel->setData(currentTableModel->index(rowNum, 1), title);
    currentTableModel->setData(currentTableModel->index(rowNum, 2), targetPath);

    copyFileToPath(sourcePath, targetPath, true); //覆盖式复制

    currentTableModel->submitAll();

    emit addPic();
}

void picDialog::on_pushButton_2_clicked()
{
    //删除图片
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行

    emit addPic();
}

void picDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    QString picPath;
    int curRow = currentView->currentIndex().row(); //获取选中的行
    picPath = currentTableModel->index(curRow, 2).data().toString();

    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(picPath));
}
