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
    if (tables.contains("person", Qt::CaseInsensitive)
            && tables.contains("dictionary", Qt::CaseInsensitive)
            && tables.contains("myword", Qt::CaseInsensitive)
            )
    {
        //如果上述表名已存在,则不需要再次创建
        //qDebug("table exsited\n");
    }
    else
    {
        QSqlQuery query;
        //创建人员表(编号, 姓名, 密码)
        query.exec("create table person(personid int primary key, name varchar, passwd varchar)");
        //创建生字表(编号, 用户, 生字)
        query.exec("create table myword(mywordid int primary key, userid varchar, myword varchar)");
        //创建字典表(编号, 字典)
        query.exec("create table dictionary(dictionaryid int primary key, myword varchar)");

        //插入管理员初始用户名和密码
        query.exec("insert into person values(1,'ad','')");

        //插入字典
        query.exec("insert into dictionary values(1, '一')");
        query.exec("insert into dictionary values(2, '二')");
        query.exec("insert into dictionary values(3, '三')");
        query.exec("insert into dictionary values(4, '四')");
        query.exec("insert into dictionary values(5, '五')");
        query.exec("insert into dictionary values(6, '十')");
        query.exec("insert into dictionary values(7, '虫')");
        query.exec("insert into dictionary values(8, '牛')");
        query.exec("insert into dictionary values(9, '鸟')");
        query.exec("insert into dictionary values(10, '鱼')");
        query.exec("insert into dictionary values(11, '马')");
        query.exec("insert into dictionary values(12, '鸭')");
        query.exec("insert into dictionary values(13, '上')");
        query.exec("insert into dictionary values(14, '下')");
        query.exec("insert into dictionary values(15, '大')");
        query.exec("insert into dictionary values(16, '小')");
        query.exec("insert into dictionary values(17, '少')");
        query.exec("insert into dictionary values(18, '中')");
        query.exec("insert into dictionary values(19, '头')");
        query.exec("insert into dictionary values(20, '只')");
        query.exec("insert into dictionary values(21, '朵')");
        query.exec("insert into dictionary values(22, '棵')");
        query.exec("insert into dictionary values(23, '条')");
        query.exec("insert into dictionary values(24, '火')");
        query.exec("insert into dictionary values(25, '六')");
        query.exec("insert into dictionary values(26, '七')");
        query.exec("insert into dictionary values(27, '八')");
        query.exec("insert into dictionary values(28, '九')");
        query.exec("insert into dictionary values(29, '不')");
        query.exec("insert into dictionary values(30, '个')");
        query.exec("insert into dictionary values(31, '红')");
        query.exec("insert into dictionary values(32, '灯')");
        query.exec("insert into dictionary values(33, '妈')");
        query.exec("insert into dictionary values(34, '白')");
        query.exec("insert into dictionary values(35, '车')");
        query.exec("insert into dictionary values(36, '门')");
        query.exec("insert into dictionary values(37, '画')");
        query.exec("insert into dictionary values(38, '听')");
        query.exec("insert into dictionary values(39, '飞')");
        query.exec("insert into dictionary values(40, '种')");
        query.exec("insert into dictionary values(41, '打')");
        query.exec("insert into dictionary values(42, '好')");
        query.exec("insert into dictionary values(43, '人')");
        query.exec("insert into dictionary values(44, '耳')");
        query.exec("insert into dictionary values(45, '牙')");
        query.exec("insert into dictionary values(46, '口')");
        query.exec("insert into dictionary values(47, '手')");
        query.exec("insert into dictionary values(48, '女')");
        query.exec("insert into dictionary values(49, '云')");
        query.exec("insert into dictionary values(50, '日')");
        query.exec("insert into dictionary values(51, '月')");
        query.exec("insert into dictionary values(52, '山')");
        query.exec("insert into dictionary values(53, '水')");
        query.exec("insert into dictionary values(54, '田')");
        query.exec("insert into dictionary values(55, '江')");
        query.exec("insert into dictionary values(56, '花')");
        query.exec("insert into dictionary values(57, '叶')");
        query.exec("insert into dictionary values(58, '沙')");
        query.exec("insert into dictionary values(59, '草')");
        query.exec("insert into dictionary values(60, '木')");
        query.exec("insert into dictionary values(61, '天')");
        query.exec("insert into dictionary values(62, '空')");
        query.exec("insert into dictionary values(63, '世')");
        query.exec("insert into dictionary values(64, '界')");
        query.exec("insert into dictionary values(65, '土')");
        query.exec("insert into dictionary values(66, '地')");
        query.exec("insert into dictionary values(67, '你')");
        query.exec("insert into dictionary values(68, '我')");
        query.exec("insert into dictionary values(69, '他')");
        query.exec("insert into dictionary values(70, '她')");
        query.exec("insert into dictionary values(71, '它')");
        query.exec("insert into dictionary values(72, '们')");
        query.exec("insert into dictionary values(73, '气')");
        query.exec("insert into dictionary values(74, '候')");
        query.exec("insert into dictionary values(75, '风')");
        query.exec("insert into dictionary values(76, '晴')");
        query.exec("insert into dictionary values(77, '雨')");
        query.exec("insert into dictionary values(78, '雪')");
        query.exec("insert into dictionary values(79, '蓝')");
        query.exec("insert into dictionary values(80, '黄')");
        query.exec("insert into dictionary values(81, '绿')");
        query.exec("insert into dictionary values(82, '色')");
        query.exec("insert into dictionary values(83, '青')");
        query.exec("insert into dictionary values(84, '美')");
        query.exec("insert into dictionary values(85, '光')");
        query.exec("insert into dictionary values(86, '亮')");
        query.exec("insert into dictionary values(87, '明')");
        query.exec("insert into dictionary values(88, '太')");
        query.exec("insert into dictionary values(89, '星')");
        query.exec("insert into dictionary values(90, '阳')");
        query.exec("insert into dictionary values(91, '爷')");
        query.exec("insert into dictionary values(92, '奶')");
        query.exec("insert into dictionary values(93, '爸')");
        query.exec("insert into dictionary values(94, '姐')");
        query.exec("insert into dictionary values(95, '家')");
        query.exec("insert into dictionary values(96, '母')");
        query.exec("insert into dictionary values(97, '树')");
        query.exec("insert into dictionary values(98, '果')");
        query.exec("insert into dictionary values(99, '瓜')");
        query.exec("insert into dictionary values(100, '枝')");
        query.exec("insert into dictionary values(101, '米')");
        query.exec("insert into dictionary values(102, '生')");
        query.exec("insert into dictionary values(103, '松')");
        query.exec("insert into dictionary values(104, '竹')");
        query.exec("insert into dictionary values(105, '柳')");
        query.exec("insert into dictionary values(106, '桃')");
        query.exec("insert into dictionary values(107, '森')");
        query.exec("insert into dictionary values(108, '林')");
        query.exec("insert into dictionary values(109, '春')");
        query.exec("insert into dictionary values(110, '秋')");
        query.exec("insert into dictionary values(111, '冬')");
        query.exec("insert into dictionary values(112, '年')");
        query.exec("insert into dictionary values(113, '岁')");
        query.exec("insert into dictionary values(114, '像')");
        query.exec("insert into dictionary values(115, '同')");
        query.exec("insert into dictionary values(116, '学')");
        query.exec("insert into dictionary values(117, '老')");
        query.exec("insert into dictionary values(118, '师')");
        query.exec("insert into dictionary values(119, '习')");
        query.exec("insert into dictionary values(120, '园')");
        query.exec("insert into dictionary values(121, '又')");
        query.exec("insert into dictionary values(122, '和')");
        query.exec("insert into dictionary values(123, '也')");
        query.exec("insert into dictionary values(124, '再')");
        query.exec("insert into dictionary values(125, '就')");
        query.exec("insert into dictionary values(126, '才')");
        query.exec("insert into dictionary values(127, '河')");
        query.exec("insert into dictionary values(128, '海')");
        query.exec("insert into dictionary values(129, '流')");
        query.exec("insert into dictionary values(130, '清')");
        query.exec("insert into dictionary values(131, '池')");
        query.exec("insert into dictionary values(132, '满')");
        query.exec("insert into dictionary values(133, '欢')");
        query.exec("insert into dictionary values(134, '乐')");
        query.exec("insert into dictionary values(135, '高')");
        query.exec("insert into dictionary values(136, '兴')");
        query.exec("insert into dictionary values(137, '歌')");
        query.exec("insert into dictionary values(138, '金')");
        query.exec("insert into dictionary values(139, '跑')");
        query.exec("insert into dictionary values(140, '跳')");
        query.exec("insert into dictionary values(141, '行')");
        query.exec("insert into dictionary values(142, '走')");
        query.exec("insert into dictionary values(143, '立')");
        query.exec("insert into dictionary values(144, '坐')");
        query.exec("insert into dictionary values(145, '东')");
        query.exec("insert into dictionary values(146, '西')");
        query.exec("insert into dictionary values(147, '南')");
        query.exec("insert into dictionary values(148, '北')");
        query.exec("insert into dictionary values(149, '前')");
        query.exec("insert into dictionary values(150, '后')");
        query.exec("insert into dictionary values(151, '为')");
        query.exec("insert into dictionary values(152, '什')");
        query.exec("insert into dictionary values(153, '么')");
        query.exec("insert into dictionary values(154, '知')");
        query.exec("insert into dictionary values(155, '道')");
        query.exec("insert into dictionary values(156, '会')");
        query.exec("insert into dictionary values(157, '来')");
        query.exec("insert into dictionary values(158, '去')");
        query.exec("insert into dictionary values(159, '回')");
        query.exec("insert into dictionary values(160, '别')");
        query.exec("insert into dictionary values(161, '从')");
        query.exec("insert into dictionary values(162, '向')");
        query.exec("insert into dictionary values(163, '许')");
        query.exec("insert into dictionary values(164, '多')");
        query.exec("insert into dictionary values(165, '几')");
        query.exec("insert into dictionary values(166, '千')");
        query.exec("insert into dictionary values(167, '有')");
        query.exec("insert into dictionary values(168, '没')");
        query.exec("insert into dictionary values(169, '毛')");
        query.exec("insert into dictionary values(170, '角')");
        query.exec("insert into dictionary values(171, '兔')");
        query.exec("insert into dictionary values(172, '禾')");
        query.exec("insert into dictionary values(173, '苗')");
        query.exec("insert into dictionary values(174, '面')");
        query.exec("insert into dictionary values(175, '方')");
        query.exec("insert into dictionary values(176, '圆')");
        query.exec("insert into dictionary values(177, '点')");
        query.exec("insert into dictionary values(178, '正')");
        query.exec("insert into dictionary values(179, '台')");
        query.exec("insert into dictionary values(180, '位')");
        query.exec("insert into dictionary values(181, '用')");
        query.exec("insert into dictionary values(182, '做')");
        query.exec("insert into dictionary values(183, '住')");
        query.exec("insert into dictionary values(184, '变')");
        query.exec("insert into dictionary values(185, '把')");
        query.exec("insert into dictionary values(186, '处')");
        query.exec("insert into dictionary values(187, '这')");
        query.exec("insert into dictionary values(188, '那')");
        query.exec("insert into dictionary values(189, '边')");
        query.exec("insert into dictionary values(190, '里')");
        query.exec("insert into dictionary values(191, '总')");
        query.exec("insert into dictionary values(192, '是')");
        query.exec("insert into dictionary values(193, '着')");
        query.exec("insert into dictionary values(194, '了')");
        query.exec("insert into dictionary values(195, '的')");
        query.exec("insert into dictionary values(196, '节')");
        query.exec("insert into dictionary values(197, '成')");
        query.exec("insert into dictionary values(198, '在')");
        query.exec("insert into dictionary values(199, '进')");
        query.exec("insert into dictionary values(200, '出')");
        query.exec("insert into dictionary values(201, '过')");
        query.exec("insert into dictionary values(202, '到')");
        query.exec("insert into dictionary values(203, '开')");
        query.exec("insert into dictionary values(204, '入')");
        query.exec("insert into dictionary values(205, '捉')");
        query.exec("insert into dictionary values(206, '找')");
        query.exec("insert into dictionary values(207, '放')");
        query.exec("insert into dictionary values(208, '玩')");
        query.exec("insert into dictionary values(209, '活')");
        query.exec("insert into dictionary values(210, '动')");
        query.exec("insert into dictionary values(211, '说')");
        query.exec("insert into dictionary values(212, '话')");
        query.exec("insert into dictionary values(213, '叫')");
        query.exec("insert into dictionary values(214, '声')");
        query.exec("insert into dictionary values(215, '吹')");
        query.exec("insert into dictionary values(216, '问')");
        query.exec("insert into dictionary values(217, '最')");
        query.exec("insert into dictionary values(218, '很')");
        query.exec("insert into dictionary values(219, '每')");
        query.exec("insert into dictionary values(220, '片')");
        query.exec("insert into dictionary values(221, '分')");
        query.exec("insert into dictionary values(222, '告')");
        query.exec("insert into dictionary values(223, '孩')");
        query.exec("insert into dictionary values(224, '子')");
        query.exec("insert into dictionary values(225, '衣')");
        query.exec("insert into dictionary values(226, '干')");
        query.exec("insert into dictionary values(227, '力')");
        query.exec("insert into dictionary values(228, '事')");
        query.exec("insert into dictionary values(229, '送')");
        query.exec("insert into dictionary values(230, '还')");
        query.exec("insert into dictionary values(231, '给')");
        query.exec("insert into dictionary values(232, '让')");
        query.exec("insert into dictionary values(233, '要')");
        query.exec("insert into dictionary values(234, '得')");
        query.exec("insert into dictionary values(235, '眼')");
        query.exec("insert into dictionary values(236, '足')");
        query.exec("insert into dictionary values(237, '皮')");
        query.exec("insert into dictionary values(238, '发')");
        query.exec("insert into dictionary values(239, '巴')");
        query.exec("insert into dictionary values(240, '心')");
        query.exec("insert into dictionary values(241, '新')");
        query.exec("insert into dictionary values(242, '快')");
        query.exec("insert into dictionary values(243, '真')");
        query.exec("insert into dictionary values(244, '全')");
        query.exec("insert into dictionary values(245, '对')");
        query.exec("insert into dictionary values(246, '长')");
        query.exec("insert into dictionary values(247, '吃')");
        query.exec("insert into dictionary values(248, '笑')");
        query.exec("insert into dictionary values(249, '看')");
        query.exec("insert into dictionary values(250, '见')");
        query.exec("insert into dictionary values(251, '想')");
        query.exec("insert into dictionary values(252, '奇')");
        query.exec("insert into dictionary values(253, '书')");
        query.exec("insert into dictionary values(254, '纸')");
        query.exec("insert into dictionary values(255, '笔')");
        query.exec("insert into dictionary values(256, '写')");
        query.exec("insert into dictionary values(257, '字')");
        query.exec("insert into dictionary values(258, '数')");
        query.exec("insert into dictionary values(259, '夜')");
        query.exec("insert into dictionary values(260, '晚')");
        query.exec("insert into dictionary values(261, '早')");
        query.exec("insert into dictionary values(262, '乌')");
        query.exec("insert into dictionary values(263, '时')");
        query.exec("insert into dictionary values(264, '间')");
        query.exec("insert into dictionary values(265, '朋')");
        query.exec("insert into dictionary values(266, '友')");
        query.exec("insert into dictionary values(267, '伴')");
        query.exec("insert into dictionary values(268, '自')");
        query.exec("insert into dictionary values(269, '己')");
        query.exec("insert into dictionary values(270, '答')");
        query.exec("insert into dictionary values(271, '请')");
        query.exec("insert into dictionary values(272, '原')");
        query.exec("insert into dictionary values(273, '完')");
        query.exec("insert into dictionary values(274, '可')");
        query.exec("insert into dictionary values(275, '起')");
        query.exec("insert into dictionary values(276, '带')");
        query.exec("insert into dictionary values(277, '觉')");
        query.exec("insert into dictionary values(278, '跟')");
        query.exec("insert into dictionary values(279, '步')");
        query.exec("insert into dictionary values(280, '石')");
        query.exec("insert into dictionary values(281, '都')");
        query.exec("insert into dictionary values(282, '国')");
        query.exec("insert into dictionary values(283, '热')");
        query.exec("insert into dictionary values(284, '爱')");
        query.exec("insert into dictionary values(285, '城')");
        query.exec("insert into dictionary values(286, '市')");
        query.exec("insert into dictionary values(287, '乡')");
        query.exec("insert into dictionary values(288, '村')");
        query.exec("insert into dictionary values(289, '工')");
        query.exec("insert into dictionary values(290, '厂')");
        query.exec("insert into dictionary values(291, '校')");
        query.exec("insert into dictionary values(292, '商')");
        query.exec("insert into dictionary values(293, '场')");
        query.exec("insert into dictionary values(294, '医')");
        query.exec("insert into dictionary values(295, '作')");
        query.exec("insert into dictionary values(296, '业')");
        query.exec("insert into dictionary values(297, '课')");
        query.exec("insert into dictionary values(298, '本')");
        query.exec("insert into dictionary values(299, '题')");
        query.exec("insert into dictionary values(300, '目')");
        query.exec("insert into dictionary values(301, '教')");
        query.exec("insert into dictionary values(302, '改')");
        query.exec("insert into dictionary values(303, '及')");
        query.exec("insert into dictionary values(304, '格')");
        query.exec("insert into dictionary values(305, '办')");
        query.exec("insert into dictionary values(306, '级')");
        query.exec("insert into dictionary values(307, '拉')");
        query.exec("insert into dictionary values(308, '推')");
        query.exec("insert into dictionary values(309, '拔')");
        query.exec("insert into dictionary values(310, '排')");
        query.exec("insert into dictionary values(311, '拍')");
        query.exec("insert into dictionary values(312, '投')");
        query.exec("insert into dictionary values(313, '男')");
        query.exec("insert into dictionary values(314, '哥')");
        query.exec("insert into dictionary values(315, '弟')");
        query.exec("insert into dictionary values(316, '父')");
        query.exec("insert into dictionary values(317, '儿')");
        query.exec("insert into dictionary values(318, '童')");
        query.exec("insert into dictionary values(319, '身')");
        query.exec("insert into dictionary values(320, '体')");
        query.exec("insert into dictionary values(321, '脚')");
        query.exec("insert into dictionary values(322, '嘴')");
        query.exec("insert into dictionary values(323, '脸')");
        query.exec("insert into dictionary values(324, '香')");
        query.exec("insert into dictionary values(325, '张')");
        query.exec("insert into dictionary values(326, '夏')");
        query.exec("insert into dictionary values(327, '虹')");
        query.exec("insert into dictionary values(328, '秀')");
        query.exec("insert into dictionary values(329, '亲')");
        query.exec("insert into dictionary values(330, '情')");
        query.exec("insert into dictionary values(331, '岛')");
        query.exec("insert into dictionary values(332, '湖')");
        query.exec("insert into dictionary values(333, '岸')");
        query.exec("insert into dictionary values(334, '桥')");
        query.exec("insert into dictionary values(335, '漂')");
        query.exec("insert into dictionary values(336, '游')");
        query.exec("insert into dictionary values(337, '伙')");
        query.exec("insert into dictionary values(338, '丁')");
        query.exec("insert into dictionary values(339, '所')");
        query.exec("insert into dictionary values(340, '现')");
        query.exec("insert into dictionary values(341, '今')");
        query.exec("insert into dictionary values(342, '午')");
        query.exec("insert into dictionary values(343, '床')");
        query.exec("insert into dictionary values(344, '钟')");
        query.exec("insert into dictionary values(345, '桌')");
        query.exec("insert into dictionary values(346, '杯')");
        query.exec("insert into dictionary values(347, '瓶')");
        query.exec("insert into dictionary values(348, '镜')");
        query.exec("insert into dictionary values(349, '针')");
        query.exec("insert into dictionary values(350, '线')");
        query.exec("insert into dictionary values(351, '伞')");
        query.exec("insert into dictionary values(352, '裙')");
        query.exec("insert into dictionary values(353, '服')");
        query.exec("insert into dictionary values(354, '布')");
        query.exec("insert into dictionary values(355, '群')");
        query.exec("insert into dictionary values(356, '众')");
        query.exec("insert into dictionary values(357, '泪')");
        query.exec("insert into dictionary values(358, '汗')");
        query.exec("insert into dictionary values(359, '直')");
        query.exec("insert into dictionary values(360, '化')");
        query.exec("insert into dictionary values(361, '语')");
        query.exec("insert into dictionary values(362, '文')");
        query.exec("insert into dictionary values(363, '加')");
        query.exec("insert into dictionary values(364, '认')");
        query.exec("insert into dictionary values(365, '等')");
        query.exec("insert into dictionary values(366, '结')");
        query.exec("insert into dictionary values(367, '实')");
        query.exec("insert into dictionary values(368, '根')");
        query.exec("insert into dictionary values(369, '李')");
        query.exec("insert into dictionary values(370, '贝')");
        query.exec("insert into dictionary values(371, '公')");
        query.exec("insert into dictionary values(372, '共')");
        query.exec("insert into dictionary values(373, '近')");
        query.exec("insert into dictionary values(374, '远')");
        query.exec("insert into dictionary values(375, '短')");
        query.exec("insert into dictionary values(376, '深')");
        query.exec("insert into dictionary values(377, '广')");
        query.exec("insert into dictionary values(378, '古')");
        query.exec("insert into dictionary values(379, '两')");
        query.exec("insert into dictionary values(380, '样')");
        query.exec("insert into dictionary values(381, '百')");
        query.exec("insert into dictionary values(382, '万')");
        query.exec("insert into dictionary values(383, '代')");
        query.exec("insert into dictionary values(384, '精')");
        query.exec("insert into dictionary values(385, '汽')");
        query.exec("insert into dictionary values(386, '船')");
        query.exec("insert into dictionary values(387, '司')");
        query.exec("insert into dictionary values(388, '机')");
        query.exec("insert into dictionary values(389, '路')");
        query.exec("insert into dictionary values(390, '列')");
        query.exec("insert into dictionary values(391, '视')");
        query.exec("insert into dictionary values(392, '望')");
        query.exec("insert into dictionary values(393, '闻')");
        query.exec("insert into dictionary values(394, '净')");
        query.exec("insert into dictionary values(395, '忘')");
        query.exec("insert into dictionary values(396, '赶')");
        query.exec("insert into dictionary values(397, '饭')");
        query.exec("insert into dictionary values(398, '猪')");
        query.exec("insert into dictionary values(399, '羊')");
        query.exec("insert into dictionary values(400, '鹅')");
        query.exec("insert into dictionary values(401, '鸡')");
        query.exec("insert into dictionary values(402, '蛋')");
        query.exec("insert into dictionary values(403, '重')");
        query.exec("insert into dictionary values(404, '量')");
        query.exec("insert into dictionary values(405, '速')");
        query.exec("insert into dictionary values(406, '度')");
        query.exec("insert into dictionary values(407, '左')");
        query.exec("insert into dictionary values(408, '右')");
        query.exec("insert into dictionary values(409, '积')");
        query.exec("insert into dictionary values(410, '往')");
        query.exec("insert into dictionary values(411, '专')");
        query.exec("insert into dictionary values(412, '各')");
        query.exec("insert into dictionary values(413, '王')");
        query.exec("insert into dictionary values(414, '主')");
        query.exec("insert into dictionary values(415, '被')");
        query.exec("insert into dictionary values(416, '包')");
        query.exec("insert into dictionary values(417, '座')");
        query.exec("insert into dictionary values(418, '席')");
        query.exec("insert into dictionary values(419, '意')");
        query.exec("insert into dictionary values(420, '外')");
        query.exec("insert into dictionary values(421, '平')");
        query.exec("insert into dictionary values(422, '整')");
        query.exec("insert into dictionary values(423, '齐')");
        query.exec("insert into dictionary values(424, '忙')");
        query.exec("insert into dictionary values(425, '响')");
        query.exec("insert into dictionary values(426, '物')");
        query.exec("insert into dictionary values(427, '洗')");
        query.exec("insert into dictionary values(428, '扫')");
        query.exec("insert into dictionary values(429, '读')");
        query.exec("insert into dictionary values(430, '唱')");
        query.exec("insert into dictionary values(431, '练')");
        query.exec("insert into dictionary values(432, '选')");
        query.exec("insert into dictionary values(433, '猫')");
        query.exec("insert into dictionary values(434, '象')");
        query.exec("insert into dictionary values(435, '蛇')");
        query.exec("insert into dictionary values(436, '虾')");
        query.exec("insert into dictionary values(437, '蚁')");
        query.exec("insert into dictionary values(438, '洞')");
        query.exec("insert into dictionary values(439, '报')");
        query.exec("insert into dictionary values(440, '名')");
        query.exec("insert into dictionary values(441, '比')");
        query.exec("insert into dictionary values(442, '赛')");
        query.exec("insert into dictionary values(443, '争')");
        query.exec("insert into dictionary values(444, '取')");
        query.exec("insert into dictionary values(445, '记')");
        query.exec("insert into dictionary values(446, '收')");
        query.exec("insert into dictionary values(447, '议')");
        query.exec("insert into dictionary values(448, '闭')");
        query.exec("insert into dictionary values(449, '合')");
        query.exec("insert into dictionary values(450, '关')");
        query.exec("insert into dictionary values(451, '战')");
        query.exec("insert into dictionary values(452, '保')");
        query.exec("insert into dictionary values(453, '刀')");
        query.exec("insert into dictionary values(454, '将')");
        query.exec("insert into dictionary values(455, '军')");
        query.exec("insert into dictionary values(456, '队')");
        query.exec("insert into dictionary values(457, '首')");
        query.exec("insert into dictionary values(458, '先')");
        query.exec("insert into dictionary values(459, '常')");
        query.exec("insert into dictionary values(460, '已')");
        query.exec("insert into dictionary values(461, '并')");
        query.exec("insert into dictionary values(462, '些')");
        query.exec("insert into dictionary values(463, '骑')");
        query.exec("insert into dictionary values(464, '领')");
        query.exec("insert into dictionary values(465, '查')");
        query.exec("insert into dictionary values(466, '引')");
        query.exec("insert into dictionary values(467, '划')");
        query.exec("insert into dictionary values(468, '提')");
        query.exec("insert into dictionary values(469, '吓')");
        query.exec("insert into dictionary values(470, '惊')");
        query.exec("insert into dictionary values(471, '怕')");
        query.exec("insert into dictionary values(472, '苦')");
        query.exec("insert into dictionary values(473, '冷')");
        query.exec("insert into dictionary values(474, '疼')");
        query.exec("insert into dictionary values(475, '京')");
        query.exec("insert into dictionary values(476, '华')");
        query.exec("insert into dictionary values(477, '窗')");
        query.exec("insert into dictionary values(478, '户')");
        query.exec("insert into dictionary values(479, '房')");
        query.exec("insert into dictionary values(480, '屋')");
        query.exec("insert into dictionary values(481, '安')");
        query.exec("insert into dictionary values(482, '装')");
        query.exec("insert into dictionary values(483, '建')");
        query.exec("insert into dictionary values(484, '造')");
        query.exec("insert into dictionary values(485, '楼')");
        query.exec("insert into dictionary values(486, '施')");
        query.exec("insert into dictionary values(487, '电')");
        query.exec("insert into dictionary values(488, '影')");
        query.exec("insert into dictionary values(489, '网')");
        query.exec("insert into dictionary values(490, '球')");
        query.exec("insert into dictionary values(491, '照')");
        query.exec("insert into dictionary values(492, '相')");
        query.exec("insert into dictionary values(493, '运')");
        query.exec("insert into dictionary values(494, '举')");
        query.exec("insert into dictionary values(495, '转')");
        query.exec("insert into dictionary values(496, '采')");
        query.exec("insert into dictionary values(497, '管')");
        query.exec("insert into dictionary values(498, '治')");
        query.exec("insert into dictionary values(499, '消')");
        query.exec("insert into dictionary values(500, '值')");

    }
}

void database::closedb()
{
    db.close();
}

QString userid;


