#ifndef COMMON_H
#define COMMON_H

#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QDialog>
#include <QObject>
#include <QAxWidget>
#include <QAbstractItemModel>
#include <QSqlDatabase>
#include <QCryptographicHash>

//拷贝文件
bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist);
//拷贝文件夹
bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
//创建文件夹
bool createFolder(const QString dir);

//加密
QString Encrypt(QString s);

//权限
#define STAFF_ROLE  0       /* 员工 */
#define BUYER_ROLE  1       /* 采购员 */
#define KEEPER_ROLE 2       /* 保管员 */
#define LEADER_ROLE 3       /* 主管 */
#define ADMIN_ROLE  4       /* 管理员 */


#define BORROW_FLAG 0       /* 借出标志 */
#define BACK_FALG   1       /* 归还标志 */

//指纹图片路径
extern QString fingerBmpPath;

//人员指纹模板
extern QMap<int, QVariant> fingerTemplateMap;

//添加人员指纹模板
void insertFingerTempMap(int userid, QVariant ATemplate);
//删除人员指纹模板
void removeFingerTempMap(int userid);
//修改人员指纹模板
void modifyFingerTempMap(int userid, QVariant ATemplate);

#endif // COMMON_H
