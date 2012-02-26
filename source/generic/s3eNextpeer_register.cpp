/*
 * WARNING: this is an autogenerated file and will be overwritten by
 * the extension interface script.
 */
/*
 * This file contains the automatically generated loader-side
 * functions that form part of the extension.
 *
 * This file is awlays compiled into all loaders but compiles
 * to nothing if this extension is not enabled in the loader
 * at build time.
 */
#include "IwDebug.h"
#include "s3eNextpeer_autodefs.h"
#include "s3eEdk.h"
#include "s3eNextpeer.h"
//Declarations of Init and Term functions
extern s3eResult s3eNextpeerInit();
extern void s3eNextpeerTerminate();


// On platforms that use a seperate UI/OS thread we can autowrap functions
// here.   Note that we can't use the S3E_USE_OS_THREAD define since this
// code is oftern build standalone, outside the main loader build.
#if defined I3D_OS_IPHONE || defined I3D_OS_OSX || defined I3D_OS_LINUX || defined I3D_OS_WINDOWS

static void s3eNextpeerInitWithProductKeyAndDelegatesContainer_wrap(const char* productKey)
{
    IwTrace(NEXTPEER_VERBOSE, ("calling s3eNextpeer func on main thread: s3eNextpeerInitWithProductKeyAndDelegatesContainer"));
    s3eEdkThreadRunOnOS((s3eEdkThreadFunc)s3eNextpeerInitWithProductKeyAndDelegatesContainer, 1, productKey);
}

static void s3eNextpeerLaunchDashboard_wrap()
{
    IwTrace(NEXTPEER_VERBOSE, ("calling s3eNextpeer func on main thread: s3eNextpeerLaunchDashboard"));
    s3eEdkThreadRunOnOS((s3eEdkThreadFunc)s3eNextpeerLaunchDashboard, 0);
}

static void s3eNextpeerDismissDashboard_wrap()
{
    IwTrace(NEXTPEER_VERBOSE, ("calling s3eNextpeer func on main thread: s3eNextpeerDismissDashboard"));
    s3eEdkThreadRunOnOS((s3eEdkThreadFunc)s3eNextpeerDismissDashboard, 0);
}

static void s3eNextpeerShutDown_wrap()
{
    IwTrace(NEXTPEER_VERBOSE, ("calling s3eNextpeer func on main thread: s3eNextpeerShutDown"));
    s3eEdkThreadRunOnOS((s3eEdkThreadFunc)s3eNextpeerShutDown, 0);
}

#define s3eNextpeerInitWithProductKeyAndDelegatesContainer s3eNextpeerInitWithProductKeyAndDelegatesContainer_wrap
#define s3eNextpeerLaunchDashboard s3eNextpeerLaunchDashboard_wrap
#define s3eNextpeerDismissDashboard s3eNextpeerDismissDashboard_wrap
#define s3eNextpeerShutDown s3eNextpeerShutDown_wrap

#endif

void s3eNextpeerRegisterExt()
{
    /* fill in the function pointer struct for this extension */
    void* funcPtrs[9];
    funcPtrs[0] = (void*)s3eNextpeerInitWithProductKeyAndDelegatesContainer;
    funcPtrs[1] = (void*)s3eNextpeerLaunchDashboard;
    funcPtrs[2] = (void*)s3eNextpeerDismissDashboard;
    funcPtrs[3] = (void*)s3eNextpeerShutDown;
    funcPtrs[4] = (void*)s3eNextpeerReportScoreForCurrentTournament;
    funcPtrs[5] = (void*)s3eNextpeerIsCurrentlyInTournament;
    funcPtrs[6] = (void*)s3eNextpeerTimeLeftInTournament;
    funcPtrs[7] = (void*)s3eNextpeerRegisterCallback;
    funcPtrs[8] = (void*)s3eNextpeerUnRegisterCallback;

    /*
     * Flags that specify the extension's use of locking and stackswitching
     */
    int flags[9] = { 0 };

    /*
     * Register the extension
     */
    s3eEdkRegister("s3eNextpeer", funcPtrs, sizeof(funcPtrs), flags, s3eNextpeerInit, s3eNextpeerTerminate, 0);
}

#if !defined S3E_BUILD_S3ELOADER

#if defined S3E_EDK_USE_STATIC_INIT_ARRAY
int s3eNextpeerStaticInit()
{
    void** p = g_StaticInitArray;
    void* end = p + g_StaticArrayLen;
    while (*p) p++;
    if (p < end)
        *p = (void*)&s3eNextpeerRegisterExt;
    return 0;
}

int g_s3eNextpeerVal = s3eNextpeerStaticInit();

#elif defined S3E_EDK_USE_DLLS
S3E_EXTERN_C S3E_DLL_EXPORT void RegisterExt()
{
    s3eNextpeerRegisterExt();
}
#endif

#endif
