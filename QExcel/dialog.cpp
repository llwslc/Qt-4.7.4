#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    timeUpdate = new QTimer(this);
    connect(timeUpdate, SIGNAL(timeout()), this, SLOT(updateTime()));
    timeUpdate->start(1*1000);

    autoRead = new QTimer(this);
    connect(autoRead, SIGNAL(timeout()), this, SLOT(readAuto()));
    autoRead->start(10*60*1000);

    autoReadFlag = 0;

    ui->label->clear();
    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(":/png/logo.png"));

    ui->label_2->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    ui->label_3->clear();
    ui->label_9->clear();
    ui->label_10->clear();

    stdModel = new QStandardItemModel();
    stdModel->setHorizontalHeaderItem(TBOPENCOMCOL, new QStandardItem(QObject::tr("单位名称")));
    stdModel->setHorizontalHeaderItem(TBOPENSALCOL, new QStandardItem(QObject::tr("当日产量")));
    stdModel->setHorizontalHeaderItem(TBOPENPROCOL, new QStandardItem(QObject::tr("当日销量")));
    stdModel->setHorizontalHeaderItem(TBOPENSTKCOL, new QStandardItem(QObject::tr("期末库存")));
    stdModel->setHorizontalHeaderItem(TBOPENTRACOL, new QStandardItem(QObject::tr("铁运")));
    stdModel->setHorizontalHeaderItem(TBOPENCARCOL, new QStandardItem(QObject::tr("汽运")));
    stdModel->setHorizontalHeaderItem(TBOPENREMCOL, new QStandardItem(QObject::tr("销售备注")));

    ui->tableView->setModel(stdModel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tableView->verticalHeader()->hide();

    connect(ui->tableView->selectionModel(),
            SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)),
            this, SLOT(tableViewRowChanged(const QModelIndex &, const QModelIndex &)));

    initDatabase();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::updateTime()
{
    ui->label_3->setText(QString(QDateTime::currentDateTime().toString("yyyy年MM月dd日 hh:mm:ss")));
    ui->label_3->setAlignment(Qt::AlignBottom | Qt::AlignRight);

    if(ui->timeEdit->time()<QTime::currentTime() && ui->timeEdit_2->time()>QTime::currentTime() && ui->checkBox->checkState())
    {
        autoReadFlag = 1;
    }
    else
    {
        autoReadFlag = 0;
    }
}

void Dialog::readAuto()
{
    if(autoReadFlag)
    {
        readXlsFunc();
        saveXlsFunc();
    }
    else
    {
    }
}

void Dialog::on_pushButton_clicked()
{
    //读取
    readXlsFunc();
    QMessageBox::information(NULL, "读取结束.", "读取成功!");

}

void Dialog::on_pushButton_2_clicked()
{
    //统计
    saveXlsFunc();
    QMessageBox::information(NULL, "汇总结束.", "汇总成功!");
}

