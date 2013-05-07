/****************************************************************************
 
 P R O P R I E T A R Y   N O T I C E
 
 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.
 
 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED
 
 ****************************************************************************/

#import <Foundation/Foundation.h>
#import "JoobMobileMultiFactorToken.h"


@interface JoobMobileAuthenticationUtils : NSObject {
    
}

/**
 Creates a BasicAuthenticationUserToken using the supplied credentials and sets it as the value for 
 the JoobMobileUserToken key in NSUserDefaults. 
 @param username An NSString object containing the user name to set against the Authentication Token 
 @param password An NSString object containing the password to set against the Authentication Token
 */
+ (void) setBasicAuthenticationToken:(NSString*)username password:(NSString*)password;

+ (void) submitDefaultMultiFactorResponse:(JoobMobileMultiFactorToken *)token password:(NSString *)password;

+ (void) submitMultiFactorResponse:(JoobMobileMultiFactorToken *)token multiFactorResponse:(NSDictionary *)multiFactorResponse;


@end
