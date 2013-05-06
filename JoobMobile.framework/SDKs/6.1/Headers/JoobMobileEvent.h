/****************************************************************************

 P R O P R I E T A R Y   N O T I C E

 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.

 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED

 ****************************************************************************/


#import <Foundation/Foundation.h>
#import "JoobMobileParserDelegate.h"


@interface JoobMobileEvent : NSObject

@property (nonatomic, retain) NSDate *timeStamp;
@property (nonatomic, retain) NSString *eventType;
@property (nonatomic, retain) NSNumber *level;
@property (nonatomic, retain) NSDictionary *eventData;

/**
 Method to initialise a JoobMobileEvent with values 
 @param type The type of event ( ie Log, Transaction, ExceededAccountThreshold, etc )
 @param timestamp The timestamp of when the event was raised ie now
 @param level The priority or urgency of the event, this is mapped to standard UNIX log levels
 @param data A NSDictionary of key/value pairs contained event information.
 @return A populated JoobMobileEvent object.
 */
- (id) initWithProperties:(NSString*)type withTimeStamp:(NSDate *)timestamp withLevel:(NSNumber*)level withData:(NSDictionary*)data;

@end