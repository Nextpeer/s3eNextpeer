#pragma once

#import "NPTournamentContainers.h"

@protocol NextpeerDelegate<NSObject>

////////////////////////////////////////////////////////////
///
/// @note   This method will be called when a tournament is about to start.
///         The tournament start container will give you some details on the tournament which is about to be played.
///         For example the tournament uuid, name and time.
////////////////////////////////////////////////////////////
-(void)nextpeerDidTournamentStartWithDetails:(NPTournamentStartDataContainer *)tournamentContainer;

////////////////////////////////////////////////////////////
///
/// @note   This method is invoked whenever the current tournament has finished.
///         In here you can place some cleanup code. For example, 
///			you can use this method to recycle the game scene.
///
////////////////////////////////////////////////////////////
-(void)nextpeerDidTournamentEnd;

@optional

// All of the delegate methods below are optional.
// Implement them only when you need to more finely control Nextpeer's behavior.

////////////////////////////////////////////////////////////
///
/// @note   Use this function to tell the SDK whether you support the given tournament. This method
///         is called once for each tournament uuid that is present in the dashboard. If this particular
///         game version doesn't support a certain tournament, use this function to tell the SDK to disable it.
///         
///         Return TRUE if you support this tournament and FALSE otherwise (Default TRUE).
///
////////////////////////////////////////////////////////////
-(BOOL)nextpeerSupportsTournamentWithId:(NSString* )tournamentUuid;

////////////////////////////////////////////////////////////
///
/// @note  This method will be called in case Nextpeer is not supported on the device.
///		   If you will return TRUE we will not show our error view and let you the opportunity to intervene.
//         (Default FALSE -> We will show UIAlertView).
///
////////////////////////////////////////////////////////////
-(BOOL)nextpeerNotSupportedShouldShowCustomError;

////////////////////////////////////////////////////////////
///
/// @note We will call it when the before the tournament will start (prior the dismissing the dashboard)
///
////////////////////////////////////////////////////////////
- (void)nextpeerWillTournamentStartWithDetails:(NPTournamentStartDataContainer *)tournamentContainer;

////////////////////////////////////////////////////////////
///
/// @note This is where you should pause your game.
///
////////////////////////////////////////////////////////////
- (void)nextpeerDashboardWillAppear;

////////////////////////////////////////////////////////////
///
/// @note This method is invoked when the dashboard has finished its animated transition and is now fully visible.
/// 
////////////////////////////////////////////////////////////
- (void)nextpeerDashboardDidAppear;

////////////////////////////////////////////////////////////
///
/// @note This is where Cocoa based games should unpause and resume playback. 
///
/// @warning	Since an exit animation will play, this will cause negative performance if your game 
///				is rendering on an EAGLView. For OpenGL games, you should refresh your view once and
///				resume your game in nextpeerDashboardDidDisappear
///
////////////////////////////////////////////////////////////
- (void)nextpeerDashboardWillDisappear;

////////////////////////////////////////////////////////////
///
/// @note This is where OpenGL games should unpause and resume playback.
///
////////////////////////////////////////////////////////////
- (void)nextpeerDashboardDidDisappear;

////////////////////////////////////////////////////////////
///
/// @note This method will be called when the player closes Nextpeer's dashboard and returns to the game
///
////////////////////////////////////////////////////////////
- (void)nextpeerDashboardDidReturnToGame;
@end
