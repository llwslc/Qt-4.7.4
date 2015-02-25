#include "mywidget.h"
#include "ui_mywidget.h"
#include "myplaylist.h"
#include "mylrc.h"
#include <QLabel>
#include <QToolBar>
#include <QVBoxLayout>
#include <QTime>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>
#include <QDesktopServices>
#include <QTextCodec>
#include <QMenu>
#include <QCloseEvent>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    InitPlayer();
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/images/bg.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

//初始化播放器
void MyWidget::InitPlayer()
{
    //设置窗口基本属性
    setWindowTitle(tr("悦耳音乐播放器"));
    setWindowIcon(QIcon(":/images/icon.png"));//从资源文件中招图标
    //setMinimumSize(320, 160);
    //setMaximumSize(320, 160);//最大最小设置为一样，代表不改变播放器窗口的大小

    //创建媒体对象
    media_object = new Phonon::MediaObject(this);
    Phonon::AudioOutput *audio_output = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::createPath(media_object, audio_output);//绑定源和接收器

    //关联媒体对象的tick信号来更新播放时间的显示
    connect(media_object, SIGNAL(tick(qint64)), this, SLOT(UpdateTime(qint64)));

    //创建顶部标签
    top_label = new QLabel(tr("悦耳音乐播放器"));
    top_label->setTextFormat(Qt::RichText);
    top_label->setOpenExternalLinks(true);//运行点击进入外部链接
    top_label->setAlignment(Qt::AlignCenter);

    //创建控制播放进度的滑块
    Phonon::SeekSlider *seek_slider = new Phonon::SeekSlider(media_object, this);

    //设置显示时间的标签
    QToolBar *widget_bar = new QToolBar(this);
    time_label = new QLabel(tr("00:00/00:00"), this);
    time_label->setToolTip(tr("当前时间/总时间"));
    time_label->setAlignment(Qt::AlignCenter);
    //QSizePolicy类是描述水平和垂直修改大小策略的一种属性
    time_label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);//水平方向上尺寸可扩展，水平方向已固定

    //播放列表开启控制图标
    QAction *PLAction = new QAction(tr("PL"), this);
    PLAction->setShortcut(QKeySequence("F4"));//设置开启播放列表的快捷键为F4
    PLAction->setToolTip(tr("播放列表(F4)"));
    connect(PLAction, SIGNAL(triggered()), this, SLOT(SetPlayListShown()));//链接触发信号

    //桌面歌词显示开启控制图标
    QAction *LRCAction = new QAction(tr("LRC"), this);
    LRCAction->setShortcut(QKeySequence("F2"));//设置开启桌面歌词的播放列表快捷键为F2
    LRCAction->setToolTip(tr("桌面歌词(F2)"));
    connect(LRCAction, SIGNAL(triggered()), this, SLOT(SetLrcShown()));

    //将上面2个action和1个widget添加到工具栏，默认的添加方式为水平方向添加
    widget_bar->addAction(PLAction);
    widget_bar->addSeparator();
    widget_bar->addWidget(time_label);
    widget_bar->addSeparator();
    widget_bar->addAction(LRCAction);
    widget_bar->addSeparator();

    //设置播放动作
    QToolBar *tool_bar = new QToolBar(this);//该构造函数没有写入文字
    play_action = new QAction(this);
    play_action->setIcon(QIcon(":/images/play.png"));
    play_action->setText(tr("播放(F5)"));
    play_action->setShortcut(QKeySequence("F5"));//播放的快捷键位F5
    connect(play_action, SIGNAL(triggered()), this, SLOT(SetPaused()));

    //设置停止动作
    stop_action = new QAction(this);
    stop_action->setIcon(QIcon(":/images/stop.png"));
    stop_action->setText(tr("停止(F6)"));
    stop_action->setShortcut(QKeySequence("F6"));
    connect(stop_action, SIGNAL(triggered()), media_object, SLOT(stop()));

    //设置上一首动作
    skip_backward_action = new QAction(this);
    skip_backward_action->setIcon(QIcon(":/images/skipBackward.png"));
    skip_backward_action->setText(tr("上一首(Ctrl+Left)"));
    skip_backward_action->setShortcut(QKeySequence("Ctrl+Left"));
    connect(skip_backward_action, SIGNAL(triggered()), this, SLOT(SkipBackward()));

    //设置下一首动作
    skip_forward_action = new QAction(this);
    skip_forward_action->setIcon(QIcon(":/images/skipForward.png"));
    skip_forward_action->setText(tr("上一首(Ctrl+Right)"));
    skip_forward_action->setShortcut(QKeySequence("Ctrl+Right"));
    connect(skip_forward_action, SIGNAL(triggered()), this, SLOT(SkipForward()));

    //设置打开文件动作
    QAction *open_action = new QAction(this);
    open_action->setIcon(QIcon(":/images/open.png"));
    open_action->setText(tr("播放文件(Ctrl+O)"));
    open_action->setShortcut(QKeySequence("Ctrl+O"));
    open_action->setEnabled(true);
    connect(open_action, SIGNAL(triggered()), this, SLOT(OpenFile()));

    //音乐控制部件
    Phonon::VolumeSlider *volume_slider = new Phonon::VolumeSlider(audio_output, this);
    volume_slider->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    //tabWidget = new QTabWidget(this);

    //tempTab = new QWidget();
    //lastTab = new QWidget();
    //playTab = new QWidget();


    //templist = new MyPlaylist(tempTab);
    //lastlist = new MyPlaylist(lastTab);
    //playlist = new MyPlaylist(playTab);
    playlist = new MyPlaylist(this);
    //cellClicked()信号是当表格中的一个cell单元被单击时发出的。
    connect(playlist, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(TableClicked(int)));
    connect(playlist, SIGNAL(play_list_clean()), this, SLOT(ClearSources()));
    connect(playlist, SIGNAL(play_list_delete(int)), this, SLOT(DeleteSources(int)));

    //tabWidget->addTab(tempTab, QString("临时播放列表"));
    //tabWidget->addTab(lastTab, QString("最近播放列表"));
    //tabWidget->addTab(playTab, QString("我的播放列表"));
    //将以上部件添加到工具栏
    tool_bar->addAction(play_action);
    tool_bar->addSeparator();
    tool_bar->addAction(stop_action);
    tool_bar->addSeparator();
    tool_bar->addAction(skip_backward_action);
    tool_bar->addSeparator();
    tool_bar->addAction(skip_forward_action);
    tool_bar->addSeparator();
    tool_bar->addWidget(volume_slider);
    tool_bar->addSeparator();
    tool_bar->addAction(open_action);

    //创建主界面管理器
    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->addWidget(top_label);
    main_layout->addWidget(seek_slider);
    main_layout->addWidget(widget_bar);
    main_layout->addWidget(tool_bar);
    main_layout->addWidget(playlist);
    //main_layout->addWidget(tabWidget);
    setLayout(main_layout);

    //设置媒体部件音乐源
    // media_object->setCurrentSource(Phonon::MediaSource("./music.mp3"));

    //每当媒体对象的状态发生改变时，就会自动发射stateChanged()信号,这里绑定信号后，就可以用这些状态来进行一些有关的设置
    connect(media_object, SIGNAL(stateChanged(Phonon::State, Phonon::State)),
            this, SLOT(StateChanged(Phonon::State, Phonon::State)));

    meta_information_resolver = new Phonon::MediaObject(this);
    Phonon::AudioOutput *meta_information_audio_output =
            new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::createPath(meta_information_resolver, meta_information_audio_output);
    connect(meta_information_resolver, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
            this, SLOT(MetaStateChanged(Phonon::State,Phonon::State)));
    connect(media_object, SIGNAL(currentSourceChanged(Phonon::MediaSource)),
            this, SLOT(SourceChanged(Phonon::MediaSource)));
    play_action->setEnabled(false);
    stop_action->setEnabled(false);
    skip_forward_action->setEnabled(false);
    skip_backward_action->setEnabled(false);
    top_label->setFocus();

    lrc = new MyLrc(this);

    // 创建系统托盘图标
    tray_icon = new QSystemTrayIcon(QIcon(":/images/icon.png"), this);
    tray_icon->setToolTip(tr("悦耳音乐播放器"));
    // 创建菜单,系统托盘图标后右击出现的菜单
    QMenu *menu = new QMenu;
    QList<QAction *> actions;
    actions << play_action << stop_action << skip_backward_action << skip_forward_action;
    menu->addActions(actions);
    menu->addSeparator();
    menu->addAction(PLAction);
    menu->addAction(LRCAction);
    menu->addSeparator();
    menu->addAction(tr("退出"), qApp, SLOT(quit()));
    tray_icon->setContextMenu(menu);
    // 托盘图标被激活后进行处理
    connect(tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(TrayIconActivated(QSystemTrayIcon::ActivationReason)));
    // 显示托盘图标
    tray_icon->show();

    //读取数据库
    QSqlQuery query;
    query.exec("select count(*) from music");
    if(query.next())
    {
        playlist->setRowCount(query.value(0).toInt());
    }
    query.exec("select * from music");
    int iRow = 0;
    while(query.next())
    {
        playlist->setItem(iRow, 0, new QTableWidgetItem(query.value(1).toString()));
        playlist->setItem(iRow, 1, new QTableWidgetItem(query.value(2).toString()));
        playlist->setItem(iRow, 2, new QTableWidgetItem(query.value(3).toString()));

        Phonon::MediaSource source(query.value(4).toString());
        sources.append(source);
        iRow ++;
    }

    playlist->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

