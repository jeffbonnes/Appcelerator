/****************************************************************************
 
 P R O P R I E T A R Y   N O T I C E
 
 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.
 
 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED
 
 ****************************************************************************/

#import <Foundation/Foundation.h>


@protocol JoobMobileAuthenticationDelegate <NSObject>

@optional
- (void) authenticationSucceeded;
- (void) authenticationFailed:(NSError*)failureReason;
- (void) logoutCompleted;
- (void) deviceRegistrationRequired;
- (void) deviceRegistrationCompleted;

@end