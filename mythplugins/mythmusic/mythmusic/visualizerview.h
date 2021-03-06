#ifndef VISUALIZERVIEW_H_
#define VISUALIZERVIEW_H_

// qt
#include <QEvent>
#include <QVector>

// mythui
#include <mythscreentype.h>

// mythmusic
#include <musiccommon.h>

class MythUIVideo;

class VisualizerView : public MusicCommon
{
    Q_OBJECT
  public:
    VisualizerView(MythScreenStack *parent, MythScreenType *parentScreen);
    ~VisualizerView(void) = default;

    bool Create(void) override; // MythScreenType
    bool keyPressEvent(QKeyEvent *) override; // MusicCommon

    void ShowMenu(void) override; // MusicCommon

  protected:
    void customEvent(QEvent *event) override; // MusicCommon

  private slots:
    void showTrackInfoPopup(void);
};

class MPUBLIC TrackInfoPopup : public MythScreenType
{
  Q_OBJECT
  public:
    TrackInfoPopup(MythScreenStack *parent, MusicMetadata *mdata);
    ~TrackInfoPopup(void);

    bool Create(void) override; // MythScreenType
    bool keyPressEvent(QKeyEvent *event) override; // MythScreenType

  protected:
    MusicMetadata *m_metadata;
    QTimer   *m_displayTimer;
};

#endif
