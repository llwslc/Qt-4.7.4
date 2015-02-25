#include "win7tts.h"

Win7TTS::Win7TTS(void) :
    _binit(0),
    _bReading(0)
{
}

Win7TTS::~Win7TTS(void)
{
}


bool Win7TTS::initSpeech()
{

    if(_binit)
        return true;

    _binit = this->_voice.setControl("96749377-3391-11D2-9EE3-00C04F797396");

    if(_binit)
    {
        connect(&this->_voice,SIGNAL(signal(QString, int, void*)), this, SLOT(dealevent(QString, int, void*)));
    }

    return _binit;
}

bool Win7TTS::speak(QString & txt)
{
    if(!_binit)
        return false;

    int result = this->_voice.dynamicCall("Speak(QString, SpeechVoiceSpeakFlags)", txt ,1).toInt();
    _bReading = true;
    return result;
}

void Win7TTS::pause()
{
    if(!_binit)
        return;
    _bReading = false;
    this->_voice.dynamicCall("Pause()");
}

void Win7TTS::resume()
{
    if(!_binit)
        return;
    _bReading = true;
    this->_voice.dynamicCall("Resume()");
}

void Win7TTS::stop()
{
    if(!_binit)
        return;
    _bReading = false;
    this->_voice.dynamicCall("Speak(QString, SpeechVoiceSpeakFlags)", "" ,2).toInt();
}

bool Win7TTS::isSpeaking()
{
    return _bReading;
}

//rate range : -10 - 10
int Win7TTS::rate()
{
    if(!_binit)
        return -99999;

    return this->_voice.property("Rate").toInt();
}

void Win7TTS::setRate(int rate)
{
    if(!_binit)
        return;

    this->_voice.dynamicCall("SetRate(int)", rate);
}

//volume range : 0 - 100
int Win7TTS::volume()
{

    if(!_binit)
        return -99999;

    return this->_voice.property("Volume").toInt();
}

void Win7TTS::setVolume(int value)
{
    if(!_binit)
        return;

    this->_voice.dynamicCall("SetVolume(int)", value);
}

void Win7TTS::dealevent(QString name, int arc , void* argv)
{
    if(name == "EndStream(int,QVariant)")
    {
        _bReading = false;
        emit speakComplete();
    }
}
