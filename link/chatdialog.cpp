#include <QtGui>

#include "chatdialog.h"

ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    lineEdit_2->setFocusPolicy(Qt::StrongFocus);
    textEdit_2->setFocusPolicy(Qt::NoFocus);
    textEdit_2->setReadOnly(true);
    listWidget_2->setFocusPolicy(Qt::NoFocus);

    connect(lineEdit_2, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    connect(lineEdit_2, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    connect(&client, SIGNAL(newMessage(QString,QString)),
            this, SLOT(appendMessage(QString,QString)));
    connect(&client, SIGNAL(newParticipant(QString)),
            this, SLOT(newParticipant(QString)));
    connect(&client, SIGNAL(participantLeft(QString)),
            this, SLOT(participantLeft(QString)));

    myNickName = client.nickName();
    newParticipant(myNickName);
    tableFormat.setBorder(0);
    QTimer::singleShot(2 * 1000, this, SLOT(showInformation()));
}

void ChatDialog::appendMessage(const QString &from, const QString &message)
{
    if (from.isEmpty() || message.isEmpty())
        return;

    QTextCursor cursor(textEdit_2->textCursor());
    cursor.movePosition(QTextCursor::End);
    QTextTable *table = cursor.insertTable(1, 2, tableFormat);
    table->cellAt(0, 0).firstCursorPosition().insertText('<' + from + "> ");
    table->cellAt(0, 1).firstCursorPosition().insertText(message);
    QScrollBar *bar = textEdit_2->verticalScrollBar();
    bar->setValue(bar->maximum());

    linkGetMessage(from, message);
}

void ChatDialog::returnPressed()
{
    QString text = lineEdit_2->text();
    if (text.isEmpty())
        return;

    if (text.startsWith(QChar('/'))) {
        QColor color = textEdit_2->textColor();
        textEdit_2->setTextColor(Qt::red);
        textEdit_2->append(tr("! Unknown command: %1")
                           .arg(text.left(text.indexOf(' '))));
        textEdit_2->setTextColor(color);
    } else {
        client.sendMessage(text);
        appendMessage(myNickName, text);
    }

    lineEdit_2->clear();
}

void ChatDialog::newParticipant(const QString &nick)
{
    if (nick.isEmpty())
        return;

    QColor color = textEdit_2->textColor();
    textEdit_2->setTextColor(Qt::gray);
    textEdit_2->append(tr("* %1 has joined").arg(nick));
    textEdit_2->setTextColor(color);
    listWidget_2->addItem(nick);

    emit linkGamePlayerTwo();
}

void ChatDialog::participantLeft(const QString &nick)
{
    if (nick.isEmpty())
        return;

    QList<QListWidgetItem *> items = listWidget_2->findItems(nick,
                                                             Qt::MatchExactly);
    if (items.isEmpty())
        return;

    delete items.at(0);
    QColor color = textEdit_2->textColor();
    textEdit_2->setTextColor(Qt::gray);
    textEdit_2->append(tr("* %1 has left").arg(nick));
    textEdit_2->setTextColor(color);

    showInformation();
}

void ChatDialog::showInformation()
{
    if (listWidget_2->count() == 1)
    {
        emit linkGamePlayerOne();
    }
    else
    {
    }
}

void ChatDialog::linkSendMessage(const QString &messageStr)
{
    client.sendMessage(messageStr);
}

QString ChatDialog::linkGetMessage(const QString &from, const QString &message)
{
    qDebug() << message << endl;
    yourNickName = from;
    getMessage = message;
    QMessageBox::StandardButton rb;
    if(message == "game")
    {
        rb = QMessageBox::information(this, tr("game"),
                                      QString("<font color='red'>" + yourNickName + "</font> want play this game with you!"), QMessageBox::Yes|QMessageBox::No);
        if(rb == QMessageBox::Yes)
        {
            linkSendMessage("agree");
            emit linkGameClient();
        }
    }

    if(message == "agree")
    {
        rb = QMessageBox::information(this, tr("game"),
                                      QString("<font color='red'>" + yourNickName + "</font> agreed to play this game with you!"), QMessageBox::Yes);
        emit linkGameAgree();
    }

    if(message.indexOf("level") != -1)
    {
        gameRole = message.at(5).unicode()-NUMTOUNICODE;
        emit linkGameLevel();
    }

    if(message.indexOf("data") != -1)
    {
        chessmanDataFromMessage(message);
        emit linkGameStart();
    }

    if(message.indexOf("left") != -1)
    {
        onlineManLeft = message.at(4).unicode()-NUMTOUNICODE;
        emit linkGameProgressBar();
    }

    if(message == "win")
    {
        QMessageBox::information(this, tr("game"),
                                 QString("<font color='red'>" + yourNickName + "</font> win!"), QMessageBox::Yes|QMessageBox::No);

        emit linkGameOver();
    }

    return getMessage;
}

QString ChatDialog::linkGetName()
{
    return yourNickName;
}