// 根据媒体源列表内容和当前媒体源的位置来改变主界面图标的状态
void MyWidget::change_action_state()
{
    // 如果媒体源列表为空
    if (sources.count() == 0)
    {
        // 如果没有在播放歌曲，则播放和停止按钮都不可用
        //（因为可能歌曲正在播放时清除了播放列表）
        if (media_object->state() != Phonon::PlayingState &&
                media_object->state() != Phonon::PausedState)
        {
            play_action->setEnabled(false);
            stop_action->setEnabled(false);
        }
        skip_backward_action->setEnabled(false);
        skip_forward_action->setEnabled(false);
    }
    else
    {
        // 如果媒体源列表不为空
        play_action->setEnabled(true);
        stop_action->setEnabled(true);
        // 如果媒体源列表只有一行
        if (sources.count() == 1)
        {
            skip_backward_action->setEnabled(false);
            skip_forward_action->setEnabled(false);
        }
        else
        {
            // 如果媒体源列表有多行
            skip_backward_action->setEnabled(true);
            skip_forward_action->setEnabled(true);
            int index = playlist->currentRow();
            // 如果播放列表当前选中的行为第一行
            if (index == 0)
                skip_backward_action->setEnabled(false);
            // 如果播放列表当前选中的行为最后一行
            if (index + 1 == sources.count())
                skip_forward_action->setEnabled(false);
        }
    }
}

