#include "common.h"

int **chessmanData;

chessman::chessman()
{
    chessmanX = 0;
    chessmanY = 0;
    chessmanType = NOCHESSMAN;
}

void chessman::clear()
{
    chessmanX = 0;
    chessmanY = 0;
    chessmanType = NOCHESSMAN;
}

void chessman::set(int x, int y, int type)
{
    chessmanX = x;
    chessmanY = y;
    chessmanType = type;
}

int chessman::getX()
{
    return chessmanX;
}

int chessman::getY()
{
    return chessmanY;
}

int chessman::getType()
{
    return chessmanType;
}

bool chessman::typeExist()
{
    bool existFlag = false;
    if(chessmanType != 0)
    {
        //数据存在
        existFlag = true;
    }
    else
    {
        existFlag = false;
    }
    return existFlag;
}

bool operator == (const chessman& a,const chessman& b)
{
    return (a.chessmanType == b.chessmanType);
}

QTime gameTime;
int gameRole;
int onlineManLeft;

database::database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

bool database::opendb(QString dbname)
{
    db.setDatabaseName(dbname);
    if(!db.open())
    {
        qDebug("db file open error");
        return false;
    }
    return true;
}

void database::createtable()
{
    QStringList tables = db.tables();
    if (tables.contains("historyList", Qt::CaseInsensitive))
    {
        //如果上述表名已存在,则不需要再次创建
        //qDebug("table exsited\n");
    }
    else
    {
        QSqlQuery query;
        //创建人员表(编号,姓名,时间,类型)
        query.exec("create table historyList(historyListid int primary key, pname varchar, time varchar, role int)");
    }
}

void database::closedb()
{
    db.close();
}

void chessmanDataFromMessage(QString message)
{
    int i = 0;
    int j = 0;
    int manNum = 0;
    switch(gameRole)
    {
    case 0:
        //等级1
        manNum = LEVELONEMANNUM; //棋盘棋子个数 10*10 20*20 25*25
        break;
    case 1:
        manNum = LEVELTWOMANNUM;
        break;
    case 2:
        manNum = LEVELTHREEMANNUM;
        break;
    default:
        manNum = LEVELONEMANNUM;
        break;
    }

    chessmanData = new int* [manNum];
    for(i=0; i<manNum; i++)
        chessmanData[i] = new int[manNum];

    for(i=0; i<manNum; i++)
        for(j=0; j<manNum; j++)
            chessmanData[i][j] = message.at(4+manNum*i+j).unicode()-NUMTOUNICODE;
}

QString chessmanDataToMessage()
{
    int i = 0;
    int j = 0;
    QString message = "";
    int manNum = 0;
    switch(gameRole)
    {
    case 0:
        //等级1
        manNum = LEVELONEMANNUM; //棋盘棋子个数 10*10 20*20 25*25
        break;
    case 1:
        manNum = LEVELTWOMANNUM;
        break;
    case 2:
        manNum = LEVELTHREEMANNUM;
        break;
    default:
        manNum = LEVELONEMANNUM;
        break;
    }

    for(i=0; i<manNum; i++)
        for(j=0; j<manNum; j++)
            message += QString(QChar(chessmanData[i][j]+NUMTOUNICODE));

    return message;
}
