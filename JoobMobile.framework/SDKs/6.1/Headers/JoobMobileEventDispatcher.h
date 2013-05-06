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
#import "JoobMobileEvent.h"

@interface JoobMobileEventDispatcher : NSObject <JoobMobileDelegate>
{
    JoobMobile *mobile;
}

@property (retain)JoobMobile *mobile;

+(JoobMobileEventDispatcher *)sharedEventManager;

/**
* A method to end a single event
* param event A JoobMobile event object representing an application event.
*/
-(void)sendEvent:(JoobMobileEvent*)event;

/**
* A method to send multiple events in a batch
* param event A JoobMobile event object representing an application event.
*/
-(void)sendEvents:(NSArray *)events;

@end
