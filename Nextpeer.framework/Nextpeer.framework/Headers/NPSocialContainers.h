/* This file contains the social containers, you can use them to get extra details on the current player */

#pragma mark -
#pragma mark NPGamePlayerContainer
#pragma mark -

/*
 The NPGamePlayerContainer can be used to retrieve data on the current player.
 */
@interface NPGamePlayerContainer : NSObject 

// The player name
@property (nonatomic, readonly) NSString* playerName;

// The player image url
@property (nonatomic, readonly) NSString* profileImageUrl;

// The player image
// @note: This property can sometimes return NIL, this happens if the image is unavailable (local cache)
@property (nonatomic, readonly) UIImage* playerImage;

// Whether or not the current player is a Facebook (or Twitter in the future for example) user or not
@property (nonatomic, readonly) BOOL isSocialAuthenticated;

@end

@interface NPGamePlayerContainer(Creation)

+(id)containerWithDictionary:(NSDictionary*)dictionary;

@end
