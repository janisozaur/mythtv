#ifndef AUDIOOUTPUTOPENSLES
#define AUDIOOUTPUTOPENSLES

#include <QMutex>
// For native audio
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <jni.h>

// MythTV headers
#include "audiooutputbase.h"

typedef SLresult (*slCreateEngine_t)(
        SLObjectItf*, SLuint32, const SLEngineOption*, SLuint32,
        const SLInterfaceID*, const SLboolean*);

class AudioOutputOpenSLES : public AudioOutputBase
{
  friend class AudioOutputOpenSLESPrivate;
  public:
    explicit AudioOutputOpenSLES(const AudioSettings &settings);
    virtual ~AudioOutputOpenSLES();

    // Volume control
    int  GetVolumeChannel(int channel) const override; // VolumeBase
    void SetVolumeChannel(int channel, int volume) override; // VolumeBase

  protected:
    bool OpenDevice(void) override; // AudioOutputBase
    void CloseDevice(void) override; // AudioOutputBase
    void WriteAudio(unsigned char *aubuf, int size) override; // AudioOutputBase
    int  GetBufferedOnSoundcard(void) const override; // AudioOutputBase
    AudioOutputSettings* GetOutputSettings(bool digital) override; // AudioOutputBase

  private:
    int GetNumberOfBuffersQueued() const;

    //static const uint      kPacketCnt;

    bool CreateEngine();
    static void SPlayedCallback(SLAndroidSimpleBufferQueueItf caller, void *pContext);
    void PlayedCallback(SLAndroidSimpleBufferQueueItf caller);
    bool StartPlayer();
    bool Stop();
    bool Open();
    void Close();

  private:
    /* OpenSL objects */
    SLObjectItf                     engineObject = nullptr;
    SLObjectItf                     outputMixObject = nullptr;
    SLAndroidSimpleBufferQueueItf   playerBufferQueue = nullptr;
    SLObjectItf                     playerObject = nullptr;
    SLVolumeItf                     volumeItf = nullptr;
    SLEngineItf                     engineEngine = nullptr;
    SLPlayItf                       playerPlay = nullptr;

    /* OpenSL symbols */
    void                           *p_so_handle = nullptr;

    slCreateEngine_t                slCreateEnginePtr = nullptr;
    SLInterfaceID                   SL_IID_ENGINE = nullptr;
    SLInterfaceID                   SL_IID_ANDROIDSIMPLEBUFFERQUEUE = nullptr;
    SLInterfaceID                   SL_IID_VOLUME = nullptr;
    SLInterfaceID                   SL_IID_PLAY = nullptr;

    /* audio buffered through opensles */
    uint8_t                        *buf = nullptr;
    int                             bufWriteBase;   // always fragment aligned
    int                             bufWriteIndex;  // offset from base

    /* if we can measure latency already */
    bool                            started;
    int                             nativeOutputSampleRate;

    QMutex                          lock;

};

#endif // AUDIOOUTPUTOPENSLES
