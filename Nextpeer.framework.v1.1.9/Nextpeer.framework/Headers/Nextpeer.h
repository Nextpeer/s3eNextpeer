////////////////////////////////////////////////////////////
///
/// Public Nextpeer API
///
////////////////////////////////////////////////////////////

#pragma once

#import <UIKit/UIKit.h>

// Importing the public headers
#import "NextpeerSettings.h"
#import "NextpeerDelegate.h"
#import "NPNotificationDelegate.h"
#import "NPTournamentDelegate.h"
#import "NPDelegatesContainer.h"
#import "NPNotificationContainer.h"
#import "NPTournamentContainers.h"
#import "NPCurrencyDelegate.h"

// Defines where notifications can appear on the screen
typedef enum NPNotificationPosition
{
    // For iPhone + iPad
	NPNotificationPosition_TOP = 0, // Default notification position
	NPNotificationPosition_BOTTOM,
    
    // For iPad only
	NPNotificationPosition_TOP_LEFT,
	NPNotificationPosition_BOTTOM_LEFT,
	NPNotificationPosition_TOP_RIGHT,
	NPNotificationPosition_BOTTOM_RIGHT,
	NPNotificationPosition_COUNT,
} NPNotificationPosition;

typedef void(^NPPostLaunchAction)(void);

@interface Nextpeer : NSObject
{
@protected
	UIWindow* mPresentationWindow;
	
	NPDelegatesContainer* mDelegatesContainer;
	id<NextpeerDelegate> mLaunchDelegate;
	
    NSString* mProductKey;
	NSString* mOverrideDisplayName;
	
	UIInterfaceOrientation mPreviousOrientation;
	UIInterfaceOrientation mDashboardOrientation;
	UIInterfaceOrientation mNotificationOrientation;
	NPNotificationPosition mNotificationPosition;
	
	BOOL mIsDashboardDismissing;
    BOOL mShouldAutoRegister;
    BOOL mInGame;
    BOOL mGameSupportsRetina;
    BOOL mGameSupportsUnifiedCurrency;
	
	UINavigationController *mRootNavigationController;
	
    NPPostLaunchAction mPostAction;
    
	void* mReservedMemory;
		
	struct {
		unsigned int isHidingDashboard:1;
		unsigned int isDismissingDashboard:1;
		unsigned int isShowingDashboard:1;
		unsigned int isDashboardVisible:1;
		unsigned int shouldReloadDashboardAfterBackground:1;
		unsigned int shouldReloadDashboard:1;
		unsigned int shouldStartTournamentAfterHiding:1;
        unsigned int didDisplayRemoteNotice:1;
	} _nextPeerFlags;
}

////////////////////////////////////////////////////////////
///
/// @return: The release Version String of the Nextpeer client library in use.
///
////////////////////////////////////////////////////////////
+ (NSString*)releaseVersionString;

////////////////////////////////////////////////////////////
///
/// @param: productKey is copied. This is your unique product key you received when registering your application.
/// @param: delegatesContainer is retained but none of the delegates in the container are retained. 
///
////////////////////////////////////////////////////////////
+ (void) initializeWithProductKey:(NSString*)productKey 
					 andDelegates:(NPDelegatesContainer*)delegatesContainer;

////////////////////////////////////////////////////////////
///
/// @param: productKey is copied. This is your unique product key you received when registering your application.
/// @param: settings is copied. The available settings are defined as NextpeerSettingXXXXXXXXXXXX. See NextpeerSettings.h
/// @param: delegatesContainer is retained but none of the delegates in the container are retained. 
///
///
////////////////////////////////////////////////////////////
+ (void) initializeWithProductKey:(NSString*)productKey 
					  andSettings:(NSDictionary*)settings 
					 andDelegates:(NPDelegatesContainer*)delegatesContainer;

////////////////////////////////////////////////////////////
///
/// Shuts down Nextpeer
///
////////////////////////////////////////////////////////////
+ (void) shutdown;

////////////////////////////////////////////////////////////
///
/// Launches the Nextpeer Dashboard view at the top of your application's keyed window.
///
/// @note:	If [Nextpeer isNextpeerSupported] returns NO this method will not execute.
///         If the player has not yet authorized your app, they will be prompted to setup an 
///			account or authorize your application before accessing the Nextpeer dashboard
///
////////////////////////////////////////////////////////////
+ (void) launchDashboard;

////////////////////////////////////////////////////////////
///
/// Removes the Nextpeer Dashboard from your application's keyed window.
///
////////////////////////////////////////////////////////////
+ (void) dismissDashboard;

////////////////////////////////////////////////////////////
///
/// This method is used to push a buffer to the other players.
/// This can potentially be used to create custom notifications or some other interactive mechanism
/// that incorporates the other players. The buffer will be sent to the other players and will activate the 
/// -(void)nextpeerDidReceiveTournamentCustomMessage: method on their NPTournamentDelegate delegate.
///
////////////////////////////////////////////////////////////
+ (void)pushDataToOtherPlayers:(NSData*)data;

////////////////////////////////////////////////////////////
///
/// This method will broadcast a notification to the other players in the tournament.
/// The current player's image will be displayed along with the text.
/// 
/// To use the current player's name in the message use %PLAYER_NAME%.
/// E.g @"%PLAYER_NAME% sent you a bomb!"
///
////////////////////////////////////////////////////////////
+ (void)pushMessageToOtherPlayers:(NSString*)message;

