#include <QtGui/QApplication>
#include "logindialog.h"
#include "mydatabase.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));

    QApplication app(argc, argv);

    //打开数据库
    mydatabase db;
    if(db.opendb("book.db"))
    {
        //创建数据库表
        db.createtable();
    }

    //创建相应的文件夹
    createFolder("user");  //人员

    //网络连接
    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        QNetworkSession *networkSession = new QNetworkSession(config, &app);
        networkSession->open();
        networkSession->waitForOpened();

        if (networkSession->isOpen()) {
            // Save the used configuration
            QNetworkConfiguration config = networkSession->configuration();
            QString id;
            if (config.type() == QNetworkConfiguration::UserChoice) {
                id = networkSession->sessionProperty(
                        QLatin1String("UserChoiceConfiguration")).toString();
            } else {
                id = config.identifier();
            }

            QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
            settings.beginGroup(QLatin1String("QtNetwork"));
            settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
            settings.endGroup();
        }
    }

    loginDialog w;
    w.show();

    return app.exec();
}

#if 0

图书管理即时服务系统
六大功能：登录模块，图书管理模块，学生管理模块，借还信息模块，图书检索模块和发送信息模块
登录模块：选择是普通用户登录还是管理员登录。管理员登录跳转到管理员界面，普通用户登录则跳转到普通用户界面。
图书管理模块：管理员通过验证界面进入系统后，进入到图书管理模块，可以对图书进行添加、删除、修改图书信息、查询、查看等一系列的操作。
用户管理模块：管理员通过验证界面进入系统后，进入到用户管理模块，可以增加用户（提供借阅卡）、删除用户、修改用户信息、查询、查看操作。数据库中用户信息包括姓名和手机号码和密码。手机号码默认为借阅卡编号，且为登录账号。管理员添加用户的时候，有设置密码一项。
借阅管理模块：管理员进入该模块中可以为用户办理借阅图书，归还图书，还可以查看用户的借阅信息。
图书检索模块：普通用户通过验证界面进入系统后，能够根据图书ID，书名，作者等多种条件对图书进行查询操作。
重点功能。。。发送信息模块
发送信息模块：管理员会根据数据库中图书的归还日期，对归还剩余时间为1天时，管理员会向用户发送提醒信息，若时间相同，就会向多个用户群发信息。

#endif
