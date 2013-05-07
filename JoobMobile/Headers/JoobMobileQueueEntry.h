/****************************************************************************
 
 P R O P R I E T A R Y   N O T I C E
 
 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.
 
 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED
 
 ****************************************************************************/

#import <Foundation/Foundation.h>
#import "JoobMobileMessage.h"

@class JoobMobileHttpResult;

typedef void (^HttpResultBlock)(JoobMobileHttpResult *result);

@interface JoobMobileQueueEntry : NSObject {

}

@property (atomic) int status;
@property (nonatomic, retain) NSString *uuid;
@property (nonatomic, retain) NSDate *timeSent;
@property (nonatomic, retain) NSNumber *lastFailureWaitTime;
@property (nonatomic, retain) NSNumber *failureCount;
@property (nonatomic, retain) JoobMobileMessage *joobMobileMessage;

/**
    A user defined object that is associated with this request, it will be passed back
    to the user on success or failure of the message associated with this queue
    entry.
 */
@property (nonatomic, retain) NSObject *userState;


/**
    The object that will be notified on success or failure of the message associated with this
    queue entry.
 */
@property (nonatomic, retain) id callbackTarget;


/**
    The selector that will be called on the target object on success of the message associated with
    this queue entry.
 */
@property SEL successCallbackSelector;


/**
    The selector that will be called on the target object on failure of the message associated with
    this queue entry.
 */
@property SEL failureCallbackSelector;


/**
*  The block to be executed on a successful HTTP request.
*/
@property HttpResultBlock successBlock;


/**
*  The block to be executed on an unsuccessful HTTP request.
*/
@property HttpResultBlock failureBlock;


/**
    Compares the priority of this queue entry with another queue entry.
    This is used by the priority queue to order this queue entry appropriately within the queue.
 */
- (NSComparisonResult)compare:(JoobMobileQueueEntry*)otherEntry;

@end