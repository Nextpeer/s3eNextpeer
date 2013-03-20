@class NPNotificationContainer;

// Implement this delegate if you don't want Nextpeer to show standard notifications in all cases.
@protocol NPNotificationDelegate<NSObject>

@optional
////////////////////////////////////////////////////////////
///
/// @note	Return whether or not Nextpeer should display a notification with the provided data.
///			If false is returned, nextpeerHandleDisallowedNotification: gets called
//			If true is returned, nextpeerNotificationWillShow: gets called before the notification appears
///
////////////////////////////////////////////////////////////
- (BOOL)nextpeerIsNotificationAllowed:(NPNotificationContainer *)notice; 

////////////////////////////////////////////////////////////
///
/// @note	Gets called when nextpeerIsNotificationAllowed: returns false. It is recommended to here display some sort of game
///			specific version of the notification based on the notification data
///
////////////////////////////////////////////////////////////
- (void)nextpeerHandleDisallowedNotification:(NPNotificationContainer *)notice;

////////////////////////////////////////////////////////////
///
/// @note	Gets called every time a notification is about to appear
///
////////////////////////////////////////////////////////////
- (void)nextpeerNotificationWillShow:(NPNotificationContainer *)notice;

////////////////////////////////////////////////////////////
///
/// @note	Should return whether Nextpeer can show the welcome banner. Defaults to YES.
///
////////////////////////////////////////////////////////////
- (BOOL)nextpeerShouldShowWelcomeBanner;

@end
