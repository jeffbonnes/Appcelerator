/****************************************************************************
 
 P R O P R I E T A R Y   N O T I C E
 
 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.
 
 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED
 
 ****************************************************************************/

#import <Foundation/Foundation.h>


@interface JoobMobileMessage : NSObject {

}

/**
 Possible priorities for a Joob Mobile Message.
 */
extern NSString *const MESSAGE_PRIORITY_HIGH;
extern NSString *const MESSAGE_PRIORITY_NORMAL;
extern NSString *const MESSAGE_PRIORITY_LOW;

extern int const TIMETOLIVE_FOREVER;
extern int const TIMETOLIVE_TRYONCE;

/**
 The http request body.
 */
@property (nonatomic, retain) NSString *body;


/**
 The URL this message will be sent to.
 */
@property (nonatomic, retain) NSString *url;


/**
 A unique identifier.
 */
@property (nonatomic, retain) NSString *uuid;


/**
 The HTTP verb.
 */
@property (nonatomic, retain) NSString *verb;


/**
 The priority for this message.
 */
@property (nonatomic, retain) NSString *priority;


/**
 The time this message was submitted to the Joob Mobile queue.
 */
@property (nonatomic, retain) NSDate *submittedToQueue;


/**
 Time to live for this message in milliseconds.
 */
@property int timeToLive;

@end
