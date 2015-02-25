#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include "ui_chatdialog.h"
#include "client.h"
#include "common.h"

class ChatDialog : public QDialog, private Ui::ChatDialog
{
    Q_OBJECT

public:
    ChatDialog(QWidget *parent = 0);

    void linkSendMessage(const QString &messageStr);
    QString linkGetMessage(const QString &from, const QString &message);
    QString linkGetName();

signals:
    void linkGamePlayerOne();
    void linkGamePlayerTwo();
    void linkGameStart();
    void linkGameAgree();
    void linkGameLevel();
    void linkGameServer();
    void linkGameClient();
    void linkGameProgressBar();
    void linkGameOver();

public slots:
    void appendMessage(const QString &from, const QString &message);

private slots:
    void returnPressed();
    void newParticipant(const QString &nick);
    void participantLeft(const QString &nick);
    void showInformation();

private:
    Client client;
    QString myNickName;
    QString yourNickName;
    QString getMessage;
    QTextTableFormat tableFormat;
};

#endif
