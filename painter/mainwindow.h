#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_mainwindow.h"
#include "paintarea.h" 
#include <QScrollArea> 
#include<QComboBox>
extern QRgb backColor; 
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent *event) ;
    void creatColorComboBox(QComboBox *comboBox);
    void doNew();
    void doOpen();
    bool doFileSave();
    bool doFileSaveAs();
    void changeEvent(QEvent *e);
public slots :
    void on_action_N_triggered();
    void on_action_O_triggered() ;
    void on_action_S_triggered() ;
    void on_action_C_triggered() ;
    void on_action_W_triggered();
    void on_action_R_triggered() ;
    void on_action_A_triggered() ;
    void on_action_Eraser_triggered() ;
    void on_action_triggered() ;
    void on_shapecomboBox_currentIndexChanged(QString shape) ;
    void on_penstylecomboBox_currentIndexChanged(QString style);
    void on_penwidthspinBox_valueChanged(int width) ;
    void on_pencolorcomboBox_currentIndexChanged(int index) ;
    void on_brushcolorcomboBox_currentIndexChanged(int index);
    void on_action_K_triggered();
private:
    Ui::MainWindowClass *ui;
    PaintArea *area;
    QScrollArea *scrollArea;
    bool isSaved;
    QString curFile;
    bool maybeSave();
    bool saveFile(QString fileName);   

};

#endif 
