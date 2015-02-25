#include "songtopdialog.h"
#include "ui_songtopdialog.h"

songTopDialog::songTopDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::songTopDialog)
{
    ui->setupUi(this);
    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    currentTableModel->setTable("songsLibrary");
    currentTableModel->select(); //选取整个表的所有行

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("歌曲名"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("艺术家"));
    currentTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("被点次数"));

    currentTableModel->removeColumn(4);
    currentTableModel->removeColumn(0);

    currentView->setModel(currentTableModel);
    currentView->sortByColumn(2);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
}

songTopDialog::~songTopDialog()
{
    delete ui;
}

void songTopDialog::paintEvent(QPaintEvent *)
{
    //背景图片
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/png/5.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
