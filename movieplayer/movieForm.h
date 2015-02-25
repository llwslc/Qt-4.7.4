#ifndef MOVIEFORM
#define MOVIEFORM

#include <QtGui>
class MovieForm:public QWidget
{
    Q_OBJECT
public:
    MovieForm(QWidget *parent=0);
    ~MovieForm();
    void play(QString fileName);

    void paintEvent(QPaintEvent *);

private slots:
    void next();
    void pre();
    void pause();
    void stop();
    void changeVolume(int);
    void setSpeed();
    void dataRecieve();
    void sliderReleased();
    void sliderPressed();
    void valueChanged(int);
    void mplayerEnded(int,QProcess::ExitStatus);
    void jumpByTime();
    void sureBtnClicked();
    void playListItem(QListWidgetItem *);
    void add();
    void del();
protected:
    void closeEvent(QCloseEvent *);
private:
    QLabel *view;
    QLabel *timeLabel;
    QLabel *percentLabel;
    QFrame *frame;
    QPushButton *playBtn;
    QPushButton *preBtn;
    QPushButton *nextBtn;
    QPushButton *timeBtn;
    QSlider *currentlBar;
    QPushButton *stopBtn;
    QSlider *volumeSlider;
    QLabel *view_2;
    QCheckBox *fullBox;
    QPushButton *speedBtn;
    QListWidget *list;
    QProcess *p;
    QString currentStr;
    QString currentPercent;
    QString totalTime;
    QString fileName;

    QSpinBox *minBox;
    QSpinBox *secBox;

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QAction *openFileAction;
    QAction *openURLAction;
    QMenu *playMenu;
    QMenu *modeMenu;
    QAction *singleAction;
    QAction *circleAction;
    QAction *randAction;
    QAction *seqAction;
    QPushButton *addBtn, *delBtn;

    int sliderFlag;
};


#endif
