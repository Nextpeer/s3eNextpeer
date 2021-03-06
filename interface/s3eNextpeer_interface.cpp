/*
 * WARNING: this is an autogenerated file and will be overwritten by
 * the extension interface script.
 */

#include "s3eExt.h"
#include "IwDebug.h"

#include "s3eNextpeer.h"

/**
 * Definitions for functions types passed to/from s3eExt interface
 */
typedef       void(*s3eNextpeerInitWithProductKey_t)(const char* productKey);
typedef       void(*s3eNextpeerLaunchDashboard_t)();
typedef       void(*s3eNextpeerLaunchDashboardWithCurrencyAmount_t)(uint32 unifiedVirtualCurrencyAmount);
typedef       void(*s3eNextpeerDismissDashboard_t)();
typedef       void(*s3eNextpeerShutDown_t)();
typedef       void(*s3eNextpeerReportScoreForCurrentTournament_t)(uint32 score);
typedef    s3eBool(*s3eNextpeerIsCurrentlyInTournament_t)();
typedef     uint32(*s3eNextpeerTimeLeftInTournament_t)();
typedef       void(*s3eNextpeerReportForfeitForCurrentTournament_t)();
typedef       void(*s3eNextpeerPushDataToOtherPlayers_t)(const void* data, uint32 length);
typedef       void(*s3eNextpeerPushNotificationToOtherPlayers_t)(const char * notice);
typedef       void(*s3eNextpeerHandleOpenURL_t)(void* url);
typedef       void(*s3eNextpeerRegisterOpenURLCallback_t)();
typedef       void(*s3eNextpeerSetUnifiedVirtualCurrencySupport_t)(s3eBool unifiedVirtualCurrencySupported);
typedef       void(*s3eNextpeerOpenFeed_t)();
typedef  s3eResult(*s3eNextpeerRegisterCallback_t)(s3eNextperCallback cbid, s3eCallback fn, void* pData);
typedef  s3eResult(*s3eNextpeerUnRegisterCallback_t)(s3eNextperCallback cbid, s3eCallback fn);

/**
 * struct that gets filled in by s3eNextpeerRegister
 */
typedef struct s3eNextpeerFuncs
{
    s3eNextpeerInitWithProductKey_t m_s3eNextpeerInitWithProductKey;
    s3eNextpeerLaunchDashboard_t m_s3eNextpeerLaunchDashboard;
    s3eNextpeerLaunchDashboardWithCurrencyAmount_t m_s3eNextpeerLaunchDashboardWithCurrencyAmount;
    s3eNextpeerDismissDashboard_t m_s3eNextpeerDismissDashboard;
    s3eNextpeerShutDown_t m_s3eNextpeerShutDown;
    s3eNextpeerReportScoreForCurrentTournament_t m_s3eNextpeerReportScoreForCurrentTournament;
    s3eNextpeerIsCurrentlyInTournament_t m_s3eNextpeerIsCurrentlyInTournament;
    s3eNextpeerTimeLeftInTournament_t m_s3eNextpeerTimeLeftInTournament;
    s3eNextpeerReportForfeitForCurrentTournament_t m_s3eNextpeerReportForfeitForCurrentTournament;
    s3eNextpeerPushDataToOtherPlayers_t m_s3eNextpeerPushDataToOtherPlayers;
    s3eNextpeerPushNotificationToOtherPlayers_t m_s3eNextpeerPushNotificationToOtherPlayers;
    s3eNextpeerHandleOpenURL_t m_s3eNextpeerHandleOpenURL;
    s3eNextpeerRegisterOpenURLCallback_t m_s3eNextpeerRegisterOpenURLCallback;
    s3eNextpeerSetUnifiedVirtualCurrencySupport_t m_s3eNextpeerSetUnifiedVirtualCurrencySupport;
    s3eNextpeerOpenFeed_t m_s3eNextpeerOpenFeed;
    s3eNextpeerRegisterCallback_t m_s3eNextpeerRegisterCallback;
    s3eNextpeerUnRegisterCallback_t m_s3eNextpeerUnRegisterCallback;
} s3eNextpeerFuncs;

