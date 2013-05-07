/****************************************************************************
 
 P R O P R I E T A R Y   N O T I C E
 
 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.
 
 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED
 
 ****************************************************************************/

#import <Foundation/Foundation.h>
#import <SystemConfiguration/SystemConfiguration.h>
#import "JoobMobileReachability.h" 
#import "JoobMobileHttpResult.h"
#import "JoobMobileAuthenticationDelegate.h"
#import "JoobMobileMessage.h"
#import "JoobMobileConnectionDelegate.h"

@protocol JoobMobileDatatankDelegate <NSObject>
@required
- (void)dataCommitted:(id)returnedURL;
@end

@interface JoobMobileDataTank : NSObject <JoobMobileConnectionDelegate, JoobMobileAuthenticationDelegate> {

}

@property (retain) id <JoobMobileDatatankDelegate> delegate;
@property (retain) JoobMobileReachability* reachability;
@property (assign) NetworkStatus networkStatus;

// Used to keep track of whether or not this client has authenticated and pause the queue if appropriate
// Start by assuming we're authenticated.
@property (assign) bool isAuthenticated;


// Method to access singleton instance
+ (id)sharedDataTankManager;


// Method to remove messages from the queue
- (void)deleteObjectFromQueue:(NSString*)key;


// Method to check network is active
- (BOOL)networkActive;


/**
 Let the data tank know that credentials have been updated so it can attempt to continue processing
 following a failed authentication error. This method must be called following a failed authentication attempt
 or the data tank will never resume processing.
 **/
- (void)credentialsUpdated;


/**
 Processes the queue, if appropriate, on a new thread.
 This method may be called multiple times but queue processing will only ever
 be running once at any given time.
 */
-(void) tryProcessQueue;


/**
 Used by the framework itself to forcibly fail a message.
 */
- (void)failMessage:(JoobMobileHttpResult*)result;

@end