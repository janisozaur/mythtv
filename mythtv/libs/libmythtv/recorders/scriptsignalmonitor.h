// -*- Mode: c++ -*-

#ifndef _SCRIPT_SIGNAL_MONITOR_H_
#define _SCRIPT_SIGNAL_MONITOR_H_

// MythTV headers
#include "signalmonitor.h"

class ScriptSignalMonitor : public SignalMonitor
{
  public:
    ScriptSignalMonitor(int db_cardnum, ChannelBase *_channel,
                        bool _release_stream,
                        uint64_t _flags = 0) :
        SignalMonitor(db_cardnum, _channel, _release_stream, _flags)
    {
        signalLock.SetValue(true);
        signalStrength.SetValue(100);
    }

    void UpdateValues(void) override // SignalMonitor
    {
        SignalMonitor::UpdateValues();

        EmitStatus();
        if (IsAllGood())
            SendMessageAllGood();
    }
};

#endif // _SCRIPT_SIGNAL_MONITOR_H_