void Dialog::readXlsFunc()
{
    //读取Excel函数
    int currentRow = 0;
    int sumRow = stdModel->rowCount();
    int sumXlsSheets = 0;
    QString openXlsName;
    QString comFilePath;
    QStringList xlsSheetName;
    QExcel *openXls = 0;

    query.exec("select * from filepathTb where filepathTbid = 1");
    while(query.next())
    {
        comFilePath = query.value(1).toString() + "\\";
    }

    while(sumRow--)
    {
        openXls = new QExcel;
        openXlsName = comFilePath + stdModel->index(currentRow, TBOPENCOMCOL).data().toString() + QDate::currentDate().toString("yyyy年M月d日") + ".xls";

        if(openXls->setXlsFilePath(openXlsName))
        {
            sumXlsSheets = openXls->getSheetsCount(); //获取工作表数目
            for(int i=1; i<=sumXlsSheets; i++)
            {
                openXls->selectSheet(i);
                xlsSheetName << openXls->getSheetName();
            }

            if(xlsSheetName.indexOf(QDate::currentDate().toString("d号")) == -1)
            {
                stdModel->setData(stdModel->index(currentRow, TBOPENPROCOL), "0");
                stdModel->setData(stdModel->index(currentRow, TBOPENSALCOL), "0");
                stdModel->setData(stdModel->index(currentRow, TBOPENSTKCOL), "0");
                stdModel->setData(stdModel->index(currentRow, TBOPENTRACOL), "0");
                stdModel->setData(stdModel->index(currentRow, TBOPENCARCOL), "0");
                stdModel->setData(stdModel->index(currentRow, TBOPENREMCOL), "");
            }
            else
            {
                openXls->selectSheet(QDate::currentDate().toString("d号"));

                stdModel->setData(stdModel->index(currentRow, TBOPENPROCOL), openXls->getCellValue(XLSOPENCOMROW, XLSOPENPROCOL).toString());
                stdModel->setData(stdModel->index(currentRow, TBOPENSALCOL), openXls->getCellValue(XLSOPENCOMROW, XLSOPENSALCOL).toString());
                stdModel->setData(stdModel->index(currentRow, TBOPENSTKCOL), openXls->getCellValue(XLSOPENCOMROW, XLSOPENSTKCOL).toString());
                stdModel->setData(stdModel->index(currentRow, TBOPENTRACOL), openXls->getCellValue(XLSOPENCOMROW, XLSOPENTRACOL).toString());
                stdModel->setData(stdModel->index(currentRow, TBOPENCARCOL), openXls->getCellValue(XLSOPENCOMROW, XLSOPENCARCOL).toString());
                stdModel->setData(stdModel->index(currentRow, TBOPENREMCOL), openXls->getCellValue(XLSOPENCOMROW, XLSOPENREMCOL).toString());
            }
        }
        else
        {
            stdModel->setData(stdModel->index(currentRow, TBOPENPROCOL), "0");
            stdModel->setData(stdModel->index(currentRow, TBOPENSALCOL), "0");
            stdModel->setData(stdModel->index(currentRow, TBOPENSTKCOL), "0");
            stdModel->setData(stdModel->index(currentRow, TBOPENTRACOL), "0");
            stdModel->setData(stdModel->index(currentRow, TBOPENCARCOL), "0");
            stdModel->setData(stdModel->index(currentRow, TBOPENREMCOL), "");
        }

        currentRow++;

        xlsSheetName.clear();
        delete openXls;
    }
    qDebug() << "读取结束";
    ui->label_9->setText("读取结束.");
}

