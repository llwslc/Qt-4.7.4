#include "mapdialog.h"
#include "ui_mapdialog.h"

mapDialog::mapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mapDialog)
{
    ui->setupUi(this);

    QFile file(":/map.html");
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(NULL, "Unable to open file", file.errorString());
    }
    QTextStream out(&file);
    QString output = out.readAll();

    ui->webView->setHtml(output);
}

mapDialog::~mapDialog()
{
    delete ui;
}
