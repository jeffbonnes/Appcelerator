/****************************************************************************
 
 P R O P R I E T A R Y   N O T I C E
 
 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.
 
 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED
 
 ****************************************************************************/

#import <Foundation/Foundation.h>
#import "JoobMobileConnection.h"
#import "JoobMobileAuthenticationDelegate.h"


typedef void (^LoginCompletedBlock)(NSString *result);


@interface JoobMobileAuthentication : NSObject  {
	
}

/**
 A delegate that will be notified of authentication and logoiut progress.
 */
@property (retain, nonatomic) id <JoobMobileAuthenticationDelegate> delegate;

+ (id)sharedAuthenticationManager;

/**
 Initializes a new JoobMobileAuthentication and sets the specified delegate.
 @param authenticationDelegate An object that implements the JoobMobileAuthenticationDelegate protocol.
 @return A new JoobMobileAuthentication.
 */
- (id) initWithDelegate:(id<JoobMobileAuthenticationDelegate>)authenticationDelegate;


- (void)authenticate:(NSDictionary *)authenticationInformation;

/**
 Called by the public JoobMobile class to perform a initial server side login attempt.
 @param url The root JoobMobile endpoint.
 */
- (void) login:(NSURL*)url onSuccess:(LoginCompletedBlock)successBlock onFailure:(LoginCompletedBlock)failureBlock withTimeout:(int)timeout;

/**
 Logs the client out of Joob Mobile.
 A server side and client side logout will occur.
 */
- (void) logout;

/**
 Raises an authentication status event via the notification center with the supplied status and reason.
 */
+ (void) sendAuthenticationEvent:(NSString *)status withReason:(NSString *)reason;

/**
* Posts response to the JoobMobile server to register the device.
*/
-(void) registerDevice:(NSString *)token endpoint:(NSURL*)url;

/**
 Returns true if there has been a token generated from a previous login.
 */
+ (BOOL) hasAuthenticated;

/**
 Used by the datatank to get the root document.
 */
- (void) getRootDocument:(int)timeout;

@end