void Dialog::saveXlsFunc()
{
    //汇总Excel函数
    int currentRow = 0;
    int sumRow = stdModel->rowCount();
    int saveRow = XLSSAVECOMROW;
    int saveSumXlsSheets = 0;
    int saveSheetIndex = 0;
    double sumSalPreNum = 0;
    double sumProPreNum = 0;
    QString saveXlsName;
    QString sumFilePath;
    QStringList xlsSheetName;
    QExcel *saveXls = 0;

    QString openXlsName;
    QExcel *openXls = 0;
    int openXlsFlag = 0;
    int openSumXlsSheets = 0;

    query.exec("select * from filepathTb where filepathTbid = 1");
    while(query.next())
    {
        sumFilePath = query.value(2).toString() + "\\";
    }

    saveXls = new QExcel;
    saveXlsName = sumFilePath + QString("澄合矿业有限公司") + QDate::currentDate().toString("yyyy年M月") + QString("产销存报表") + ".xls";

    if(saveXls->setXlsFilePath(saveXlsName))
    {
        //exist
    }
    else
    {
        //create file
        copyFileToPath(":/xls/sum.xls", saveXlsName, true);

        QFile fileChange(saveXlsName);
        fileChange.setPermissions(QFile::WriteOwner);

        if(saveXls->setXlsFilePath(saveXlsName))
        {
            //success
            saveSumXlsSheets = saveXls->getSheetsCount(); //获取工作表数目
            saveXls->setSheetName(saveSumXlsSheets, QDate::currentDate().toString("d号"));

            openXlsFlag = 1;
        }
        else
        {
            QMessageBox::information(NULL, QString("失败"), QString("文件开打失败!"));

            delete saveXls;
            return;
        }
    }

    saveSumXlsSheets = saveXls->getSheetsCount(); //获取工作表数目
    if(saveSumXlsSheets==1 && saveXls->getSheetName(saveSumXlsSheets)==QDate::currentDate().toString("d号")) //新表
    {
        openXlsFlag = 1;
        openXls = new QExcel;
        openXlsName = sumFilePath + QString("澄合矿业有限公司") + QDate::currentDate().addMonths(-1).toString("yyyy年M月") + QString("产销存报表") + ".xls";
        if(openXls->setXlsFilePath(openXlsName))
        {
            //success
            openSumXlsSheets = openXls->getSheetsCount();
            openXls->selectSheet(openSumXlsSheets);
        }
        else
        {
            QMessageBox::information(NULL, QString("失败"), QString("文件开打失败!"));

            delete openXls;
            return;
        }
    }
    else
    {
        for(int i=1; i<=saveSumXlsSheets; i++)
        {
            saveXls->selectSheet(i);
            xlsSheetName << saveXls->getSheetName();
        }

        saveSheetIndex = xlsSheetName.indexOf(QDate::currentDate().toString("d号"));
        if(saveSheetIndex == -1)
        {
            //copy
            saveXls->copySheet(saveSumXlsSheets, saveSumXlsSheets+1);
            saveXls->setSheetName(saveSumXlsSheets+1, QDate::currentDate().toString("d号"));

            saveSheetIndex = saveSumXlsSheets+1;
        }
        else
        {
            //find
            saveSheetIndex++;
        }
    }

    saveXls->selectSheet(QDate::currentDate().toString("d号"));
    saveXls->setCellString(XLSSAVETIMROW, XLSSAVETIMCOL, QString("澄合矿业有限公司") + QDate::currentDate().toString("yyyy年M月d日") + QString("产销存报表"));

    while(sumRow--)
    {
        saveXls->setCellString(saveRow, XLSSAVECOMCOL, stdModel->index(currentRow, TBOPENCOMCOL).data().toString());
        saveXls->setCellString(saveRow, XLSSAVESALCOL, stdModel->index(currentRow, TBOPENSALCOL).data().toString());
        saveXls->setCellString(saveRow, XLSSAVEPROCOL, stdModel->index(currentRow, TBOPENPROCOL).data().toString());
        saveXls->setCellString(saveRow, XLSSAVESTKCOL, stdModel->index(currentRow, TBOPENSTKCOL).data().toString());
        saveXls->setCellString(saveRow, XLSSAVETRACOL, stdModel->index(currentRow, TBOPENTRACOL).data().toString());
        saveXls->setCellString(saveRow, XLSSAVECARCOL, stdModel->index(currentRow, TBOPENCARCOL).data().toString());
        saveXls->setCellString(saveRow, XLSSAVEREMCOL, stdModel->index(currentRow, TBOPENREMCOL).data().toString());

        if(openXlsFlag == 0)
        {
            saveXls->selectSheet(saveSheetIndex-1);
            sumSalPreNum = saveXls->getCellValue(saveRow, XLSSAVESSLCOL).toDouble();
            sumProPreNum = saveXls->getCellValue(saveRow, XLSSAVESPRCOL).toDouble();
            saveXls->selectSheet(saveSheetIndex);
        }
        else
        {
            sumSalPreNum = openXls->getCellValue(saveRow, XLSSAVESSLCOL).toDouble();
            sumProPreNum = openXls->getCellValue(saveRow, XLSSAVESPRCOL).toDouble();
        }

        saveXls->setCellString(saveRow, XLSSAVESSLCOL, QString::number(stdModel->index(currentRow, TBOPENSALCOL).data().toDouble()+sumSalPreNum, 'f', 6));
        saveXls->setCellString(saveRow, XLSSAVESPRCOL, QString::number(stdModel->index(currentRow, TBOPENPROCOL).data().toDouble()+sumProPreNum, 'f', 6));

        currentRow++;
        saveRow++;

        sumSalPreNum = 0;
        sumProPreNum = 0;
    }
    xlsSheetName.clear();

    for(int i=saveRow; i<XLSSAVEENDROW; i++)
    {
        saveXls->setCellString(i, XLSSAVECOMCOL, QString(""));
        saveXls->setCellString(i, XLSSAVESALCOL, QString(""));
        saveXls->setCellString(i, XLSSAVEPROCOL, QString(""));
        saveXls->setCellString(i, XLSSAVESTKCOL, QString(""));
        saveXls->setCellString(i, XLSSAVEREMCOL, QString(""));
        saveXls->setCellString(i, XLSSAVESSLCOL, QString(""));
        saveXls->setCellString(i, XLSSAVESPRCOL, QString(""));
    }

    saveXls->setCellString(XLSSAVEENDROW, XLSSAVEREMCOL, QString(""));

    saveXls->save();
    delete saveXls;

    if(openXlsFlag)
    {
        delete openXls;
    }
    qDebug() << "统计结束";
    ui->label_10->setText("汇总结束.");
}

void Dialog::on_pushButton_6_clicked()
{
    //选择单位文件夹
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    if(dir.length() == 0) {
    } else {
        ui->lineEdit->setText(dir);

        query.exec("update filepathTb set filepathcom = '" + dir + "' where filepathTbid = 1");
    }
}

void Dialog::on_pushButton_7_clicked()
{
    //选择汇总文件夹
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    if(dir.length() == 0) {
    } else {
        ui->lineEdit_2->setText(dir);

        query.exec("update filepathTb set filepathsum = '" + dir + "' where filepathTbid = 1");
    }
}