// 解析LRC歌词，在stateChanged()函数的Phonon::PlayingState处和aboutToFinish()函数中调用了该函数
void MyWidget::resolve_lrc(const QString &source_file_name)
{
    lrc_map.clear();
    if(source_file_name.isEmpty())
        return;
    QString file_name = source_file_name;
    QString lrc_file_name = file_name.left(file_name.length() - 3) + "lrc";//把音频文件的后缀改成lrc后缀

    // 打开歌词文件
    QFile file(lrc_file_name);
    if (!file.open(QIODevice::ReadOnly)) {
        lrc->setText(QFileInfo(media_object->currentSource().fileName()).baseName()
                     + tr(" --- 未找到歌词文件！"));
        return ;
    }
    // 设置字符串编码
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QString all_text = QString(file.readAll());
    file.close();
    // 将歌词按行分解为歌词列表
    QStringList lines = all_text.split("\n");

    //这个是时间标签的格式[00:05.54]
    //正则表达式d{2}表示匹配2个数字
    QRegExp rx("\\[\\d{2}:\\d{2}\\.\\d{2}\\]");
    foreach(QString oneline, lines) {
        QString temp = oneline;
        temp.replace(rx, "");//用空字符串替换正则表达式中所匹配的地方,这样就获得了歌词文本
        // 然后依次获取当前行中的所有时间标签，并分别与歌词文本存入QMap中
        //indexIn()为返回第一个匹配的位置，如果返回为-1，则表示没有匹配成功
        //正常情况下pos后面应该对应的是歌词文件
        int pos = rx.indexIn(oneline, 0);
        while (pos != -1) { //表示匹配成功
            QString cap = rx.cap(0);//返回第0个表达式匹配的内容
            // 将时间标签转换为时间数值，以毫秒为单位
            QRegExp regexp;
            regexp.setPattern("\\d{2}(?=:)");
            regexp.indexIn(cap);
            int minute = regexp.cap(0).toInt();
            regexp.setPattern("\\d{2}(?=\\.)");
            regexp.indexIn(cap);
            int second = regexp.cap(0).toInt();
            regexp.setPattern("\\d{2}(?=\\])");
            regexp.indexIn(cap);
            int millisecond = regexp.cap(0).toInt();
            qint64 totalTime = minute * 60000 + second * 1000 + millisecond * 10;
            // 插入到lrc_map中
            lrc_map.insert(totalTime, temp);
            pos += rx.matchedLength();
            pos = rx.indexIn(oneline, pos);//匹配全部
        }
    }
    // 如果lrc_map为空
    if (lrc_map.isEmpty()) {
        lrc->setText(QFileInfo(media_object->currentSource().fileName()).baseName()
                     + tr(" --- 歌词文件内容错误！"));
        return;
    }
}

