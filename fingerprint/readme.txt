for(int i=0; i<135; i++)
{
    qDebug() << i << " : " << qFinger->metaObject()->method(i).typeName() << " " << qFinger->metaObject()->method(i).signature();
}

0  :     destroyed(QObject*) 
1  :     destroyed() 
2  :     deleteLater() 
3  :     _q_reregisterTimers(void*) 
4  :     customContextMenuRequested(QPoint) 
5  :     setEnabled(bool) 
6  :     setDisabled(bool) 
7  :     setWindowModified(bool) 
8  :     setWindowTitle(QString) 
9  :     setStyleSheet(QString) 
10  :     setFocus() 
11  :     update() 
12  :     repaint() 
13  :     setVisible(bool) 
14  :     setHidden(bool) 
15  :     show() 
16  :     hide() 
17  :     setShown(bool) 
18  :     showMinimized() 
19  :     showMaximized() 
20  :     showFullScreen() 
21  :     showNormal() 
22  :  bool   close() 
23  :     raise() 
24  :     lower() 
25  :     updateMicroFocus() 
26  :     _q_showIfNotHidden() 
27  :     OnCapture(bool,QVariant) 
28  :     OnCaptureToFile(bool) 
29  :     OnEnroll(bool,QVariant) 
30  :     OnEnrollToFile(bool) 
31  :     OnFeatureInfo(int) 
32  :     OnFingerLeaving() 
33  :     OnFingerTouching() 
34  :     OnImageReceived(bool&) 
35  :     exception(int,QString,QString,QString) 
36  :     propertyChanged(QString) 
37  :     signal(QString,int,void*) 
38  :  bool   AddBitmap(int,int,int,int,int,int) 
39  :  bool   AddImageFile(QString,int) 
40  :  int   AddRegTemplateFileToFPCacheDB(int,int,QString) 
41  :  int   AddRegTemplateFileToFPCacheDBEx(int,int,QString,QString) 
42  :  int   AddRegTemplateStrToFPCacheDB(int,int,QString) 
43  :  int   AddRegTemplateStrToFPCacheDBEx(int,int,QString,QString) 
44  :  int   AddRegTemplateToFPCacheDB(int,int,QVariant) 
45  :  int   AddRegTemplateToFPCacheDBEx(int,int,QVariant,QVariant) 
46  :     BeginCapture() 
47  :     BeginEnroll() 
48  :     CancelCapture() 
49  :     CancelEnroll() 
50  :  QVariant   CompressTemplate(QString) 
51  :  int   ControlSensor(int,int) 
52  :  QVariant   ConvertAttTemplate(QVariant) 
53  :  QVariant   ConvertToBiokey(QVariant) 
54  :  int   CreateFPCacheDB() 
55  :  int   CreateFPCacheDBEx() 
56  :  bool   DecodeTemplate(QString,QVariant&) 
57  :  QVariant   DecodeTemplate1(QString) 
58  :  bool   DongleIsExist() 
59  :  bool   DongleMemRead(int&,int&,QVariant&) 
60  :  bool   DongleMemWrite(int&,int&,QVariant&) 
61  :  bool   DongleSeed(int&,int&,int&,int&,int&) 
62  :  int   DongleUserID() 
63  :  bool   EncodeTemplate(QVariant,QString&) 
64  :  QString   EncodeTemplate1(QVariant) 
65  :     EndEngine() 
66  :  int   ExtractImageFromTerminal(QVariant,int,bool,QVariant&) 
67  :  int   ExtractImageFromURU(QString,int,bool,QVariant&) 
68  :  int   ExtractImageFromURU4000(LPSTR,int,bool,QVariant&) 
69  :     FlushFPImages() 
70  :     FreeFPCacheDB(int) 
71  :     FreeFPCacheDBEx(int) 
72  :  bool   GenRegTemplateAsStringFromFile(QString,int,QString&) 
73  :  bool   GenVerTemplateAsStringFromFile(QString,int,QString&) 
74  :  bool   GetFingerImage(QVariant&) 
75  :  QVariant   GetTemplate() 
76  :  QString   GetTemplateAsString() 
77  :  QString   GetTemplateAsStringEx(QString) 
78  :     GetTemplateCount(int,int&,int&) 
79  :  QVariant   GetTemplateEx(QString) 
80  :  int   GetVerScore() 
81  :  QVariant   GetVerTemplate() 
82  :  QVariant   GetVerTemplateEx(QString) 
83  :  int   IdentificationFromFileInFPCacheDB(int,QString,int&,int&) 
84  :  int   IdentificationFromStrInFPCacheDB(int,QString,int&,int&) 
85  :  int   IdentificationInFPCacheDB(int,QVariant,int&,int&) 
86  :  int   InitEngine() 
87  :  bool   IsOneToOneTemplate(QVariant) 
88  :  bool   IsOneToOneTemplateFile(QString) 
89  :  bool   IsOneToOneTemplateStr(QString) 
90  :  bool   MF_GET_SNR(int,int,uint,uint,uint&,uint&) 
91  :  bool   MF_GetSerNum(int,int,uint&) 
92  :  bool   MF_GetVersionNum(int,int,uint&) 
93  :  bool   MF_PCDRead(int,int,uint,uint,uint,uint&,uint&) 
94  :  bool   MF_PCDWrite(int,int,uint,uint,uint,uint&,uint&) 
95  :  bool   MF_SetSerNum(int,int,uint&,uint&) 
96  :     ModifyTemplate(QVariant&,bool) 
97  :     ModifyTemplateFile(QString,bool) 
98  :     ModifyTemplateStr(QString&,bool) 
99  :     PrintImageAt(int,int,int,int,int) 
100  :     PrintImageEllipseAt(int,int,int,int,int,QColor) 
101  :  int   RemoveRegTemplateFromFPCacheDB(int,int) 
102  :  int   RemoveRegTemplateFromFPCacheDBEx(int,int) 
103  :     SaveBitmap(QString) 
104  :     SaveJPG(QString) 
105  :  bool   SaveTemplate(QString,QVariant) 
106  :     SaveTemplateStr(QString,QString) 
107  :     SetActive(bool) 
108  :     SetAutoIdentifyPara(bool,int,int) 
109  :     SetEngineValid(bool) 
110  :     SetEnrollCount(int) 
111  :     SetEnrollIndex(int) 
112  :     SetFPEngineVersion(QString) 
113  :     SetForceSecondMatch(bool) 
114  :     SetImageDirection(bool) 
115  :     SetImageHeight(int) 
116  :     SetImageWidth(int) 
117  :     SetIsRegister(bool) 
118  :     SetIsReturnNoLic(bool) 
119  :     SetLowestQuality(int) 
120  :     SetOneToOnePara(int,int) 
121  :     SetOneToOneThreshold(int) 
122  :     SetRegTplFileName(QString) 
123  :     SetSensorCount(int) 
124  :     SetSensorIndex(int) 
125  :     SetSensorSN(QString) 
126  :  int   SetTemplateLen(QVariant&,int) 
127  :     SetTemplateLen(int) 
128  :     SetThreshold(int) 
129  :     SetVerTplFileName(QString) 
130  :     UsingXTFTemplate(bool) 
131  :  bool   VerFinger(QVariant&,QVariant,bool,bool&) 
132  :  bool   VerFingerFromFile(QString,QString,bool,bool&) 
133  :  bool   VerFingerFromStr(QString&,QString,bool,bool&) 
134  :  bool   VerRegFingerFile(QString,QVariant,bool,bool&) 
