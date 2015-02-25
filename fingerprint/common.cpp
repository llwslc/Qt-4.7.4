#include "common.h"

//拷贝文件
bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist)
{
    toDir.replace("\\","/");
    if (sourceDir == toDir){
        return true;
    }
    if (!QFile::exists(sourceDir)){
        return false;
    }
    QDir *createfile = new QDir;
    bool exist = createfile->exists(toDir);
    if (exist){
        if(coverFileIfExist){
            createfile->remove(toDir);
        }
    }//end if

    if(!QFile::copy(sourceDir, toDir))
    {
        return false;
    }
    return true;
}

//拷贝文件夹
bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);
    if(!targetDir.exists()){    // 如果目标目录不存在，则进行创建
        if(!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isDir()){    // 当为目录时，递归的进行copy
            if(!copyDirectoryFiles(fileInfo.filePath(),
                                   targetDir.filePath(fileInfo.fileName()),
                                   coverFileIfExist))
                return false;
        }
        else{            // 当允许覆盖操作时，将旧文件进行删除操作
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
                targetDir.remove(fileInfo.fileName());
            }

            // 进行文件copy
            if(!QFile::copy(fileInfo.filePath(),
                            targetDir.filePath(fileInfo.fileName()))){
                return false;
            }
        }
    }
    return true;
}

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

//加密
QString Encrypt(QString s)
{
    QByteArray sourceStr = s.toAscii();
    QCryptographicHash *md4Hash = new QCryptographicHash(QCryptographicHash::Md4);
    md4Hash->addData(sourceStr);
    QByteArray targetStr = md4Hash->result();
    QString resStr = targetStr.toHex();

    resStr = resStr + "lichao";
    sourceStr = resStr.toAscii();
    QCryptographicHash *md5Hash = new QCryptographicHash(QCryptographicHash::Md5);
    md5Hash->addData(sourceStr);
    targetStr = md5Hash->result();
    resStr = targetStr.toHex();

    resStr = resStr + "lichao";
    sourceStr = resStr.toAscii();
    QCryptographicHash *sha1Hash = new QCryptographicHash(QCryptographicHash::Sha1);
    sha1Hash->addData(sourceStr);
    targetStr = sha1Hash->result();
    resStr = targetStr.toHex();

    return resStr;
}

QString fingerBmpPath = "f.bmp";
QMap<int, QVariant> fingerTemplateMap;


//添加人员指纹模板
void insertFingerTempMap(int userid, QVariant ATemplate)
{
    fingerTemplateMap.insert(userid, ATemplate);
}

//删除人员指纹模板
void removeFingerTempMap(int userid)
{
    fingerTemplateMap.remove(userid);
}

//修改人员指纹模板
void modifyFingerTempMap(int userid, QVariant ATemplate)
{
    removeFingerTempMap(userid);
    insertFingerTempMap(userid, ATemplate);
}