void MyWidget::UpdateTime(qint64 time)
{
    qint64 total_time_value = media_object->totalTime();//直接获取该音频文件的总时长参数，单位为毫秒
    //这3个参数分别代表了时，分，秒；60000毫秒为1分钟，所以分钟第二个参数是先除6000,第3个参数是直接除1s
    QTime total_time(0, (total_time_value/60000)%60, (total_time_value/1000)%60);
    QTime current_time(0, (time/60000)%60, (time/1000)%60);//传进来的time参数代表了当前的时间
    QString str = current_time.toString("mm:ss") + "/" + total_time.toString("mm:ss");
    time_label->setText(str);

    // 获取当期时间对应的歌词
    if(!lrc_map.isEmpty()) {
        // 获取当前时间在歌词中的前后两个时间点
        qint64 previous = 0;
        qint64 later = 0;
        //keys()方法返回lrc_map列表
        foreach (qint64 value, lrc_map.keys()) {
            if (time >= value) {
                previous = value;
            } else {
                later = value;
                break;
            }
        }

        // 达到最后一行,将later设置为歌曲总时间的值
        if (later == 0)
            later = total_time_value;

        // 获取当前时间所对应的歌词内容
        QString current_lrc = lrc_map.value(previous);

        //        // 没有内容时
        //        if(current_lrc.length() < 2)
        //            current_lrc = tr("悦耳音乐播放器");

        // 如果是新的一行歌词，那么重新开始显示歌词遮罩
        if(current_lrc != lrc->text()) {
            lrc->setText(current_lrc);
            top_label->setText(current_lrc);
            qint64 interval_time = later - previous;
            lrc->start_lrc_mask(interval_time);
        }
    } else {  // 如果没有歌词文件，则在顶部标签中显示歌曲标题
        top_label->setText(QFileInfo(media_object->
                                     currentSource().fileName()).baseName());
    }
}

void MyWidget::SetPaused()
{
    if(media_object->state() == Phonon::PlayingState) {
        media_object->pause();
    }
    else
        media_object->play();
}

//播放上一首歌曲
void MyWidget::SkipBackward()
{
    lrc->stop_lrc_mask();
    int index = sources.indexOf(media_object->currentSource());
    media_object->setCurrentSource(sources.at(index - 1));
    media_object->play();
}

//播放下一首歌曲
void MyWidget::SkipForward()
{
    lrc->stop_lrc_mask();
    int index = sources.indexOf(media_object->currentSource());
    media_object->setCurrentSource(sources.at(index + 1));
    media_object->play();
}

void MyWidget::OpenFile()
{
    //可以同时打开多个音频文件
    QStringList list = QFileDialog::getOpenFileNames(this, tr("打开音乐文件"),
                                                     QDesktopServices::storageLocation(QDesktopServices::MusicLocation),
                                                     tr("音乐文件 (*.mp3)"));
    if(list.isEmpty())
        return;
    //获取当前媒体源列表的大小
    int index = sources.size();
    foreach(QString string, list) {
        Phonon::MediaSource source(string);
        sources.append(source);
    }
    if(!sources.isEmpty()) {
        //如果媒体源列表不为空，则将新加入的第一个媒体源作为当前媒体源
        meta_information_resolver->setCurrentSource(sources.at(index));
    }
}

void MyWidget::SetPlayListShown()
{
    if(playlist->isHidden())
    {
        playlist->move(frameGeometry().bottomLeft());//显示在主界面的下方
        playlist->show();
    }
    else
    {
        playlist->hide();
    }
}

