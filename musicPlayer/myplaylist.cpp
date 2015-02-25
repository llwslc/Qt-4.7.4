#include "myplaylist.h"
#include <QContextMenuEvent>
#include <QMenu>


MyPlaylist::MyPlaylist(QWidget *parent) :
    QTableWidget(parent)
{
    //setWindowTitle(tr("播放列表"));
    //设置为一个独立的窗口，且只有一个关闭按钮
    //setWindowFlags(Qt::Window | Qt::WindowTitleHint);

    //resize(400, 400);
    //setMaximumWidth(400);
    //setMinimumWidth(400);//固定窗口大小

    //resize(parent->height(),
    //       parent->width());

    setRowCount(0);//初始的行数为0
    setColumnCount(3);//初始的列数为1

    //设置第一个标签
    QStringList list;
    list << tr("标题") << tr("歌手") << tr("长度");
    setHorizontalHeaderLabels(list);

    setSelectionMode(QAbstractItemView::SingleSelection);//设置只能选择单行
    setSelectionBehavior(QAbstractItemView::SelectRows);

    setShowGrid(false);//设置不显示网格
}


void MyPlaylist::clear_play_list()
{
    while(rowCount())
    {
        removeRow(0);
    }

    QSqlQuery query;
    query.exec("delete from music");

    emit play_list_clean();//删除完后，发送清空成功信号
}

void MyPlaylist::del_play_list()
{
    int curRow = currentIndex().row(); //获取选中的行

    QSqlQuery query;
    QString mtitle = item(curRow, 0)->data(Qt::DisplayRole).toString();
    QString msinger = item(curRow, 1)->data(Qt::DisplayRole).toString();
    QString mlength = item(curRow, 2)->data(Qt::DisplayRole).toString();
    query.exec("delete from music where mtitle = '" + mtitle + "' and msinger = '" + msinger + "' and mlength = '" + mlength + "'");

    removeRow(curRow); //删除该行

    emit play_list_delete(curRow);//删除完后，发送删除成功信号
}


void MyPlaylist::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu;
    menu.addAction(tr("删除歌曲"), this, SLOT(del_play_list()));//可以直接在这里指定槽函数
    menu.addAction(tr("清空列表"), this, SLOT(clear_play_list()));//可以直接在这里指定槽函数
    menu.exec(event->globalPos());//返回鼠标指针的全局位置
}


void MyPlaylist::closeEvent(QCloseEvent *event)
{
    if(isVisible()) {
        hide();
        event->ignore();//清零接收标志
    }
}