////////////////////////////////////////////////////////////
///
/// Call this method to report the current score for the tournament. This allows Nextpeer to send
/// various notifications about the players' scores.
///
////////////////////////////////////////////////////////////
+ (void)reportScoreForCurrentTournament:(uint32_t)score;

////////////////////////////////////////////////////////////
///
/// Call this method to check if any tournament is running at the moment.
///
////////////////////////////////////////////////////////////
+ (BOOL) isCurrentlyInTournament;

////////////////////////////////////////////////////////////
///
/// Call this method to report the player has failed the current tournament (AKA "Game Over"). Nextpeer will display a popup dialog, allowing the user 
/// to chose whether he\she would like to retry or to forfeit the current tournament. 
///
/// @note: If the user would like to retry, Nextpeer will invoke the retrySelector parameter,
//		   otherwise, Nextpeer will invoke the forfeitSelector parameter
///
// @deprecated Will be removed in the next major version. Build your own custom end menu, report to 'reportForfeitForCurrentTournament' if the user wish to end game.
////////////////////////////////////////////////////////////
+ (void)displayGameEndedWithTarget:(id)target withForfeitSelector:(SEL)forfeitSelector andRetrySelector:(SEL)retrySelector DEPRECATED_ATTRIBUTE;;

////////////////////////////////////////////////////////////
///
/// Call this method when the user wishes to exit the current tournament. 
/// This will close any in-game notifiactions and dialogs. 
///
////////////////////////////////////////////////////////////
+ (void) reportForfeitForCurrentTournament;

////////////////////////////////////////////////////////////
///
/// Call this method when you wish to change the notification orientation in run time.
/// It's preferable to use the settings dictionary if you wish to set this up at start-time.
///
////////////////////////////////////////////////////////////
+ (void) setNotificationOrientation:(UIInterfaceOrientation)orientation;

////////////////////////////////////////////////////////////
///
/// This method will return the amount of seconds left for this tournament.
/// @note: If no tournament is currently taking place then this method will return 0.
///
////////////////////////////////////////////////////////////
+ (NSUInteger)timeLeftInTournament;

////////////////////////////////////////////////////////////
///
/// Let the platform handle a url request
/// Call this mehtod from your UIApplicationDelegate: pre 4.2 support handleOpenURL and for For 4.2+ support, application:openURL:sourceApplication:annotation:
/// @parm url - the URL that was passed to the application delegate's handleOpenURL method(s).
/// @note: The platform may call '[Nextpeer launchDashboard]' under some scenarios
/// @return: YES if the url starts with np[app_id] and the sdk handled the request; NO if the attempt to handle the URL failed (not supported by the platform).
///
////////////////////////////////////////////////////////////
+ (BOOL)handleOpenURL:(NSURL *)url;

////////////////////////////////////////////////////////////
/// 
/// Call this method to verify if the current run time environment supports Nextpeer requirements.
///
/// @note: Minimum iOS version supported by the SDK is iOS 4.0. You can handle such case by implementing NextpeerDelegate method 
///		   nextpeerNotSupportedShouldShowCustomError (otherwise Nextpeer will display alert).
/// @return: YES if the run time requirements match, NO otherwise.
///
////////////////////////////////////////////////////////////
+ (BOOL)isNextpeerSupported;

////////////////////////////////////////////////////////////
/// 
/// Call this method register this user's device token. This will allow Nextpeer to send invitations to this user
/// when he/she is invited to play the current game. Note that this is only relevant if you've followed the push notification
/// integration instructions and provided the p12 file for your game.
///
/// @example
/// - (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
///     // Updates the device token and registers the token with Nextpeer
///     [Nextpeer registerDeviceToken:deviceToken];
/// }
///
////////////////////////////////////////////////////////////
+ (void)registerDeviceToken:(NSData*)deviceToken;

////////////////////////////////////////////////////////////
/// 
/// Call this method after the launching of the app. This allows Nextpeer to respond to any push or local notifications
/// that may have been received when the app was in the background.
/// Note that you will need to call this method after Nextpeer has already been initialized.
///
/// @return Returns a boolean value indicating if the notification will be handled by Nextpeer
///
/// @example
/// - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions { 
///     ...
///     [Nextpeer initializeWithProductKey...];
///     ...
///     [Nextpeer handleLaunchOptions:launchOptions];
///     ...
///     
/// }
///
////////////////////////////////////////////////////////////
+ (BOOL)handleLaunchOptions:(NSDictionary*)launchOptions;

////////////////////////////////////////////////////////////
/// 
/// Call this method after the receiving a remote push notification while the app is running.
/// that may have been received when the app was off.
///
/// @return Returns a boolean value indicating if the notification will be handled by Nextpeer
///
/// @example
/// - (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo {
///     ...
///     [Nextpeer handleRemoteNotification:userInfo];
///     ...
///     
/// }
///
////////////////////////////////////////////////////////////
+ (BOOL)handleRemoteNotification:(NSDictionary*)userInfo;

////////////////////////////////////////////////////////////
/// 
/// Call this method after the receiving a remote push notification while the app is running.
/// that may have been received when the app was off.
///
/// @return Returns a boolean value indicating if the notification will be handled by Nextpeer
///
/// @example
/// - (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification {
///     ...
///     [Nextpeer handleLocalNotification:userInfo];
///     ...
///     
/// }
///
////////////////////////////////////////////////////////////
+ (BOOL)handleLocalNotification:(UILocalNotification*)notification;



@end
