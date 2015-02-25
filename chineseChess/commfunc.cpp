#include "commfunc.h"

int chessGameOver;

//创建文件夹
bool createFolder(const QString dir)
{
    QDir *temp = new QDir;
    bool exist = temp->exists(dir);
    if(exist)
        qDebug() << "文件夹已存在" << endl;
    else
    {
        bool ok = temp->mkdir(dir);
        if(ok)
            qDebug() << "文件夹创建成功" << endl;
    }

    return true;
}

void chessmanDataFromFile(QString fileData, int chessmanData[10][9])
{
    qDebug() << fileData << fileData.size() << endl;
    int i = 0;
    int j = 0;

    for(i=0; i<10; i++)
        for(j=0; j<9; j++)
        {
            chessmanData[i][j] = fileData.at(9*i+j).unicode()-NUMTOUNICODE;
            qDebug() << i << j << 9*i+j << endl;
        }
}

QString chessmanDataToFile(const int chessmanData[10][9])
{
    int i = 0;
    int j = 0;
    QString fileData = "";

    for(i=0; i<10; i++)
        for(j=0; j<9; j++)
            fileData += QString(QChar(chessmanData[i][j]+NUMTOUNICODE));

    qDebug() << fileData.size() << endl;
    return fileData;
}

void gameIsOver(int position[10][9])
{
    int i,j;
    bool RedLive = FALSE,BlackLive = FALSE;
    //检查红方九宫是否有将帅
    for(i = 7;i < 10; i++)
    {
        for(j = 3; j < 6; j++)
        {
            if(position[i][j] == B_KING)
                BlackLive = TRUE;
            if(position[i][j] == R_KING)
                RedLive = TRUE;
        }
    }
    //检查黑方九宫是否有将帅
    for(i = 0; i < 3; i++)
    {
        for(j = 3; j < 6; j++)
        {
            if(position[i][j] == B_KING)
                BlackLive = TRUE;
            if(position[i][j] == R_KING)
                RedLive = TRUE;
        }
    }

    chessGameOver = 0;
    if(!RedLive)	//红将不在了
    {
        chessGameOver = 1;
    }
    if(!BlackLive)
    {
        chessGameOver = 2;
    }
}

