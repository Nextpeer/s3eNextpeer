/* This file contains the tournament containers, you can use them to get extra details on the tournament which about to start, or the one which ended.
   More over, you can use the NPTournamentCustomMessageContainer for your in-tournament custom messages */


#pragma mark -
#pragma mark NPTournamentCustomMessageContainer
#pragma mark -

/*
 The NPTournamentCustomMessageContainer can be used to create custom notifications and events while engaging the other players
 that are currently playing. The container that is passed contains the sending user's name and image as well as the message being sent.
 The 
 */
@interface NPTournamentCustomMessageContainer : NSObject

// The player name
@property (nonatomic, readonly) NSString* playerName;

// The player's profile image URL
@property (nonatomic, readonly) NSString* playerImageUrl;

// The player image
// @note: This property can sometimes return NIL, this happens if the image for the player that sent the message is unavailable
@property (nonatomic, readonly) UIImage* playerImage;

// The custom message (which past as a buffer)
@property (nonatomic, readonly) NSData* message;

@end

@interface NPTournamentCustomMessageContainer(Creation)

+(id)containerWithDictionary:(NSDictionary*)dictionary;

@end

#pragma mark -
#pragma mark NPTournamentStartDataContainer
#pragma mark -

/*
 The NPTournamentStartDataContainer used to extract some info about the tournament which is about to be played  
 */
@interface NPTournamentStartDataContainer : NSObject 

// The tournament UUID is provided so that your game can identify which tournament needs to be loaded.
// You can find the UUId in the developer dashboard
@property (nonatomic, readonly) NSString* tournamentUuid;

// The tournament display name
@property (nonatomic, readonly) NSString* tournamentName;

// The tournament time to play in seconds
@property (nonatomic, readonly) NSUInteger tournamentTimeSeconds; 

// A tournament specific assigned random seed for the game. All players within the same tournament
// receive the same seed from the tournament (so that their games are matched)
@property (nonatomic, readonly) NSUInteger tournamentRandomSeed;

// A flag that states if the current tournament is game controlled
@property (nonatomic, readonly) BOOL tournamentIsGameControlled;

@end

@interface NPTournamentStartDataContainer(Creation)

+(id)containerWithDictionary:(NSDictionary*)dictionary;

@end

#pragma mark -
#pragma mark NPTournamentEndDataContainer
#pragma mark -

/*
 The NPTournamentEndDataContainer used to extract some info about the tournament which just ended
 */
@interface NPTournamentEndDataContainer : NSObject 

// The tournament UUID is provided so that your game can identify which tournament needs to be loaded.
// You can find the UUId in the developer dashboard
@property (nonatomic, readonly) NSString* tournamentUuid;

// The player name
@property (nonatomic, readonly) NSString* playerName;

// The player total currency amount (after the tournament ended of course).
@property (nonatomic, readonly) NSUInteger currentCurrencyAmount; 

// The player rank in the tournament (where 1 means first, 1..tournamentTotalPlayers)
@property (nonatomic, readonly) NSUInteger playerRankInTournament; 

// The amount of players in the tournament
@property (nonatomic, readonly) NSUInteger tournamentTotalPlayers; 

// The player's score at the end of the tournament
@property (nonatomic, readonly) NSUInteger playerScore;

@end

@interface NPTournamentEndDataContainer(Creation)

+(id)containerWithDictionary:(NSDictionary*)dictionary;

@end