void MyWidget::SetLrcShown()
{
    if(lrc->isHidden())
        lrc->show();
    else
        lrc->hide();
}

void MyWidget::StateChanged(Phonon::State new_state, Phonon::State old_state)
{
    switch(new_state)
    {
    //当新状态时错误状态时，如果是致命错误则显示警告致命错误消息框，否则显示普通错误消息框
    case Phonon::ErrorState:
        if(media_object->errorType() == Phonon::FatalError) {
            QMessageBox::warning(this, tr("致命错误"), media_object->errorString());//显示其错误的内容
        }
        else {
            QMessageBox::warning(this, tr("错误"), media_object->errorString());//显示普通错误
        }
        break;
        //当新状态为播放状态时,更改一些状态的控件
    case Phonon::PlayingState:
        stop_action->setEnabled(true);
        play_action->setIcon(QIcon(":/images/pause.png"));
        play_action->setText(tr("暂停(F5)"));
        //更改第一行的标签内容为播放文件的文件名。注意baseName是在QFileInfo的后面
        top_label->setText(QFileInfo(media_object->currentSource().fileName()).baseName());
        resolve_lrc(media_object->currentSource().fileName());
        break;
    case Phonon::StoppedState:
        stop_action->setEnabled(false);
        play_action->setIcon(QIcon(":/images/play.png"));
        //setText函数实现的功能感觉和setToolTip一样,只是这里设置过了的文本如果该action对应到菜单栏，则会显示出来
        play_action->setText(tr("播放(F5)"));
        top_label->setText(tr("悦耳音乐播放器"));
        time_label->setText(tr("00:00/00:00"));
        lrc->stop_lrc_mask();
        lrc->setText(tr("悦耳音乐播放器"));
        break;
    case Phonon::PausedState:
        stop_action->setEnabled(true);
        play_action->setIcon(QIcon(":/images/play.png"));
        play_action->setText(tr("播放(F5)"));
        top_label->setText(QFileInfo(media_object->currentSource().fileName()).baseName() + tr(" 已暂停!"));
        // 如果该歌曲有歌词文件
        if (!lrc_map.isEmpty()) {
            lrc->stop_lrc_mask();
            lrc->setText(top_label->text());
        }
        break;
    case Phonon::BufferingState:
        break;
    default:
        ;
    }
}

//该槽函数是当媒体源发生改变时，触发currentSourceChanged()信号,从而执行该槽函数
//该函数完成的功能是选中所改变的媒体源那一行
void MyWidget::SourceChanged(const Phonon::MediaSource &source)
{
    int index = sources.indexOf(source);
    playlist->selectRow(index);
    change_action_state();
}

//当媒体播放快结束时，会发送aboutToFinish()信号，从而触发该槽函数
void MyWidget::AboutToFinish()
{
    int index = sources.indexOf(media_object->currentSource())+1;
    if(sources.size() > index) {
        media_object->enqueue(sources.at(index));//将下一首歌曲添加到播放列表中
        media_object->seek(media_object->totalTime());//跳到当前歌曲的最后
        lrc->stop_lrc_mask();
        resolve_lrc(sources.at(index).fileName());
    }
    else {
        media_object->stop();//如果已经是打开音频文件的最后一首歌了，就直接停止
    }

}

