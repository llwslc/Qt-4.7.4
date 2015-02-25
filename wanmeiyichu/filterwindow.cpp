#include "filterwindow.h"
#include "ui_filterwindow.h"

filterWindow::filterWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::filterWindow)
{
    ui->setupUi(this);
}

filterWindow::~filterWindow()
{
    delete ui;
}

void filterWindow::showEvent(QShowEvent *)
{
    this->move(globaWindowsPos);   //调整窗口位置

    QSqlQuery query;
    QString filterStr;
    int filterInt = INTNUMBERINIT;
    int currentRow = INTNUMBERINIT;

    while(filterListWidget->rowCount())
        filterListWidget->removeRow(filterListWidget->rowCount()-INTNUMBERDECREMENT);

#ifdef DEBUGLEVELTWO
    qDebug() << "filterListWidget->rowCount() = " << filterListWidget->rowCount() << endl;
#endif

    if(typePressed != NOBUTTONPRESSED)
    {
        filterStr = "type";
        filterInt = typePressed;
    }
    else
    {
        //NULL
    }
    if(seasonPressed != NOBUTTONPRESSED)
    {
        filterStr = "season";
        filterInt = seasonPressed;
    }
    else
    {
        //NULL
    }
    if(classtypePressed != NOBUTTONPRESSED)
    {
        filterStr = "classtype";
        filterInt = classtypePressed;
    }
    else
    {
        //NULL
    }

#ifdef DEBUGLEVELTWO
    qDebug() << filterStr << filterInt << endl;
#endif

    query.exec("select * from clothes where " + filterStr + " = '" + QString::number(filterInt, NUMBERTOSTRINGBASE) + "'");
    while(query.next())
    {
        QTableWidgetItem *tableWidgetItem = new QTableWidgetItem(QTableWidgetItem::Type);
        tableWidgetItem->setIcon(QIcon(QPixmap(query.value(SQLCLOTHESPICPATHINDEX).toString()).scaled(FILTERLISTWIDGETPICWIDTH, FILTERLISTWIDGETPICHEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
        tableWidgetItem->setText(query.value(SQLCLOTHESIDNUMINDEX).toString());
        tableWidgetItem->setTextAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        currentRow = filterListWidget->rowCount();

#ifdef DEBUGLEVELTWO
        qDebug() << "currentRow" << currentRow << endl;
#endif

        if(currentRow == INTNUMBERINIT)
        {
            filterListWidget->insertRow(currentRow);
            filterListWidget->setRowHeight(currentRow, FILTERLISTWIDGETCOLUMNHEIGHT);
            filterListWidget->setIconSize(QSize(FILTERLISTWIDGETPICWIDTH, FILTERLISTWIDGETPICHEIGHT));
            filterListWidget->setItem(currentRow, FILTERLISTWIDGETITEMONE, tableWidgetItem);
        }
        else
        {
            currentRow--;
            if(filterListWidget->item(currentRow, FILTERLISTWIDGETITEMONE) == NULL)
            {
                filterListWidget->setItem(currentRow, FILTERLISTWIDGETITEMONE, tableWidgetItem);
            }
            else
            {
                if(filterListWidget->item(currentRow, FILTERLISTWIDGETITEMTWO) == NULL)
                {
                    filterListWidget->setItem(currentRow, FILTERLISTWIDGETITEMTWO, tableWidgetItem);
                }
                else
                {
                    if(filterListWidget->item(currentRow, FILTERLISTWIDGETITEMTHREE) == NULL)
                    {
                        filterListWidget->setItem(currentRow, FILTERLISTWIDGETITEMTHREE, tableWidgetItem);
                    }
                    else
                    {
                        currentRow++;
                        filterListWidget->insertRow(currentRow);
                        filterListWidget->setRowHeight(currentRow, FILTERLISTWIDGETCOLUMNHEIGHT);
                        filterListWidget->setIconSize(QSize(FILTERLISTWIDGETPICWIDTH, FILTERLISTWIDGETPICHEIGHT));
                        filterListWidget->setItem(currentRow, FILTERLISTWIDGETITEMONE, tableWidgetItem);
                    }
                }
            }
        }
    }
}

void filterWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(BKGPAINTERX, BKGPAINTERY, QPixmap(":/images/background.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void filterWindow::mousePressEvent(QMouseEvent *event)
{
    this->windowPos = this->pos();
    this->mousePos = event->globalPos();
    this->dPos = mousePos - windowPos;
}

void filterWindow::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - this->dPos);
}

void filterWindow::closeEvent(QCloseEvent *)
{
    globaWindowsPos = this->QWidget::pos();
}

void filterWindow::exitButton_clicked()
{
    this->close();
}

void filterWindow::filterListWidget_DoubleClicked(const QModelIndex &index)
{
    //筛选列表双击
    QSqlQuery query;
    int daydressIdNum = INTNUMBERINIT;
    QString daydressPicPathString;
    int selectFilterClothesIdNumInt = INTNUMBERINIT;

    if(filterListWidget->item(filterListWidget->currentRow(), filterListWidget->currentColumn()) == NULL)
    {
        //NULL
    }
    else
    {
        selectFilterClothesIdNumInt = filterListWidget->item(filterListWidget->currentRow(), filterListWidget->currentColumn())->text().toInt();

        query.exec("select * from daydress order by daydressid");
        while(query.next())
            daydressIdNum = query.value(SQLDAYDRESSIDNUMINDEX).toInt();

        daydressIdNum++;

        query.exec("select * from clothes where clothesid = '" + QString::number(selectFilterClothesIdNumInt, NUMBERTOSTRINGBASE) + "'");
        while(query.next())
            daydressPicPathString = query.value(SQLCLOTHESPICPATHINDEX).toString();

        query.exec("insert into daydress values('" + QString::number(daydressIdNum, NUMBERTOSTRINGBASE)
                   + "', '" + QString::number(selectFilterClothesIdNumInt, NUMBERTOSTRINGBASE)
                   + "', '" + QString::number(daydressColSelectInt, NUMBERTOSTRINGBASE)
                   + "', '" + daydressDateEdit->date().toString("yyyy.MM.dd")
                   + "', '" + daydressPicPathString
                   + "')");

        emit modifyDaydress();
        this->close();
    }
}
