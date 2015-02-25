#ifndef MYPLAYLIST_H
#define MYPLAYLIST_H

#include <QTableWidget>
#include "common.h"

class MyPlaylist : public QTableWidget
{
    Q_OBJECT
public:
    explicit MyPlaylist(QWidget *parent = 0);
    
signals:
    void play_list_clean();
    void play_list_delete(int);
    
public slots:

protected:
    void contextMenuEvent(QContextMenuEvent *);
    void closeEvent(QCloseEvent *);

private slots:
    void clear_play_list();
    void del_play_list();
    
};

#endif // MYPLAYLIST_H
