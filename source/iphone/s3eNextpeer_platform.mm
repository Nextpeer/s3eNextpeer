/*
 * iphone-specific implementation of the s3eNextpeer extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eNextpeer_internal.h"

#include "s3eTypes.h"
#include "s3eEdk.h"
#include "s3eEdk_iphone.h"
#include "IwDebug.h"

// Nextpeer specific
#include "Nextpeer.h"
#include "NextpeerDelegate.h"

/////////////////
//// Generic Callback Methods
/////////////////
s3eResult s3eNextpeerRegisterCallback(s3eNextperCallback cbid, s3eCallback fn, void* pData)
{
    return s3eEdkCallbacksRegister(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_MAX, cbid, fn, pData, 0);
}
s3eResult s3eNextpeerUnRegisterCallback(s3eNextperCallback cbid, s3eCallback fn)
{
    return s3eEdkCallbacksUnRegister(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_MAX, cbid, fn);
}


/////////////////
//// Deallocation callbacks
/////////////////

static void s3eGCReleaseTournamentStartData(uint32 deviceId, int32 notification, void* systemData, void* instance, int32 returnCode, void* data)
{
    s3eNextpeerTournamentStartData* tournamentStartData = (s3eNextpeerTournamentStartData*)systemData;
    if (tournamentStartData && tournamentStartData->m_tournamentUuid) {
        s3eEdkFreeOS(tournamentStartData->m_tournamentUuid);
    }
}


/////////////////
//// Delegates Implementation
/////////////////

@interface S3ENextpeerDelegate : NSObject<NextpeerDelegate> 
{
}
@end

@implementation S3ENextpeerDelegate

-(void)nextpeerDidTournamentStartWithDetails:(NPTournamentStartDataContainer *)tournamentContainer
{
    NSLog(@"[s3eNextpeer] - called nextpeerDidTournamentStartWithDetails with id %@ and time %d", tournamentContainer.tournamentUuid, tournamentContainer.tournamentTimeSeconds);
    
    // Check that someone has registered for this callback
    if (!s3eEdkCallbacksIsRegistered(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_DID_TOURNAMENT_START)) {
        NSLog(@"[s3eNextpeer] - no callback registered for nextpeerDidTournamentStartWithDetails! This should not happen!");
        return;
    }
    
    // Convert the container we got into a struct and then send it along to the callback function
    s3eNextpeerTournamentStartData dataStruct;
    int dlen = strlen([tournamentContainer.tournamentUuid UTF8String]) + 1;
    dataStruct.m_tournamentUuid = (char*)s3eEdkMallocOS(sizeof(char) * dlen);
    
    NSLog(@"[s3eNextpeer] dataStruct address is 0x%x", dataStruct);
    
    strlcpy(dataStruct.m_tournamentUuid, [tournamentContainer.tournamentUuid UTF8String], S3E_NEXTPEER_STRING_MAX_1);
    dataStruct.m_tournamentSeconds = tournamentContainer.tournamentTimeSeconds;
    
    NSLog(@"[s3eNextpeer] dataStruct contains id %s and time %d", dataStruct.m_tournamentUuid, dataStruct.m_tournamentSeconds);

    s3eEdkCallbacksEnqueue(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_DID_TOURNAMENT_START, &dataStruct, 
                           sizeof(s3eNextpeerTournamentStartData), NULL, S3E_FALSE, &s3eGCReleaseTournamentStartData, NULL);
}

-(void)nextpeerDidTournamentEnd
{
    NSLog(@"[s3eNextpeer] - called nextpeerDidTournamentEnd");
    
    // Call the proper callback
    if (s3eEdkCallbacksIsRegistered(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_DID_TOURNAMENT_END)) {
        s3eEdkCallbacksEnqueue(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_DID_TOURNAMENT_END);
    }
    else {
        NSLog(@"[s3eNextpeer] - nextpeerDidTournamentEnd has no callback registered! This should not happen!");
        IwError(("[Nextpeer] nextpeerDidTournamentEnd called but m_didTournamentEndCallback is null"));
    }
}

-(void)nextpeerDashboardWillAppear
{
    NSLog(@"[s3eNextpeer] - called nextpeerDashboardWillAppear");
    if (s3eEdkCallbacksIsRegistered(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_DASHBOARD_WILL_APPEAR)) {
        s3eEdkCallbacksEnqueue(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_DASHBOARD_WILL_APPEAR);
    }
}

-(void)nextpeerDashboardDidAppear
{
    NSLog(@"[s3eNextpeer] - called nextpeerDashboardDidAppear");
    if (s3eEdkCallbacksIsRegistered(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_DASHBOARD_DID_APPEAR)) {
        s3eEdkCallbacksEnqueue(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_DASHBOARD_DID_APPEAR);
    }
}

-(void)nextpeerDashboardWillDisappear
{
    NSLog(@"[s3eNextpeer] - called nextpeerDashboardWillDisappear");
    if (s3eEdkCallbacksIsRegistered(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_DASHBOARD_WILL_DISAPPEAR)) {
        s3eEdkCallbacksEnqueue(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_DASHBOARD_WILL_DISAPPEAR);
    }
}

-(void)nextpeerDashboardDidDisappear
{
    NSLog(@"[s3eNextpeer] - called nextpeerDashboardDidDisappear");
    if (s3eEdkCallbacksIsRegistered(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_DASHBOARD_DID_DISAPPEAR)) {
        s3eEdkCallbacksEnqueue(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_DASHBOARD_DID_DISAPPEAR);
    }
}

@end


/////////////////
//// Globals
/////////////////

// Global Nextpeer delegate
static S3ENextpeerDelegate* g_NextpeerDelegate;




/////////////////
//// Public Functions (Nextpeer)
/////////////////

s3eResult s3eNextpeerInit_platform()
{
    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
}

void s3eNextpeerTerminate_platform()
{
    // Add any platform-specific termination code here
}

void s3eNextpeerInitWithProductKeyAndDelegatesContainer(const char* productKey)
{
    NSString* aProductKey = [NSString stringWithUTF8String:productKey];
    
    if (g_NextpeerDelegate) {
        [g_NextpeerDelegate release];
    }
    
    g_NextpeerDelegate = [[S3ENextpeerDelegate alloc] init];
    
    // Initialize Nextpeer with the product key and our global delegates container
    [Nextpeer initializeWithProductKey:aProductKey andDelegates:[NPDelegatesContainer containerWithNextpeerDelegate:g_NextpeerDelegate]];
}


void s3eNextpeerLaunchDashboard()
{
    // Call the launch dashboard function
    [Nextpeer launchDashboard];
}

void s3eNextpeerDismissDashboard()
{
    // Call the dismissal function
    [Nextpeer dismissDashboard];
}

void s3eNextpeerShutDown()
{
    // Call the Nextpeer shudown function
    [Nextpeer shutdown];
    
    // Delete the current global Nextpeer delegate
    if (g_NextpeerDelegate) {
        [g_NextpeerDelegate release];
        g_NextpeerDelegate = nil;
    }
}

void s3eNextpeerReportScoreForCurrentTournament(uint32 score)
{
    uint32_t aScore = score;
    [Nextpeer reportScoreForCurrentTournament:aScore];
}

s3eBool s3eNextpeerIsCurrentlyInTournament()
{
    BOOL isInTourney = [Nextpeer isCurrentlyInTournament];
    return isInTourney;
}

uint32 s3eNextpeerTimeLeftInTournament()
{
    return [Nextpeer timeLeftInTourament];
}