static s3eNextpeerFuncs g_Ext;
static bool g_GotExt = false;
static bool g_TriedExt = false;
static bool g_TriedNoMsgExt = false;

static bool _extLoad()
{
    if (!g_GotExt && !g_TriedExt)
    {
        s3eResult res = s3eExtGetHash(0x9aa36f5b, &g_Ext, sizeof(g_Ext));
        if (res == S3E_RESULT_SUCCESS)
            g_GotExt = true;
        else
            s3eDebugAssertShow(S3E_MESSAGE_CONTINUE_STOP_IGNORE, "error loading extension: s3eNextpeer");
        g_TriedExt = true;
        g_TriedNoMsgExt = true;
    }

    return g_GotExt;
}

static bool _extLoadNoMsg()
{
    if (!g_GotExt && !g_TriedNoMsgExt)
    {
        s3eResult res = s3eExtGetHash(0x9aa36f5b, &g_Ext, sizeof(g_Ext));
        if (res == S3E_RESULT_SUCCESS)
            g_GotExt = true;
        g_TriedNoMsgExt = true;
        if (g_TriedExt)
            g_TriedExt = true;
    }

    return g_GotExt;
}

s3eBool s3eNextpeerAvailable()
{
    _extLoadNoMsg();
    return g_GotExt ? S3E_TRUE : S3E_FALSE;
}

void s3eNextpeerInitWithProductKey(const char* productKey)
{
    IwTrace(NEXTPEER_VERBOSE, ("calling s3eNextpeer[0] func: s3eNextpeerInitWithProductKey"));

    if (!_extLoad())
        return;

    g_Ext.m_s3eNextpeerInitWithProductKey(productKey);
}

void s3eNextpeerLaunchDashboard()
{
    IwTrace(NEXTPEER_VERBOSE, ("calling s3eNextpeer[1] func: s3eNextpeerLaunchDashboard"));

    if (!_extLoad())
        return;

    g_Ext.m_s3eNextpeerLaunchDashboard();
}

void s3eNextpeerLaunchDashboardWithCurrencyAmount(uint32 unifiedVirtualCurrencyAmount)
{
    IwTrace(NEXTPEER_VERBOSE, ("calling s3eNextpeer[2] func: s3eNextpeerLaunchDashboardWithCurrencyAmount"));

    if (!_extLoad())
        return;

    g_Ext.m_s3eNextpeerLaunchDashboardWithCurrencyAmount(unifiedVirtualCurrencyAmount);
}

void s3eNextpeerDismissDashboard()
{
    IwTrace(NEXTPEER_VERBOSE, ("calling s3eNextpeer[3] func: s3eNextpeerDismissDashboard"));

    if (!_extLoad())
        return;

    g_Ext.m_s3eNextpeerDismissDashboard();
}

void s3eNextpeerShutDown()
{
    IwTrace(NEXTPEER_VERBOSE, ("calling s3eNextpeer[4] func: s3eNextpeerShutDown"));

    if (!_extLoad())
        return;

    g_Ext.m_s3eNextpeerShutDown();
}

void s3eNextpeerReportScoreForCurrentTournament(uint32 score)
{
    IwTrace(NEXTPEER_VERBOSE, ("calling s3eNextpeer[5] func: s3eNextpeerReportScoreForCurrentTournament"));

    if (!_extLoad())
        return;

    g_Ext.m_s3eNextpeerReportScoreForCurrentTournament(score);
}

s3eBool s3eNextpeerIsCurrentlyInTournament()
{
    IwTrace(NEXTPEER_VERBOSE, ("calling s3eNextpeer[6] func: s3eNextpeerIsCurrentlyInTournament"));

    if (!_extLoad())
        return 0;

    return g_Ext.m_s3eNextpeerIsCurrentlyInTournament();
}

