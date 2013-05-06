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
#import "JoobMobileConnectionDelegate.h"
#import "JoobMobileMultiFactorToken.h"


@interface JoobMobileMultiFactorAuthenticationHandler : NSObject

/**
 Method called when the MFA headers are present in a HTTP response.
 @param httpResult The JoobMobileHttpResult object associated with the request.
 */
- (void) processMultiFactorAuthenticationRequest:(JoobMobileHttpResult*)httpResult;

/**
 Method called from the JoobMobile class to submit the MFA response to the JoobMobile server.
 @param token The token originally passed to the delegate method containing token UUID and message UUID 
 @param response The reponse to the MFA challenge, content dependant on plugin used.
 */
- (void) postMultifactorResponse:(JoobMobileMultiFactorToken *)token  response:(NSDictionary *)response;

/**
 Method to generate a DefaultMultiFactorAuthentication token as per the default MFA plugin shipped with JoobMobile.
 @param token The token as passed to the MFA delegate method when a challenge is presented.
 @param password The password the user entered.
 @returns NSDictionary A dictionary representing the DefaultMultiFactorResponse document.
 */
+ (NSDictionary*)generateDefaultMultiFactorAuthenticationToken:(JoobMobileMultiFactorToken*)token withPassword:(NSString*)password;

@end