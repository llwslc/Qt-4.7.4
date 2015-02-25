#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "donewdialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPainter>
#include <QDebug>

extern QRgb backColor; 

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags) :
    QMainWindow(parent, flags),ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);

    //初始化
    setWindowTitle(tr("画图"));
    setWindowIcon(QIcon("image/Holiday.png"));
    setFixedSize(700,500);
    area = new PaintArea;
    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(area);
    scrollArea->widget()->setMinimumSize(800,600);
    setCentralWidget(scrollArea);
    curFile = tr("未命名.png");
    creatColorComboBox(ui->pencolorcomboBox);
    creatColorComboBox(ui->brushcolorcomboBox);
}

MainWindow::~MainWindow()
{
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::doOpen()
{
    //打开文件
    if (maybeSave())
    {
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("打开文件"), QDir::currentPath());
        if (!fileName.isEmpty())
        {
            area->openImage(fileName);
            scrollArea->widget()->resize(area->getImageSize());
            isSaved = true;
            curFile = fileName;
        }
    }
}

void MainWindow::doNew()
{
    //创建新文件
    if(maybeSave())
    {
        on_action_K_triggered();
        isSaved = false;
    }
}

bool MainWindow::maybeSave()
{
    //是否要保存
    if(area->isModified())
    {
        QMessageBox::StandardButton box;
        box = QMessageBox::warning(this,tr("保存文件"),tr("您想保存当前图片吗？"),
                                   QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if(box == QMessageBox::Yes)
        {
            return doFileSaveAs();
        }
        else if(box == QMessageBox::Cancel)
        {
            return false;
        }
    }
    return true;
}

bool MainWindow::doFileSave()
{
    //是否保存文件
    if(isSaved)
    {
        return saveFile(curFile);
    }
    else return doFileSaveAs();
}

bool MainWindow::saveFile(QString fileName)
{
    //保存文件函数
    if(area->saveImage(fileName,"png"))
    {
        isSaved = true;
        return true;
    }
    else return false;
}

bool MainWindow::doFileSaveAs()
{
    //另存为
    QString fileName = QFileDialog::getSaveFileName(this,tr("另存为"),curFile);
    if(fileName.isEmpty())
    {
        return false;
    }
    else return saveFile(fileName);
}

void MainWindow::on_action_N_triggered()
{
    //创建新文件的槽函数
    doNew();
}

void MainWindow::on_action_O_triggered() 
{
    //打开文件的槽函数
    doOpen();
}

void MainWindow::on_action_S_triggered()
{
    //保存文件的槽函数
    doFileSave();
}

void MainWindow::on_action_A_triggered()
{
    //另存为文件的槽函数
    doFileSaveAs();
}

void MainWindow::on_action_W_triggered()
{
    //程序关于的槽函数
    area->aboutus();
}

void MainWindow::on_action_triggered() 
{
    //是否保存的槽函数
    if(maybeSave())
        qApp->quit();
}

void MainWindow::closeEvent(QCloseEvent *event) 
{
    //窗口关闭的槽函数
    if(maybeSave())
        qApp->quit();
    else event->ignore();
}

void MainWindow::on_action_R_triggered()
{
    //旋转的槽函数
    area->doRotate();
}

void MainWindow::on_action_Eraser_triggered() 
{
    //橡皮擦的槽函数
    area->setShape(PaintArea::None);
    area->setPenWidth(8);
    area->setPenColor (qRgb(255,255,255));
}

void MainWindow::on_action_C_triggered() 
{
    //清空的槽函数
    area->doClear();
}

void MainWindow::creatColorComboBox(QComboBox *comboBox)
{
    //初始化一个颜色下拉框控件
    QPixmap pix(16,16);
    QPainter painter(&pix);
    painter.fillRect(0,0,16,16,Qt::black);
    comboBox->addItem(QIcon(pix),tr("黑色"),Qt::black);
    painter.fillRect(0,0,16,16,Qt::white);
    comboBox->addItem(QIcon(pix),tr("白色"),Qt::white);
    painter.fillRect(0,0,16,16,Qt::red);
    comboBox->addItem(QIcon(pix),tr("红色"),Qt::red);
    painter.fillRect(0,0,16,16,Qt::green);
    comboBox->addItem(QIcon(pix),tr("绿色"),Qt::green);
    painter.fillRect(0,0,16,16,Qt::blue);
    comboBox->addItem(QIcon(pix),tr("蓝色"),Qt::blue);
    painter.fillRect(0,0,16,16,Qt::yellow);
    comboBox->addItem(QIcon(pix),tr("黄色"),Qt::yellow);
    comboBox->addItem(tr("无颜色"),Qt::transparent);
}

void MainWindow::on_shapecomboBox_currentIndexChanged(QString shape) 
{
    //笔画的选择
    if(shape == tr("普通画笔"))
        area->setShape(PaintArea::None);
    else if(shape == tr("矩形"))
        area->setShape(PaintArea::Rectangle);
    else if(shape == tr("直线"))
        area->setShape(PaintArea::Line);
    else if(shape == tr("椭圆"))
        area->setShape(PaintArea::Ellipse);
    else if(shape == tr("三角形"))
        area->setShape(PaintArea::Triangle);
    else if(shape == tr("任意四边形"))
        area->setShape(PaintArea::Fourline);
}

void MainWindow::on_penstylecomboBox_currentIndexChanged(QString style) 
{
    //线条的选择
    if(style == tr("实线"))
    {
        area->setPenStyle(Qt::SolidLine);
    }
    else if(style == tr("点线"))
    {
        area->setPenStyle(Qt::DotLine);
    }
    else if(style == tr("长虚线"))
    {
        area->setPenStyle(Qt::DashLine);
    }
}

void MainWindow::on_penwidthspinBox_valueChanged(int width)
{
    //选择笔
    area->setPenWidth(width);
}

void MainWindow::on_pencolorcomboBox_currentIndexChanged(int index) 
{
    //笔颜色选择
    QColor color = ui->pencolorcomboBox->itemData(index,Qt::UserRole).value<QColor>();
    area->setPenColor(color);
}

void MainWindow::on_brushcolorcomboBox_currentIndexChanged(int index) 
{
    //填充颜色选择
    QColor color = ui->brushcolorcomboBox->itemData(index,Qt::UserRole).value<QColor>();
    area->setBrushColor(color);
}

void MainWindow::on_action_K_triggered() 
{
    //新的画布槽函数
    DoNewDialog dlg;
    dlg.show();
    if(dlg.exec()!=QDialog::Accepted)
        dlg.show();
    int width = dlg.getWidth();
    int height = dlg.getHeight();
    area->setImageSize(width,height);
    scrollArea->widget()->resize(width,height);
    area->setImageColor(dlg.getBackColor());
}
