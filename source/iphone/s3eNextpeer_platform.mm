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

// Forward declarations
static void s3eGCReleaseOpenURLData(uint32 deviceId, int32 notification, void* systemData, void* instance, int32 returnCode, void* data);

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
//// openURL callback (from UIApplication)
/////////////////

static int32 s3eNextpeerOpenURLCallback(void* systemData, void* userData)
{
    NSLog(@"[s3eNextpeer] - handleOpenURL callback invoked with URL: %@", (NSURL*)systemData);
    
    // Invoke an app callback
    if (s3eEdkCallbacksIsRegistered(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_OPEN_URL_CALLED)) {

        NSLog(@"[s3eNextpeer] - handleOpenURL app callback found will invoke it");
        
        NSURL* url = (NSURL*)systemData;
        NSString* urlStr = [url description];
        int len = strlen([urlStr UTF8String]) + 1;
        char* buf = (char*)s3eEdkMallocOS(sizeof(char) * len);
        strlcpy(buf, [urlStr UTF8String], S3E_NEXTPEER_STRING_MAX_2);
        
        s3eEdkCallbacksEnqueue(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_OPEN_URL_CALLED, buf, len, NULL, S3E_FALSE, &s3eGCReleaseOpenURLData, NULL);
    }
    
    return 0;
}

void s3eNextpeerRegisterOpenURLCallback()
{
    // Init a callback for handleOpenURL
    NSLog(@"[s3eNextpeer] - registering openURL callback function");
    s3eEdkCallbacksRegisterInternal(S3E_EDK_INTERNAL, S3E_EDK_CALLBACK_MAX, S3E_EDK_IPHONE_HANDLEOPENURL, s3eNextpeerOpenURLCallback, NULL, S3E_FALSE);   
}

/////////////////
//// Local and Push related functions
/////////////////
static void s3eNextpeerRegiserDeviceToken()
{
    // Ask for a device token from the user
    const char* token = s3eEdkAppGetRemoteNotificationToken();
    
    if (!token) {
        NSLog(@"[s3eNextpeer] Device provided NULL device token, push will not be possible for this device");
        return;
    }
    
    // Make sure the token we've received isn't an empty string (happens sometimes on error)
    if (!strlen(token)) {
        NSLog(@"[s3eNextpeer] Device provided empty device token, push will not be possible for this device");
        return;
    }
    
    NSLog(@"[s3eNextpeer] Device token for device is (from Marmalade) %s", token);
    
    // Convert token from string form to raw binary form
    // For example - "378b98a9 d7e21860 a4b6697e 51b4a3c2 561c78ec d0438f9b b2c97d14 2eb750e0"
    NSMutableData* tokenData = [[NSMutableData alloc] init];
    unsigned char singleByte = 0;
    char charPair[3] = { 0, 0, 0 };
    unsigned int len = strlen(token);
    unsigned int i = 0;
    
    while (i < len-1) {
        // Skip any spaces in the device token
        if (token[i] == ' ') {
            i++;
            continue;
        }
        
        // Create pair of hex chars for conversion (i.e. 'ab' or '1f')
        charPair[0] = token[i];
        charPair[1] = token[i+1];
        
        // Convert and append single byte
        singleByte = strtol(charPair, NULL, 16);
        [tokenData appendBytes:&singleByte length:sizeof(singleByte)];
        
        i += 2;
    }
    
    [Nextpeer registerDeviceToken:tokenData];
    [tokenData release];
}

static void s3eNextpeerHandleInitialNotifications()
{
    // Check for push notification that may have started the app
    NSDictionary* pushNotice = (NSDictionary*)s3eEdkAppGetInitialRemoteNotification();
    if (pushNotice) {
        [Nextpeer handleRemoteNotification:pushNotice];
        s3eEdkAppReleaseInitialRemoteNotification();
        return;
    }
    
    // Check if we have an initial local notification instead
    UILocalNotification* localNotice = (UILocalNotification*)s3eEdkAppGetInitialLocalNotification();
    if (localNotice) {
        [Nextpeer handleLocalNotification:localNotice];
        s3eEdkAppReleaseInitialLocalNotification();
        return;
    }
}

static int32 s3eNextpeerRemoteNotificationCallback(void* systemData, void* userData)
{
    NSLog(@"[s3eNextpeer] Received remote notification whilst running");    
    UILocalNotification* notification = (UILocalNotification*)systemData;
    
    if (notification) {
        [Nextpeer handleLocalNotification:notification];
    }
    
    return 0;
}

static int32 s3eNextpeerLocalNotificationCallback(void* systemData, void* userData)
{
    NSLog(@"[s3eNextpeer] Received local notification whilst running");    
    NSDictionary* notification = (NSDictionary*)systemData;
    
    if (notification) {
        [Nextpeer handleRemoteNotification:notification];
    }
    
    return 0;
}


