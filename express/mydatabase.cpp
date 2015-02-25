#include "mydatabase.h"

mydatabase::mydatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

bool mydatabase::opendb(QString dbname)
{
    db.setDatabaseName(dbname);
    if(!db.open())
    {
        qDebug("db file open error");
        return false;
    }
    return true;
}

void mydatabase::createtable()
{
    QStringList tables = db.tables();
    if (tables.contains("car", Qt::CaseInsensitive)
            && tables.contains("goods", Qt::CaseInsensitive)
            && tables.contains("orders", Qt::CaseInsensitive)
            && tables.contains("user", Qt::CaseInsensitive)
            && tables.contains("expresscom", Qt::CaseInsensitive)
            )
    {
        //如果上述表名已存在,则不需要再次创建
        //qDebug("table exsited\n");
    }
    else
    {
        QSqlQuery query;
        //创建车辆表(编号,司机,车牌号,类型)
        query.exec("create table car(carid int primary key, name varchar, carnum varchar, type int)");
        //创建物品表(编号,名称,类型,日期)
        query.exec("create table goods(goodsid int primary key, name varchar, type int, date datetime)");
        //创建订单表(编号,订单号,快递公司)
        query.exec("create table orders(ordersid int primary key, ordernum varchar, express int)");
        //创建人员表(编号,用户名,密码)
        query.exec("create table user(userid int primary key, name varchar, passwd varchar)");
        //创建快递公司表(编号,公司名,代码)
        query.exec("create table expresscom(expresscomid int primary key, name varchar, codes varchar)");

        query.exec("insert into user values(0, 'ad', '')");

        query.exec("insert into expresscom values(0, '', '')");
        query.exec("insert into expresscom values(1, 'AAE快递', 'aae')");
        query.exec("insert into expresscom values(2, '安捷快递', 'anjie')");
        query.exec("insert into expresscom values(3, '安信达快递', 'anxinda')");
        query.exec("insert into expresscom values(4, 'Aramex国际快递', 'aramex')");
        query.exec("insert into expresscom values(5, '成都奔腾国际快递', 'benteng')");
        query.exec("insert into expresscom values(6, 'CCES快递', 'cces')");
        query.exec("insert into expresscom values(7, '长通物流', 'changtong')");
        query.exec("insert into expresscom values(8, '程光快递', 'chengguang')");
        query.exec("insert into expresscom values(9, '城际快递', 'chengji')");
        query.exec("insert into expresscom values(10, '城市100', 'chengshi100')");
        query.exec("insert into expresscom values(11, '传喜快递', 'chuanxi')");
        query.exec("insert into expresscom values(12, '传志快递', 'chuanzhi')");
        query.exec("insert into expresscom values(13, 'CityLinkExpress', 'citylink')");
        query.exec("insert into expresscom values(14, '东方快递', 'coe')");
        query.exec("insert into expresscom values(15, '城市之星', 'cszx')");
        query.exec("insert into expresscom values(16, '大田物流', 'datian')");
        query.exec("insert into expresscom values(17, '大洋物流快递', 'dayang')");
        query.exec("insert into expresscom values(18, '德邦物流', 'debang')");
        query.exec("insert into expresscom values(19, '德创物流', 'dechuang')");
        query.exec("insert into expresscom values(20, 'DHL快递', 'dhl')");
        query.exec("insert into expresscom values(21, '店通快递', 'diantong')");
        query.exec("insert into expresscom values(22, '递达快递', 'dida')");
        query.exec("insert into expresscom values(23, '递四方速递', 'disifang')");
        query.exec("insert into expresscom values(24, 'DPEX快递', 'dpex')");
        query.exec("insert into expresscom values(25, 'D速快递', 'dsu')");
        query.exec("insert into expresscom values(26, '百福东方物流', 'ees')");
        query.exec("insert into expresscom values(27, 'EMS快递', 'ems')");
        query.exec("insert into expresscom values(28, '凡宇快递', 'fanyu')");
        query.exec("insert into expresscom values(29, 'Fardar', 'fardar')");
        query.exec("insert into expresscom values(30, '国际Fedex', 'fedex')");
        query.exec("insert into expresscom values(31, 'Fedex国内', 'fedexcn')");
        query.exec("insert into expresscom values(32, '飞邦物流', 'feibang')");
        query.exec("insert into expresscom values(33, '飞豹快递', 'feibao')");
        query.exec("insert into expresscom values(34, '原飞航物流', 'feihang')");
        query.exec("insert into expresscom values(35, '飞狐快递', 'feihu')");
        query.exec("insert into expresscom values(36, '飞远物流', 'feiyuan')");
        query.exec("insert into expresscom values(37, '丰达快递', 'fengda')");
        query.exec("insert into expresscom values(38, '飞康达快递', 'fkd')");
        query.exec("insert into expresscom values(39, '广东邮政物流', 'gdyz')");
        query.exec("insert into expresscom values(40, '邮政国内小包', 'gnxb')");
        query.exec("insert into expresscom values(41, '共速达物流|快递', 'gongsuda')");
        query.exec("insert into expresscom values(42, '国通快递', 'guotong')");
        query.exec("insert into expresscom values(43, '山东海红快递', 'haihong')");
        query.exec("insert into expresscom values(44, '海盟速递', 'haimeng')");
        query.exec("insert into expresscom values(45, '昊盛物流', 'haosheng')");
        query.exec("insert into expresscom values(46, '河北建华快递', 'hebeijianhua')");
        query.exec("insert into expresscom values(47, '恒路物流', 'henglu')");
        query.exec("insert into expresscom values(48, '华企快递', 'huaqi')");
        query.exec("insert into expresscom values(49, '华夏龙物流', 'huaxialong')");
        query.exec("insert into expresscom values(50, '天地华宇物流', 'huayu')");
        query.exec("insert into expresscom values(51, '汇强快递', 'huiqiang')");
        query.exec("insert into expresscom values(52, '汇通快递', 'huitong')");
        query.exec("insert into expresscom values(53, '海外环球快递', 'hwhq')");
        query.exec("insert into expresscom values(54, '佳吉快运', 'jiaji')");
        query.exec("insert into expresscom values(55, '佳怡物流', 'jiayi')");
        query.exec("insert into expresscom values(56, '加运美快递', 'jiayunmei')");
        query.exec("insert into expresscom values(57, '金大物流', 'jinda')");
        query.exec("insert into expresscom values(58, '京广快递', 'jingguang')");
        query.exec("insert into expresscom values(59, '晋越快递', 'jinyue')");
        query.exec("insert into expresscom values(60, '急先达物流', 'jixianda')");
        query.exec("insert into expresscom values(61, '嘉里大通物流', 'jldt')");
        query.exec("insert into expresscom values(62, '康力物流', 'kangli')");
        query.exec("insert into expresscom values(63, '顺鑫(KCS)快递', 'kcs')");
        query.exec("insert into expresscom values(64, '快捷快递', 'kuaijie')");
        query.exec("insert into expresscom values(65, '跨越快递', 'kuayue')");
        query.exec("insert into expresscom values(66, '乐捷递快递', 'lejiedi')");
        query.exec("insert into expresscom values(67, '联昊通快递', 'lianhaotong')");
        query.exec("insert into expresscom values(68, '成都立即送快递', 'lijisong')");
        query.exec("insert into expresscom values(69, '龙邦快递', 'longbang')");
        query.exec("insert into expresscom values(70, '民邦快递', 'minbang')");
        query.exec("insert into expresscom values(71, '明亮物流', 'mingliang')");
        query.exec("insert into expresscom values(72, '闽盛快递', 'minsheng')");
        query.exec("insert into expresscom values(73, '港中能达快递', 'nengda')");
        query.exec("insert into expresscom values(74, 'OCS快递', 'ocs')");
        query.exec("insert into expresscom values(75, '平安达', 'pinganda')");
        query.exec("insert into expresscom values(76, '中国邮政平邮', 'pingyou')");
        query.exec("insert into expresscom values(77, '品速心达快递', 'pinsu')");
        query.exec("insert into expresscom values(78, '全晨快递', 'quanchen')");
        query.exec("insert into expresscom values(79, '全峰快递', 'quanfeng')");
        query.exec("insert into expresscom values(80, '全际通快递', 'quanjitong')");
        query.exec("insert into expresscom values(81, '全日通快递', 'quanritong')");
        query.exec("insert into expresscom values(82, '全一快递', 'quanyi')");
        query.exec("insert into expresscom values(83, 'RPX保时达', 'rpx')");
        query.exec("insert into expresscom values(84, '如风达快递', 'rufeng')");
        query.exec("insert into expresscom values(85, '赛澳递', 'saiaodi')");
        query.exec("insert into expresscom values(86, '三态速递', 'santai')");
        query.exec("insert into expresscom values(87, '伟邦(SCS)快递', 'scs')");
        query.exec("insert into expresscom values(88, '圣安物流', 'shengan')");
        query.exec("insert into expresscom values(89, '盛丰物流', 'shengfeng')");
        query.exec("insert into expresscom values(90, '盛辉物流', 'shenghui')");
        query.exec("insert into expresscom values(91, '申通快递', 'shentong')");
        query.exec("insert into expresscom values(92, '顺丰快递', 'shunfeng')");
        query.exec("insert into expresscom values(93, '穗佳物流', 'suijia')");
        query.exec("insert into expresscom values(94, '速尔快递', 'sure')");
        query.exec("insert into expresscom values(95, '天天快递', 'tiantian')");
        query.exec("insert into expresscom values(96, 'TNT快递', 'tnt')");
        query.exec("insert into expresscom values(97, '通成物流', 'tongcheng')");
        query.exec("insert into expresscom values(98, '通和天下物流', 'tonghe')");
        query.exec("insert into expresscom values(99, 'UPS', 'ups')");
        query.exec("insert into expresscom values(100, 'USPS快递', 'usps')");
        query.exec("insert into expresscom values(101, '万家物流', 'wanjia')");
        query.exec("insert into expresscom values(102, '微特派', 'weitepai')");
        query.exec("insert into expresscom values(103, '祥龙运通快递', 'xianglong')");
        query.exec("insert into expresscom values(104, '新邦物流', 'xinbang')");
        query.exec("insert into expresscom values(105, '信丰快递', 'xinfeng')");
        query.exec("insert into expresscom values(106, '希优特快递', 'xiyoute')");
        query.exec("insert into expresscom values(107, '源安达快递', 'yad')");
        query.exec("insert into expresscom values(108, '亚风快递', 'yafeng')");
        query.exec("insert into expresscom values(109, '一邦快递', 'yibang')");
        query.exec("insert into expresscom values(110, '银捷快递', 'yinjie')");
        query.exec("insert into expresscom values(111, '亿顺航快递', 'yishunhang')");
        query.exec("insert into expresscom values(112, '优速快递', 'yousu')");
        query.exec("insert into expresscom values(113, '北京一统飞鸿快递', 'ytfh')");
        query.exec("insert into expresscom values(114, '远成物流', 'yuancheng')");
        query.exec("insert into expresscom values(115, '圆通快递', 'yuantong')");
        query.exec("insert into expresscom values(116, '元智捷诚', 'yuanzhi')");
        query.exec("insert into expresscom values(117, '越丰快递', 'yuefeng')");
        query.exec("insert into expresscom values(118, '韵达快递', 'yunda')");
        query.exec("insert into expresscom values(119, '运通中港快递', 'yuntong')");
        query.exec("insert into expresscom values(120, '源伟丰', 'ywfex')");
        query.exec("insert into expresscom values(121, '宅急送快递', 'zhaijisong')");
        query.exec("insert into expresscom values(122, '郑州建华快递', 'zhengzhoujianhua')");
        query.exec("insert into expresscom values(123, '芝麻开门快递', 'zhima')");
        query.exec("insert into expresscom values(124, '济南中天万运', 'zhongtian')");
        query.exec("insert into expresscom values(125, '中铁快运', 'zhongtie')");
        query.exec("insert into expresscom values(126, '中通快递', 'zhongtong')");
        query.exec("insert into expresscom values(127, '忠信达快递', 'zhongxinda')");
        query.exec("insert into expresscom values(128, '中邮物流', 'zhongyou')");

    }
}

void mydatabase::closedb()
{
    db.close();
}
