#import <Foundation/Foundation.h>

@class NPInGameNotification;

@interface NPNotificationContainer : NSObject 
{
@private
    NPInGameNotification* mNotification;
    UIImage* mRenderedImage;
}

@property (nonatomic, readonly) NSString* notificationText;
@property (nonatomic, readonly) UIImage* renderedImage;

@end
