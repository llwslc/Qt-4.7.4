#ifndef WIN7ITTS_H
#define WIN7ITTS_H

#include "itts.h"
#include <QAxObject.h>

class Win7TTS :
        public ITTS
{
    Q_OBJECT
public:
    Win7TTS(void);
    virtual ~Win7TTS(void);

    virtual bool initSpeech();
    virtual bool speak(QString & txt);
    virtual void pause();
    virtual void resume();
    virtual void stop();

    //rate range : -10 - 10
    virtual int rate();
    virtual void setRate(int rate);

    //volume range : 0 - 100
    virtual int volume();
    virtual void setVolume(int value) ;
    virtual bool isSpeaking();
private slots:

    void dealevent(QString name, int arc , void* argv);

private:
    QAxObject _voice;
    bool _binit;
    bool _bReading;
};

#endif // WIN7ITTS_H
