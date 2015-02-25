#ifndef WARDROBEDIALOG_H
#define WARDROBEDIALOG_H

#include <QDialog>
#include "myfunc.h"

namespace Ui {
    class wardrobeDialog;
}

class wardrobeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit wardrobeDialog(QWidget *parent = 0);
    ~wardrobeDialog();

    void showEvent(QShowEvent *);

private slots:
    void initDialog();

    void on_comboBox_4_currentIndexChanged(int index);

    void on_comboBox_5_currentIndexChanged(int index);

private:
    Ui::wardrobeDialog *ui;
};

#endif // WARDROBEDIALOG_H