static void s3eNextpeerRegisterNotificationCallbacks()
{
    NSLog(@"[s3eNextpeer] registering notification callbacks");
    s3eEdkCallbacksRegisterInternal(S3E_EDK_INTERNAL, S3E_EDK_CALLBACK_MAX, S3E_EDK_IPHONE_DID_RECEIVE_REMOTE_NOTIFICATION, s3eNextpeerRemoteNotificationCallback, NULL, S3E_FALSE);
    
    s3eEdkCallbacksRegisterInternal(S3E_EDK_INTERNAL, S3E_EDK_CALLBACK_MAX, S3E_EDK_IPHONE_DID_RECEIVE_LOCAL_NOTIFICATION, s3eNextpeerRemoteNotificationCallback, NULL, S3E_FALSE);
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

static void s3eGCReleaseCustomMessageData(uint32 deviceId, int32 notification, void* systemData, void* instance, int32 returnCode, void* data)
{
    s3eNextpeerCustomMessageData* customMessageData = (s3eNextpeerCustomMessageData*)systemData;
    if (customMessageData) {
        if (customMessageData->m_playerName) {
            s3eEdkFreeOS(customMessageData->m_playerName);
        }
        if (customMessageData->m_dataReceived) {
            s3eEdkFreeOS(customMessageData->m_dataReceived);
        }
        if (customMessageData->m_playerImageData) {
            s3eEdkFreeOS(customMessageData->m_playerImageData);
        }
    }
}

static void s3eGCReleaseOpenURLData(uint32 deviceId, int32 notification, void* systemData, void* instance, int32 returnCode, void* data)
{
    char* url = (char*)systemData;
    if (url) {
        s3eEdkFreeOS(url);
    }
}

static void s3eGCReleaseCurrencyAmount(uint32 deviceId, int32 notification, void* systemData, void* instance, int32 returnCode, void* data)
{
    // Leave blank for now
}


/////////////////
//// Obj-C Globals
/////////////////

// Global flag for unified virtual currency support
static BOOL g_UnifiedVirtualCurrencySupport = FALSE;

// Global unified currency amount which is set when the dashboard is launched
static NSUInteger g_UnifiedVirtualCurrencyAmount = 0;


/////////////////
//// Delegates Implementation
/////////////////

@interface S3ENextpeerDelegate : NSObject<NextpeerDelegate, NPCurrencyDelegate> 
{
}
@end

@implementation S3ENextpeerDelegate

-(void)_convertTournamentContainer:(NPTournamentStartDataContainer *)tournamentContainer toDataStruct:(s3eNextpeerTournamentStartData*)dataStruct
{
    int dlen = strlen([tournamentContainer.tournamentUuid UTF8String]) + 1;
    dataStruct->m_tournamentUuid = (char*)s3eEdkMallocOS(sizeof(char) * dlen);
    
    strlcpy(dataStruct->m_tournamentUuid, [tournamentContainer.tournamentUuid UTF8String], S3E_NEXTPEER_STRING_MAX_1);
    dataStruct->m_tournamentSeconds = tournamentContainer.tournamentTimeSeconds;
}

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
    [self _convertTournamentContainer:tournamentContainer toDataStruct:&dataStruct];
    
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

-(void)nextpeerDashboardDidReturnToGame
{
    NSLog(@"[s3eNextpeer] - called nextpeerDashboardDidReturnToGame");
    if (s3eEdkCallbacksIsRegistered(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_DASHBOARD_RETURN_TO_GAME)) {
        s3eEdkCallbacksEnqueue(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_DASHBOARD_RETURN_TO_GAME);
    }
}

-(void)nextpeerWillTournamentStartWithDetails:(NPTournamentStartDataContainer *)tournamentContainer
{
    NSLog(@"[s3eNextpeer] - called nextpeerWillTournamentStartWithDetails");
    if (s3eEdkCallbacksIsRegistered(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_WILL_TOURNAMENT_START)) {   
        s3eNextpeerTournamentStartData startData;
        [self _convertTournamentContainer:tournamentContainer toDataStruct:&startData];
        
        s3eEdkCallbacksEnqueue(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_WILL_TOURNAMENT_START, &startData, 
                               sizeof(s3eNextpeerTournamentStartData), NULL, S3E_FALSE, &s3eGCReleaseTournamentStartData, NULL);
    }
}

-(void)nextpeerDidReceiveCustomMessage:(NPTournamentCustomMessageContainer *)message
{
    NSLog(@"[s3eNextpeer] - called nextpeerDidReceiveCustomMessage");
    
    if (s3eEdkCallbacksIsRegistered(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_DID_RECEIVE_CUSTOM_MESSAGE)) {   
        s3eNextpeerCustomMessageData messageData;
        
        // Copy the data over
        int nameLen = strlen([message.playerName UTF8String]) + 1;
        messageData.m_playerName = (char*)s3eEdkMallocOS(sizeof(char)*nameLen);
        strlcpy(messageData.m_playerName, [message.playerName UTF8String], S3E_NEXTPEER_STRING_MAX_1);
        
        messageData.m_dataReceivedLen = [message.message length];
        messageData.m_dataReceived = s3eEdkMallocOS(messageData.m_dataReceivedLen);
        [message.message getBytes:messageData.m_dataReceived length:messageData.m_dataReceivedLen];
        
        UIImage* senderImage = message.playerImage;
        void* imageData = 0;
        uint32 imageDataLen = 0;
        
        if (senderImage) {
            NSData* senderImageData = UIImagePNGRepresentation(senderImage);
            if (senderImageData) {
                imageDataLen = [senderImageData length];
                imageData = s3eEdkMallocOS(imageDataLen);
                [senderImageData getBytes:imageData length:imageDataLen];
            }
        }

        messageData.m_playerImageData = imageData;
        messageData.m_playerImageDataLen = imageDataLen;
        
        // Call the callback
        s3eEdkCallbacksEnqueue(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_DID_RECEIVE_CUSTOM_MESSAGE, &messageData, 
                               sizeof(s3eNextpeerCustomMessageData), NULL, S3E_FALSE, &s3eGCReleaseCustomMessageData, NULL);
    }
}

// Methods for VCurrency
- (BOOL)nextpeerSupportsUnifiedCurrency
{
    return g_UnifiedVirtualCurrencySupport;
}

- (NSUInteger)nextpeerGetCurrency
{
    return g_UnifiedVirtualCurrencyAmount;
}

-(void)nextpeerAddAmountToCurrency:(NSInteger)amount
{
    g_UnifiedVirtualCurrencyAmount += amount;
    
    // Also notify the game it needs to update the current amount of currency
    if (s3eEdkCallbacksIsRegistered(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_VCURRENCY_ADD_CURRENCY_AMOUNT)) {   
        int32 currencyAmount = amount;
        
        s3eEdkCallbacksEnqueue(S3E_EXT_NEXTPEER_HASH, S3E_NEXTPEER_CALLBACK_VCURRENCY_ADD_CURRENCY_AMOUNT, &currencyAmount, sizeof(currencyAmount), 
                               NULL, S3E_FALSE, &s3eGCReleaseCurrencyAmount, NULL);
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

void s3eNextpeerInitWithProductKey(const char* productKey)
{
    NSString* aProductKey = [NSString stringWithUTF8String:productKey];
    
    if (g_NextpeerDelegate) {
        [g_NextpeerDelegate release];
    }
    
    g_NextpeerDelegate = [[S3ENextpeerDelegate alloc] init];
    
    // Initialize Nextpeer with the product key and our global delegates container
    NPDelegatesContainer* delegatesContainer = [NPDelegatesContainer containerWithNextpeerDelegate:g_NextpeerDelegate];
    delegatesContainer.currencyDelegate = g_NextpeerDelegate; // add vcurrency delegate
    
    [Nextpeer initializeWithProductKey:aProductKey andDelegates:delegatesContainer];
    
    // Register any device tokens
    s3eNextpeerRegiserDeviceToken();
    
    // Setup callbacks for notifications
    s3eNextpeerRegisterNotificationCallbacks();
}

void s3eNextpeerLaunchDashboard()
{
    // Call the launch dashboard function
    [Nextpeer launchDashboard];
}

void s3eNextpeerLaunchDashboardWithCurrencyAmount(uint32 unifiedVirtualCurrencyAmount)
{
    g_UnifiedVirtualCurrencyAmount = unifiedVirtualCurrencyAmount;
    s3eNextpeerLaunchDashboard();
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

void s3eNextpeerReportForfeitForCurrentTournament()
{
    [Nextpeer reportForfeitForCurrentTournament];
}

void s3eNextpeerPushDataToOtherPlayers(const void* data, uint32 length)
{
    NSData* aData = [NSData dataWithBytes:data length:length];
    
    [Nextpeer pushDataToOtherPlayers:aData];
}

void s3eNextpeerPushNotificationToOtherPlayers(const char * notice)
{
    NSString* aNotice = [NSString stringWithUTF8String:notice];
    [Nextpeer pushMessageToOtherPlayers:aNotice];
}

void s3eNextpeerHandleOpenURL(void* url)
{
    if (!url) {
        return;
    }
    
    NSURL* aURL = (NSURL*)url;
    [Nextpeer handleOpenURL:aURL];
}

/////////////////
//// Public Functions (Virtual Currency)
/////////////////

void s3eNextpeerSetUnifiedVirtualCurrencySupport(s3eBool unifiedVirtualCurrencySupported)
{
    g_UnifiedVirtualCurrencySupport = unifiedVirtualCurrencySupported;
}


