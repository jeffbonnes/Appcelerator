/****************************************************************************
 
 P R O P R I E T A R Y   N O T I C E
 
 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.
 
 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED
 
 ****************************************************************************/

#import <Foundation/Foundation.h>
#import "JoobMobile.h"
#import "JoobMobileSettings.h"

@interface JoobMobileFactory : NSObject

/**
 Used to access the JoobMobile API
 @returns JoobMobile Returns the JoobMobile API instance
 */
+ (JoobMobile*)getApi;

/**
 Used to access the JoobMobile API
 @param delegate The class containing JoobMobile delegate methods.
 methodName:joobMobileHttpResult: and accept an NSOject as the first parameter and a JoobMobileHttpResult as the second.
 @returns JoobMobile Returns the JoobMobile API instance
 */
+ (JoobMobile*)getApi:(id)delegate;

/**
 Used to access the JoobMobile settings
 @returns JoobMobile Returns the JoobMobile API instance
 */
+ (JoobMobileSettings*)getSettings;

@end