void Dialog::on_pushButton_3_clicked()
{
    //添加单位
    int rowNum = stdModel->rowCount(); //获得表的行数

    if(ui->lineEdit_3->text().trimmed().length() == 0)
    {
        return;
    }
    else
    {
        if(stdModel->findItems(ui->lineEdit_3->text().trimmed()).size())
        {
            return;
        }
        else
        {
            stdModel->insertRow(rowNum); //添加一行
            stdModel->setData(stdModel->index(rowNum, TBOPENCOMCOL), ui->lineEdit_3->text().trimmed());

            rowNum = 0;
            query.exec("select unitTbid from unitTb");
            while(query.next())
            {
                rowNum = query.value(0).toInt() + 1;
            }

            query.exec("insert into unitTb values('" + QString::number(rowNum, 10) + "', '" + ui->lineEdit_3->text().trimmed() + "')");
        }
    }
}

void Dialog::on_pushButton_4_clicked()
{
    //修改单位
    query.exec("update unitTb set name = '" + ui->lineEdit_3->text().trimmed() + "' where name = '" + stdModel->index(ui->tableView->currentIndex().row(), 0).data().toString() + "'");

    stdModel->setData(stdModel->index(ui->tableView->currentIndex().row(), TBOPENCOMCOL), ui->lineEdit_3->text().trimmed());
}

void Dialog::on_pushButton_8_clicked()
{
    //删除单位
    query.exec("delete from unitTb where name = '" + stdModel->index(ui->tableView->currentIndex().row(), 0).data().toString() + "'");

    stdModel->removeRow(ui->tableView->currentIndex().row());
}

void Dialog::tableViewRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    //列表单击
    int curRow = ui->tableView->currentIndex().row(); //获取选中的行
    ui->lineEdit_3->setText(stdModel->index(curRow, 0).data().toString());
}

void Dialog::on_timeEdit_editingFinished()
{
    //前时间编辑完成
    if(ui->timeEdit_2->time() > ui->timeEdit->time())
    {
    }
    else
    {
        ui->timeEdit_2->setTime(ui->timeEdit->time().addSecs(1*60*60));
    }

    query.exec("update timeTb set timepre = '" + ui->timeEdit->time().toString("hh:mm:ss") + "' where timeTbid = '1'");
    query.exec("update timeTb set timenext = '" + ui->timeEdit_2->time().toString("hh:mm:ss") + "' where timeTbid = '1'");

    query.exec("select * from timeTb where timeTbid = 1");
    while(query.next())
    {
        ui->timeEdit->setTime(QTime::fromString(query.value(1).toString(), "hh:mm:ss"));
        ui->timeEdit_2->setTime(QTime::fromString(query.value(2).toString(), "hh:mm:ss"));
    }
}

void Dialog::on_timeEdit_2_editingFinished()
{
    //后时间编辑完成
    if(ui->timeEdit_2->time() > ui->timeEdit->time())
    {
    }
    else
    {
        ui->timeEdit_2->setTime(ui->timeEdit->time().addSecs(1*60*60));
    }

    query.exec("update timeTb set timenext = '" + ui->timeEdit_2->time().toString("hh:mm:ss") + "' where timeTbid = '1'");

    query.exec("select * from timeTb where timeTbid = 1");
    while(query.next())
    {
        ui->timeEdit_2->setTime(QTime::fromString(query.value(2).toString(), "hh:mm:ss"));
    }
}

void Dialog::on_checkBox_clicked()
{
    //自动读取点击
    query.exec("update timeTb set role = '" + QString::number(ui->checkBox->checkState(), 10) + "' where timeTbid = '1'");

    query.exec("select * from timeTb where timeTbid = 1");
    while(query.next())
    {
        ui->checkBox->setChecked(query.value(3).toInt());
    }
}

void Dialog::initDatabase()
{
    //初始化面板
    query.exec("select * from filepathTb where filepathTbid = 1");
    while(query.next())
    {
        ui->lineEdit->setText(query.value(1).toString());
        ui->lineEdit_2->setText(query.value(2).toString());
    }

    query.exec("select * from timeTb where timeTbid = 1");
    while(query.next())
    {
        ui->timeEdit->setTime(QTime::fromString(query.value(1).toString(), "hh:mm:ss"));
        ui->timeEdit_2->setTime(QTime::fromString(query.value(2).toString(), "hh:mm:ss"));
        ui->checkBox->setChecked(query.value(3).toInt());
    }

    int rowNum = 0;
    query.exec("select * from unitTb");
    while(query.next())
    {
        rowNum = stdModel->rowCount(); //获得表的行数
        stdModel->insertRow(rowNum); //添加一行
        stdModel->setData(stdModel->index(rowNum, TBOPENCOMCOL), query.value(1).toString());
    }

}
