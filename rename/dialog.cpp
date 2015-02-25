#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    //重命名
    #if 1
    //   <td height="30"><p align="center" class="STYLE4">短片(HTF Shorts)</p></td>
    QFile::copy("F:\\HappyTreeFriends\\HTF_44_Swallow_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\A Hard Act To Swallow(拯救蚂蚁).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_58_Sucker_pt1_BB24_new.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\A Sucker For Love - Part 1(棒棒糖1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_59_Sucker_pt2_BB24.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\A Sucker For Love - Part 2(棒棒糖2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_53_Zoo_1_BB24.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\A to Zoo - Part 1(动物园1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_53_Zoo_2_BB24.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\A to Zoo - Part 2(动物园2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_62_Flocked_BB24.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\All Flocked Up(落鸟).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_38_Bread_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Better Off Bread(烤面包).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_51_Blind.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Blind Date(初次约会).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_15_Boo_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Boo Do You Think You Are(鬼城).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_55_Cofin.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Can’t Stop Coffin(活埋).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_12_Chip_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Chip Off The Ol’ Block(锄草).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_36_Class_BB24.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Class Act(班级表演).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_04_Antics_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Crazy Antics(舌头).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_28_Eyecandy_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Eye Candy(眼睛糖果).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_32_Eyescold_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Eyes Cold Lemonade(眼睛饮料).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_30_Flippin_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Flippin’ Burgers(果酱).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_31_Whale_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Get Whale Soon(鲸鱼).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_26_Trails1_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Happy Trails Part 1(郊游1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_27_Trails2_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Happy Trails Part 2(郊游2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_05_Ball_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Havin’ A Ball(玩球).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_47_Dolly_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Hello Dolly(诅咒2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_03_Helping_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Helping Helps(水灾).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_14_Hide_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Hide and Seek(捉迷藏).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_02_House_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\House Warming(新房子).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_39_Trick_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\I Get a Trick Out of You(魔术).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_66_I_Nub_h264.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\I Nub You(同类).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_46_Icy_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Icy You(偷吃冷饮).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_21_Snap_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\It’s A Snap(鼠夹子).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_54_Desert.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Just Desert(沙漠).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_43_Reel_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Keeping It Reel(看电影).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_45_Slide_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Let It Slide(水上滑梯).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_19_Meat_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Meat Me For Lunch(偷肉).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_34_Milkin_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Milkin’ It(偷牛).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_16_Mime_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Mime And Mime Again(断腿).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_13_Tooth_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Nuttin’ But The Tooth(拔牙).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_07_Nuttin_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Nuttin’ Wrong With Candy(售货机).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_22_Hook_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Off The Hook(钩眼).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_35_Sight_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Out Of Sight Out Of Mime(刻头).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_42_Limb_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Out On A Limb(伐木).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_60_Peas_BB24.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Peas in a Pod(魔豆).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_09_Pitchin_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Pitchin’ Impossible(扔球).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_56_Read_BB24.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Read ‘Em and Weep(魔咒).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_48_Remains_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Remains To Be Seen(大团圆).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_29_Rink_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Rink Hijinks(掏心).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_40_Shard_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Shard At Work(吃灯泡).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_50_Ski_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Ski Ya, Wouldn’t Wanna Be Ya(滑雪).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_33_Snip_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Snip Snip Hooray(剃头).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_24_Snow_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Snow What(冰凌).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_63_Fishy.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Something Fishy(宠物鱼).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_23_Spare_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Spare Me(保龄球).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_01_Spin_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Spin Fun Knowin’ Ya(转).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_10_Stayin_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Stayin’ Alive(跳舞).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_49_Spot_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Stealing The Spotlight(装饰灯).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_52_Suck_BB24.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Suck It Up(吸).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_20_Sweet_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Sweet Ride(冰淇淋).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_65_Swelter_h264.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Swelter Skelter(酷暑).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_37_Wheel_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\The Way You Make Me Wheel(公路丧命).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_25_Knife_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\This Is Your Knife(篝火).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_18_Tongue_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Tongue Twister(滑冰).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_11_Treasure_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Treasure These Idol Moments(诅咒).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_41_Water_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Water Way To Go(出海).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_06_Water_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Water You Wading For(池塘).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_57_Scrooged.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\We’re Scrooged(财迷心窍).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_08_Wheelin_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Wheelin’ And Dealin’(赛车).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_WhosLine.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Whose Line Is It Anyway(钓鱼).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_64_Hitch_H264.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Without A Hitch(搭车).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_61_Wrath_HD.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\Wrath of Con(发布会).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_17_Bakin_640.flv", "F:\\HappyTreeFriends\\短片(HTF Shorts)\\You’re Baking Me Crazy(熨斗).flv");



    //    <td height="30"><p align="center" class="STYLE4">影片(TV Episodes)</p></td>
    QFile::copy("F:\\HappyTreeFriends\\HTF_S02_Sink_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\And the Kitchen Sink - Part 1(漩涡1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S02_Sink_Pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\And the Kitchen Sink - Part 2(漩涡2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S14_Wish_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\As You Wish - Part 1(神灯1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S14_Wish_Pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\As You Wish - Part 2(神灯2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S36_Authopsy_Pt_1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Autopsy Turvy (Double Whammy - Part 3)(双重人格3).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S36_Authopsy_Pt_2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Autopsy Turvy (Double Whammy - Part 4)(双重人格4).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S25_Blast_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Blast From the Past - Part 1(时光机1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S25_Blast_Pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Blast From the Past - Part 2(时光机2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S21_Heart_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Change of Heart - Part 1(换心1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S21_Heart_Pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Change of Heart - Part 2(换心2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_Chew_pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Chew Said A Mouthful - Part 1(夺命糖1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_Chew_pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Chew Said A Mouthful - Part 2(夺命糖2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S13_Concrete_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Concrete Solution - Part 1(混凝土1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S13_Concrete_Pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Concrete Solution - Part 2(混凝土2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S16_Doggone_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Doggone It! - Part 1(疯狗1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S16_Doggone_Pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Doggone It! - Part 2(疯狗2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S17_Chain_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Don’t Yank My Chain - Part 1(越狱1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S17_Chain_Pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Don’t Yank My Chain - Part 2(越狱2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S35_Whammy_Pt_1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Double Whammy - Part 1(双重人格1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S35_Whammy_Pt_2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Double Whammy - Part 2(双重人格2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S08_Dunce_Pt_1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Dunce Upon A Time - Part 1(天宫1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S08_Dunce_Pt_2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Dunce Upon A Time - Part 2(天宫2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S29_Comb_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Easy Comb, Easy Go - Part 1(生发水1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S29_Comb_Pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Easy Comb, Easy Go - Part 2(生发水2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S12_Sleigh_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Easy For You To Sleigh - Part 1(圣诞小偷1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S12_Sleigh_Pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Easy For You To Sleigh - Part 2(圣诞小偷2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S11_Litter_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Every Litter Bit Hurts - Part 1(环保1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S11_Litter_Pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Every Litter Bit Hurts - Part 2(环保2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S03_Gems_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Gems the Breaks - Part 1(绿宝石1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S03_Gems_Pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Gems the Breaks - Part 2(绿宝石2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S01_Hero_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Hero to Eternity - Part 1(英雄1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S01_Hero_Pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Hero to Eternity - Part 2(英雄2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S20_Hole_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Hole Lotta Love - Part 1(地洞1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S20_Hole_Pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Hole Lotta Love - Part 2(地洞2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S22_Home_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Home Is Where The Hurt Is - Part 1(建房1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S22_Home_Pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Home Is Where The Hurt Is - Part 2(建房2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S23_Idol_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Idol Curiosity - Part 1(诅咒3).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S23_Idol_Pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Idol Curiosity - Part 2(诅咒4).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S37_Jam_Pt_1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\In A Jam - Part 1(歌星1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S37_Jam_Pt_2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\In A Jam - Part 2(歌星2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S09_Fitso_Pt_1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Ipso Fatso - Part 1(减肥1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S09_Fitso_Pt_2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Ipso Fatso - Part 2(减肥2).flv");
    QFile::copy("F:\\HappyTreeFriends\\htf_39_junk_trunk_1_700.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Junk in the Truck - Part 1(大象1).flv");
    QFile::copy("F:\\HappyTreeFriends\\htf_39_junk_trunk_2_500.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Junk in the Truck - Part 2(大象2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S21_Mime_Part1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Mime to Five - Part 1(求职1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S21_Mime_Part2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Mime to Five - Part 2(求职2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S10_Party_Pt_1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Party Animal - Part 1(生日宴会1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S10_Party_Pt_2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Party Animal - Part 2(生日宴会2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S18_Sea_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Sea What I Found - Part 1(寻宝1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S18_Sea_Pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Sea What I Found - Part 2(寻宝2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S24_Develops_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\See What Develops - Part 1(照相1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S24_Develops_Pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\See What Develops - Part 2(照相2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S19_Sight_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Sight for Sore Eyes - Part 1(近视1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S19_Sight_Pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Sight for Sore Eyes - Part 2(近视2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S06_Snow_Part1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Snow Place To Go - Part 1(冰天雪地1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S06_Snow_Part2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Snow Place To Go - Part 2(冰天雪地2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S05_Hike_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Take A Hike - Part 1(远足1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S05_Hike_Pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Take A Hike - Part 2(远足2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S04_Track_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\The Wrong Side of the Tracks - Part 1(过山车1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S04_Track_Pt2.mov.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\The Wrong Side of the Tracks - Part 2(过山车2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF-S32-Tongue_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Tongue in Cheek - Part 1(遥控1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF-S32-Tongue_Pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Tongue in Cheek - Part 2(遥控2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S07_Flame_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Who’s to Flame - Part 1(火灾1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S07_Flame_Pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Who’s to Flame - Part 2(火灾2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S28_Wing_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Wingin’ It - Part 1(空难1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S28_Wing_Pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Wingin’ It - Part 2(空难2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S33_Wipe_Pt_1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Wipe Out! - Part 1(冲浪1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S33_Wipe_Pt_2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Wipe Out! - Part 2(冲浪2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S09_Wishy_Pt1.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Wishy Washy - Part 1(洁癖1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_S09_Wishy_Pt2.flv", "F:\\HappyTreeFriends\\影片(TV Episodes)\\Wishy Washy - Part 2(洁癖2).flv");



    //    <td height="30"><p align="center" class="STYLE4">爱的印迹(Love Bites)</p></td>
    QFile::copy("F:\\HappyTreeFriends\\HTF_LB_Love_1280x720.flv", "F:\\HappyTreeFriends\\爱的印迹(Love Bites)\\I Heart U(爱的幻术).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_LB_SeaOfLove_HD_1280x720.flv", "F:\\HappyTreeFriends\\爱的印迹(Love Bites)\\Sea of Love(爱之海).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_LB_ColdHearted_HD_1280x720.flv", "F:\\HappyTreeFriends\\爱的印迹(Love Bites)\\Cold Hearted(盲爱).flv");




    //    <td height="30"><p align="center" class="STYLE4">非主流(Irregulars)</p></td>
    QFile::copy("F:\\HappyTreeFriends\\HTF_BanjoFrenzy_720.flv", "F:\\HappyTreeFriends\\非主流(Irregulars)\\Banjo Frenzy(五弦琴).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF-FOB_NTSC_24.flv", "F:\\HappyTreeFriends\\非主流(Irregulars)\\Carpal Tunnel of Love(恋爱).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_False_pt1.flv", "F:\\HappyTreeFriends\\非主流(Irregulars)\\False Alarm - Part 1(虚假警报1).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_False_pt2.flv", "F:\\HappyTreeFriends\\非主流(Irregulars)\\False Alarm - Part 2(虚假警报2).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_SkiPatrol_2.flv", "F:\\HappyTreeFriends\\非主流(Irregulars)\\Ski Patrol(滑雪急救).flv");



    //    <td height="30"><p align="center" class="STYLE4">贺卡(Kringles)</p></td>
    QFile::copy("F:\\HappyTreeFriends\\htf_08_chill_kringle.flv", "F:\\HappyTreeFriends\\贺卡(Kringles)\\Chill Kringle(雪人).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_Kringles_Kitchen.flv", "F:\\HappyTreeFriends\\贺卡(Kringles)\\Kitchen Kringle(夜宴).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_Kringles_Reindeer.flv", "F:\\HappyTreeFriends\\贺卡(Kringles)\\Reindeer Kringle(鹿).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_Kringles_Ski.flv", "F:\\HappyTreeFriends\\贺卡(Kringles)\\Ski Kringle(滑雪).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_07_Kringles_Strain.flv", "F:\\HappyTreeFriends\\贺卡(Kringles)\\Strain Kringle(打雪仗).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_Kringles_Train.flv", "F:\\HappyTreeFriends\\贺卡(Kringles)\\Train Kringle(小火车).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_Kringles_Tree.flv", "F:\\HappyTreeFriends\\贺卡(Kringles)\\Tree Kringle(树).flv");



    //    <td height="30"><p align="center" class="STYLE4">动作片特辑(KA-POW!)</p></td>
    QFile::copy("F:\\HappyTreeFriends\\BooksOfFurry.flv", "F:\\HappyTreeFriends\\动作片特辑(KA-POW!)\\Buddhist Monkey - Books of Fury(书).flv");
    QFile::copy("F:\\HappyTreeFriends\\EnterTheGarden.flv", "F:\\HappyTreeFriends\\动作片特辑(KA-POW!)\\Buddhist Monkey - Enter The Garden(护花使者).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_01_KaPow_3Courses_H264_1280x720_new.flv", "F:\\HappyTreeFriends\\动作片特辑(KA-POW!)\\Buddhist Monkey - Three Courses of Death(烈焰).flv");
    QFile::copy("F:\\HappyTreeFriends\\MoleInTheCity.flv", "F:\\HappyTreeFriends\\动作片特辑(KA-POW!)\\Mole In The City(间谍).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_03_KaPow_Spledid_H264_1280x720.flv", "F:\\HappyTreeFriends\\动作片特辑(KA-POW!)\\Splendid’s SSSSSuper Squad - Mirror, Mirror(超人对决).flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_02_KaPow_Operation_H264_1280x720.flv", "F:\\HappyTreeFriends\\动作片特辑(KA-POW!)\\W.A.R. Journal - Operation - Tiger Bomb(人体炸弹).flv");



    //    <td height="30"><p align="center" class="STYLE4">花絮和幕后(Break)</p></td>
    QFile::copy("F:\\HappyTreeFriends\\HTF_DVD_Abestos.flv", "F:\\HappyTreeFriends\\花絮和幕后(Break)\\Asbestos I Can Do.flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_Behind_the_Screams.flv", "F:\\HappyTreeFriends\\花絮和幕后(Break)\\Behind The Screams.flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_ChoreLoser.flv", "F:\\HappyTreeFriends\\花絮和幕后(Break)\\Chore Loser.flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_Caroling_Deck_The_Holes.flv", "F:\\HappyTreeFriends\\花絮和幕后(Break)\\Deck the Halls.flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_HateMail.flv", "F:\\HappyTreeFriends\\花絮和幕后(Break)\\Hate Mail.flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_SeizeTheDay.flv", "F:\\HappyTreeFriends\\花絮和幕后(Break)\\Seize The Day.flv");
    QFile::copy("F:\\HappyTreeFriends\\Something_Fishy_Rec.flv", "F:\\HappyTreeFriends\\花絮和幕后(Break)\\Something Fishy Voice-Over Session.flv");
    QFile::copy("F:\\HappyTreeFriends\\Trainspotting.flv", "F:\\HappyTreeFriends\\花絮和幕后(Break)\\Under The Skin of Happy Tree Friends.flv");
    QFile::copy("F:\\HappyTreeFriends\\HTF_VOices.flv", "F:\\HappyTreeFriends\\花絮和幕后(Break)\\Voices of Doom.flv");

    qDebug() << "copy end";
#endif
}
