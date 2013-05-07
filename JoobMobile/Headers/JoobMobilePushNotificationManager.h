/****************************************************************************
 
 P R O P R I E T A R Y   N O T I C E
 
 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.
 
 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED
 
 ****************************************************************************/

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "JoobMobile.h"

/**
 Implement this delegate to be notified when push notifications are received.
 */
@protocol JoobMobilePushNotificationDelegate <NSObject>

@optional

/** 
 A delegate method that is called when a push event is received via the JoobMobile framework.
 */
- (void)pushReceived:(NSDictionary *)pushContents;

/**
* A delegate method that is called when push registration is successful. This includes the registration process
* with Apple and notification to the JoobMobile server itself.
*/
- (void)pushRegistrationSucceeded;

/** 
 A delegate method that is called when a push registration attempt via the JoobMobile framework fails.
 * This includes the registration process with Apple and notification to the JoobMobile server itself.
 */
- (void)pushRegistrationFailed:(NSError *)error;

@end

@interface JoobMobilePushNotificationManager : NSObject <UIApplicationDelegate, JoobMobileDelegate> {
    
}


/**
 The delegate that will be called when push notifications are received.
 */
@property (nonatomic,retain) id<JoobMobilePushNotificationDelegate> delegate;


/**
 Initializes a new JoobMobilePushNotificationManager using the specified delegate.
 */
- (id) initWithDelegate:(id<JoobMobilePushNotificationDelegate>)notificationDelegate;


/**
 Call this method to register for push notifications using the JoobMobile framework. This should only be called from your application delegate
 and the JoobMobilePushNotificationManager instance should be a member variable that will remain for the life time of your application. The below methods must also
 be proxied through to the JoobMobilePushNotificationManager member variable from the application delegate.
 */
- (void)registerForNotifications;


/** 
 The following methods must be proxied through from your application delegate to the JoobMobilePushNotificationManager to enable push notifications.
 */
- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;
- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error;
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo;

@end