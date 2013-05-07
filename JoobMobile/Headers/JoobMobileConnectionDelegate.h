/****************************************************************************
 
 P R O P R I E T A R Y   N O T I C E
 
 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.
 
 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED
 
 ****************************************************************************/

#import <Foundation/Foundation.h>
#import "JoobMobileHttpResult.h"

@protocol JoobMobileConnectionDelegate <NSObject>
@required
/**
 The request failed delegate method gets fired when an HTTP error is encountered.
 @returns ident The request identifier is passed back to the delegate method.
 */
- (void)httpRequestFailed:(NSString*)requestUuid;


/**
 The request recieved delegate method gets fired when an HTTP request is successful.
 @returns httpResult A JoobMobileHttpResult object is passed back to the delegate method.
 */
- (void)httpResultReceived:(JoobMobileHttpResult*)httpResult;

@end