uint32 s3eNextpeerTimeLeftInTournament()
{
    IwTrace(NEXTPEER_VERBOSE, ("calling s3eNextpeer[7] func: s3eNextpeerTimeLeftInTournament"));

    if (!_extLoad())
        return 0;

    return g_Ext.m_s3eNextpeerTimeLeftInTournament();
}

void s3eNextpeerReportForfeitForCurrentTournament()
{
    IwTrace(NEXTPEER_VERBOSE, ("calling s3eNextpeer[8] func: s3eNextpeerReportForfeitForCurrentTournament"));

    if (!_extLoad())
        return;

    g_Ext.m_s3eNextpeerReportForfeitForCurrentTournament();
}

void s3eNextpeerPushDataToOtherPlayers(const void* data, uint32 length)
{
    IwTrace(NEXTPEER_VERBOSE, ("calling s3eNextpeer[9] func: s3eNextpeerPushDataToOtherPlayers"));

    if (!_extLoad())
        return;

    g_Ext.m_s3eNextpeerPushDataToOtherPlayers(data, length);
}

void s3eNextpeerPushNotificationToOtherPlayers(const char * notice)
{
    IwTrace(NEXTPEER_VERBOSE, ("calling s3eNextpeer[10] func: s3eNextpeerPushNotificationToOtherPlayers"));

    if (!_extLoad())
        return;

    g_Ext.m_s3eNextpeerPushNotificationToOtherPlayers(notice);
}

void s3eNextpeerHandleOpenURL(void* url)
{
    IwTrace(NEXTPEER_VERBOSE, ("calling s3eNextpeer[11] func: s3eNextpeerHandleOpenURL"));

    if (!_extLoad())
        return;

    g_Ext.m_s3eNextpeerHandleOpenURL(url);
}

void s3eNextpeerRegisterOpenURLCallback()
{
    IwTrace(NEXTPEER_VERBOSE, ("calling s3eNextpeer[12] func: s3eNextpeerRegisterOpenURLCallback"));

    if (!_extLoad())
        return;

    g_Ext.m_s3eNextpeerRegisterOpenURLCallback();
}

void s3eNextpeerSetUnifiedVirtualCurrencySupport(s3eBool unifiedVirtualCurrencySupported)
{
    IwTrace(NEXTPEER_VERBOSE, ("calling s3eNextpeer[13] func: s3eNextpeerSetUnifiedVirtualCurrencySupport"));

    if (!_extLoad())
        return;

    g_Ext.m_s3eNextpeerSetUnifiedVirtualCurrencySupport(unifiedVirtualCurrencySupported);
}

void s3eNextpeerOpenFeed()
{
    IwTrace(NEXTPEER_VERBOSE, ("calling s3eNextpeer[14] func: s3eNextpeerOpenFeed"));

    if (!_extLoad())
        return;

    g_Ext.m_s3eNextpeerOpenFeed();
}

s3eResult s3eNextpeerRegisterCallback(s3eNextperCallback cbid, s3eCallback fn, void* pData)
{
    IwTrace(NEXTPEER_VERBOSE, ("calling s3eNextpeer[15] func: s3eNextpeerRegisterCallback"));

    if (!_extLoad())
        return S3E_RESULT_SUCCESS;

    return g_Ext.m_s3eNextpeerRegisterCallback(cbid, fn, pData);
}

s3eResult s3eNextpeerUnRegisterCallback(s3eNextperCallback cbid, s3eCallback fn)
{
    IwTrace(NEXTPEER_VERBOSE, ("calling s3eNextpeer[16] func: s3eNextpeerUnRegisterCallback"));

    if (!_extLoad())
        return S3E_RESULT_SUCCESS;

    return g_Ext.m_s3eNextpeerUnRegisterCallback(cbid, fn);
}
