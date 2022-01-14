#ifdef WIN32
#include "StdAfx.h"
#endif

#include "plog.h"
#include <iostream>
#include "PLogControl.h"

extern "C"  {
    static PLogControl *g_plogControl = NULL;

    PLOG_API HANDLE PLogOpen(const char *log) {
        if(g_plogControl == NULL)
            return NULL;
        return g_plogControl->PLogOpen(log);
    }

    PLOG_API bool PLogClose(HANDLE h) {
        if(g_plogControl == NULL)
            return false;
        return g_plogControl->PLogClose(h);
    }

    PLOG_API bool PLogWrite(int type, HANDLE h, const char *log, unsigned short logLen) {
        if(g_plogControl == NULL)
            return false;
        return g_plogControl->PLogWrite(type, h, log, logLen);
    }

    PLOG_API bool PLogWriteHex(int type, HANDLE h, const char *prefix, const char *data, unsigned short dataLen) {
        if(g_plogControl == NULL)
            return false;
        return g_plogControl->PLogWriteHex(type, h, prefix, data, dataLen);
    }

    PLOG_API void PLogInit() {
        if(g_plogControl == NULL)
        {
            g_plogControl = new PLogControl;
            g_plogControl->StartThread();
        }
    }

    PLOG_API void PLogUnInit() {
        if(g_plogControl != NULL)
        {
            g_plogControl->StopThread();
            delete g_plogControl;
            g_plogControl = NULL;
        }
    }
};