void MyWidget::MetaStateChanged(Phonon::State new_state, Phonon::State old_state)
{
    // 错误状态，则从媒体源列表中除去新添加的媒体源
    if(new_state == Phonon::ErrorState) {
        QMessageBox::warning(this, tr("打开文件时出错"), meta_information_resolver->errorString());
        //takeLast()为删除最后一行并将其返回
        while (!sources.isEmpty() &&
               !(sources.takeLast() == meta_information_resolver->currentSource()))
        {};//只留下最后一行
        return;
    }
    // 如果既不处于停止状态也不处于暂停状态，则直接返回
    if(new_state != Phonon::StoppedState && new_state != Phonon::PausedState)
        return;
    // 如果媒体源类型错误，则直接返回
    if(meta_information_resolver->currentSource().type() == Phonon::MediaSource::Invalid)
        return;

    QMap<QString, QString> meta_data = meta_information_resolver->metaData();//获取媒体源中的源数据

    //获取文件标题信息
    QString title = meta_data.value("TITLE");
    //如果媒体元数据中没有标题信息，则去该音频文件的文件名为该标题信息
    if(title == "") {
        QString str = meta_information_resolver->currentSource().fileName();
        title = QFileInfo(str).baseName();
    }
    QTableWidgetItem *title_item = new QTableWidgetItem(title);
    title_item->setFlags(title_item->flags() ^ Qt::ItemIsEditable);

    //获取艺术家信息
    QTableWidgetItem *artist_item = new QTableWidgetItem(meta_data.value("ARTIST"));
    artist_item->setFlags(artist_item->flags() ^ Qt::ItemIsEditable);

    //获取总时间信息
    qint64 total_time  = meta_information_resolver->totalTime();
    QTime time(0, (total_time/60000)%60, (total_time/10000)%60);
    QTableWidgetItem *time_item = new QTableWidgetItem(time.toString("mm:ss"));

    //sources为打开的所以音频文件列表,playlist为音乐播放列表表格对象
    int index = sources.indexOf(meta_information_resolver->currentSource())+1;

    //插入数据库
    QSqlQuery query;
    int idNum = 0;
    query.exec("select musicid from music where mtitle = '" + title + "' and msinger = '" + meta_data.value("ARTIST") + "' and mlength = '" + time.toString("mm:ss") + "'");
    if(query.next())
    {
        //null
    }
    else
    {
        //插入播放列表
        int current_rows = playlist->rowCount();//返回列表中的行数
        playlist->insertRow(current_rows);
        playlist->setItem(current_rows, 0, title_item);
        playlist->setItem(current_rows, 1, artist_item);
        playlist->setItem(current_rows, 2, time_item);

        query.exec("select musicid from music");
        while(query.next())
        {
            if(idNum < query.value(0).toInt())
                idNum = query.value(0).toInt();
        }

        idNum++;

        query.exec("insert into music values('" + QString::number(idNum, 10) + "', '"
                   + title + "', '"
                   + meta_data.value("ARTIST") + "', '"
                   + time.toString("mm:ss") + "', '"
                   + sources.at(index-1).fileName() + "')");
    }

    if(sources.size() > index)
    {
        //没有解析完
        meta_information_resolver->setCurrentSource(sources.at(index));
    }
    else
    {
        //没有被选中的行
        if(playlist->selectedItems().isEmpty()) {
            // 如果现在没有播放歌曲则设置第一个媒体源为媒体对象的当前媒体源
            //（因为可能正在播放歌曲时清空了播放列表，然后又添加了新的列表）
            if(media_object->state() != Phonon::PlayingState && media_object->state() != Phonon::PausedState)
                media_object->setCurrentSource(sources.at(0));
            else {
                //如果正在播放歌曲，则选中播放列表的第一个曲目,并更改图标状态
                playlist->selectRow(0);
                change_action_state();
            }
        }
        else {
            // 如果播放列表中有选中的行，那么直接更新图标状态
            change_action_state();
        }
    }
}

void MyWidget::TableClicked(int row)
{
    //bool was_palying = media_object->state() == Phonon::PlayingState;
    media_object->stop();//停止当前播放的歌曲
    media_object->clearQueue();//清楚播放队列

    //如果单就的播放列表行号比媒体源中列表行号还大，则直接返回
    if(row >= sources.size())
        return;
    media_object->setCurrentSource(sources.at(row));
    //if(was_palying)//如果选中前在播放歌曲，那么选中后也继续播放歌曲
    media_object->play();
}

void MyWidget::ClearSources()
{
    sources.clear();
    change_action_state();
}

void MyWidget::DeleteSources(int row)
{
    sources.removeAt(row);
}

//系统托盘图标被激活
void MyWidget::TrayIconActivated(QSystemTrayIcon::ActivationReason activation_reason)
{
    if(activation_reason == QSystemTrayIcon::Trigger)
        show();
}

//关闭事件处理函数
void MyWidget::closeEvent(QCloseEvent *event)
{
    if(isVisible()) {
        hide();//单击关闭时，软件并没有关闭起来，而是隐藏在系统图标上
        tray_icon->showMessage(tr("悦耳音乐播放器"), tr("单击我重新回到主界面"));
        event->ignore();//不发送关闭信号
    }
}
