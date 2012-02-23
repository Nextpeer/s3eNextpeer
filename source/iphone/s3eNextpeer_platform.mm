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
//// Delegates Implementation
/////////////////

@interface S3ENextpeerDelegate : NSObject<NextpeerDelegate> 
{
    s3eNextpeerCBDidTournamentStartWithDetails m_didTournamentStartCallback;
    s3eNextpeerCBDidTournamentEnd m_didTournamentEndCallback;
}
-(id)initWithS3EDelegatesContainer:(const s3eNextpeerDelegatesContainer*)delegatesContainer;

@end

@implementation S3ENextpeerDelegate

-(id)initWithS3EDelegatesContainer:(const s3eNextpeerDelegatesContainer*)delegatesContainer
{
    if ((self = [super init])) {
        m_didTournamentStartCallback = delegatesContainer->m_NextpeerDelegate.m_didTournamentStartCallback;
        m_didTournamentEndCallback = delegatesContainer->m_NextpeerDelegate.m_didTournamentEndCallback;
    }
    
    return self;
}

-(void)nextpeerDidTournamentStartWithDetails:(NPTournamentStartDataContainer *)tournamentContainer
{
    // Convert the container we got into a struct and then send it along to the callback function
    // NOTE: the callee is in charge of deallocating the memory for this container struct
    s3eNextpeerTournamentStartData* dataStruct = (s3eNextpeerTournamentStartData*)s3eEdkMallocOS(sizeof(s3eNextpeerTournamentStartData), TRUE);
    
    strcpy(dataStruct->m_tournamentUuid, [tournamentContainer.tournamentUuid UTF8String]);
    dataStruct->m_tournamentSeconds = tournamentContainer.tournamentTimeSeconds;
    
    if (m_didTournamentStartCallback) {
        m_didTournamentStartCallback(dataStruct);
    }
    else {
        IwError(("[Nextpeer] nextpeerDidTournamentStartWithDetails called but m_didTournamentStartCallback was null"));
        s3eEdkFreeOS(dataStruct);
    }
}

-(void)nextpeerDidTournamentEnd
{
    // Call the proper callback
    if (m_didTournamentEndCallback) {
        m_didTournamentEndCallback();
    }
    else {
        IwError(("[Nextpeer] nextpeerDidTournamentEnd called but m_didTournamentEndCallback is null"));
    }
}

@end


/////////////////
//// Globals
/////////////////

// Global Nextpeer delegate
static S3ENextpeerDelegate* g_NextpeerDelegate;




/////////////////
//// Functions
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

void s3eNextpeerInitWithProductKeyAndDelegatesContainer(const char* productKey, const s3eNextpeerDelegatesContainer* delegatesContainer)
{
    NSString* aProductKey = [NSString stringWithUTF8String:productKey];
    
    if (g_NextpeerDelegate) {
        [g_NextpeerDelegate release];
    }
    
    g_NextpeerDelegate = [[S3ENextpeerDelegate alloc] initWithS3EDelegatesContainer:delegatesContainer];
    
    // Initialize Nextpeer with the product key and our global delegates container
    [Nextpeer initializeWithProductKey:aProductKey andDelegates:[NPDelegatesContainer containerWithNextpeerDelegate:g_NextpeerDelegate]];
}


void s3eNextpeerLaunchDashboard()
{
    // Call the launch dashboard function
    [Nextpeer launchDashboard];
}


void s3eNextpeerShutDown()
{
    // Call the Nextpeer shudown function
    [Nextpeer shutdown];
}
