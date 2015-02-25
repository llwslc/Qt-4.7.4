#ifndef TETRIXWINDOW_H
#define TETRIXWINDOW_H

#include <QWidget>
#include <QLCDNumber>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>
#include "tetrixboard.h"

class TetrixWindow : public QWidget
{
    Q_OBJECT
public:
    TetrixWindow();

private:
    QLabel *createLabel(const QString &text);

    TetrixBoard *board;
    QLabel *nextPieceLabel;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *topButton;
    QLCDNumber *levelLCD;
    QLCDNumber *scoreLCD;

    QRadioButton *easyRadio;
    QRadioButton *normalRadio;
    QRadioButton *hardRadio;
    QButtonGroup *radioGroup;

public slots:
    void setHard();

signals:
    void hardChanged(int hardSet);

};

#endif // TETRIXWINDOW_H
