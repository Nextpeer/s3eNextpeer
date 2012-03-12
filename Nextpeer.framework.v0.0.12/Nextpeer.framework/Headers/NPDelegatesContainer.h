#import "NextpeerDelegate.h"
#import "NPNotificationDelegate.h"
#import "NPTournamentDelegate.h"

@interface NPDelegatesContainer : NSObject
{
	id<NextpeerDelegate>	nextpeerDelegate;
	id<NPNotificationDelegate> notificationDelegate;
    id<NPTournamentDelegate> tournamentDelegate;
}

@property (nonatomic, assign) id<NextpeerDelegate> nextpeerDelegate;
@property (nonatomic, assign) id<NPNotificationDelegate> notificationDelegate;
@property (nonatomic, assign) id<NPTournamentDelegate> tournamentDelegate;

+ (NPDelegatesContainer*)containerWithNextpeerDelegate:(id<NextpeerDelegate>)aNPDelegate;

+ (NPDelegatesContainer*)containerWithNextpeerDelegate:(id<NextpeerDelegate>)aNPDelegate
									tournamentDelegate:(id<NPTournamentDelegate>)aTournamentDelegate;

+ (NPDelegatesContainer*)containerWithNextpeerDelegate:(id<NextpeerDelegate>)aNPDelegate
								notificationDelegate:(id<NPNotificationDelegate>)aNoticeDelegate;

+ (NPDelegatesContainer*)containerWithNextpeerDelegate:(id<NextpeerDelegate>)aNPDelegate
                                  notificationDelegate:(id<NPNotificationDelegate>)aNoticeDelegate 
                                    tournamentDelegate:(id<NPTournamentDelegate>)aTournamentDelegate;


@end
