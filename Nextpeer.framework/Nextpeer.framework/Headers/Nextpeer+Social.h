#import "NPSocialContainers.h"

////////////////////////////////////////////////////////////
///
/// Public Nextpeer API - Social
///
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
///
/// Use this method to invoke the Facebook post dialog. 
/// The user will be promped to login if she hasn't done that before.
///
/// @param message Message to be displayed on the wall. Must be specified.
/// @param link Link for the given post. Could link to anywhere. If nil then the link would be to the app's iTunes page (what was specified in Nextpeer's dashboard).
/// @param imageUrl Url for an image to be displayed on the post. If nil then the image is the app's icon as it appears in Nextpeer's dashboard.
///
////////////////////////////////////////////////////////////

+ (void)postToFacebookWallMessage:(NSString*)message link:(NSString*)link imageUrl:(NSString*)imageUrl;

////////////////////////////////////////////////////////////
///
/// Use this method to retrieve the current player details such as name and image.
///
/// @note: If the user never opened Nextpeer's dashboard or Nextpeer was not initialized the method will return NIL.
////////////////////////////////////////////////////////////
+ (NPGamePlayerContainer *)getCurrentPlayerDetails;