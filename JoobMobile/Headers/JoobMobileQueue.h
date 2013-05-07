/****************************************************************************
 
 P R O P R I E T A R Y   N O T I C E
 
 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.
 
 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED
 
 ****************************************************************************/

//
//  This class is a singleton purely to contain the queue of messages

#import <Foundation/Foundation.h>
#import "JoobMobileMessage.h"
#import "JoobMobileDatabaseUtilities.h"
#import "JoobMobileQueueEntry.h"
#import "JoobMobileMessageStoreDelegate.h"
#import "JoobMobilePersistentMessage.h"
#import "JoobMobileMessageStore.h"

@interface JoobMobileQueue : NSObject <JoobMobileMessageStoreDelegate> {

}

/**
    The singleton instance of the JoobMobileQueue - Use this for all access to this class.
 */
+(JoobMobileQueue*)sharedManager;

/**
    Adds a JoobMobileMessage to the pending queue for processing,
    @param joobMobileMessage The JoobMobileMessage to add to the queue.
    @param withState The user state for this queue entry.
    @param withTarget An object that will be notified on success or failure of the message.
    @param withSuccessCallback The selector that will be invoked on the target object on success.
    @param withFailureCallback The selector that will be invoked on the target object on failure.
    @param willPersist A bool to indicate if this message should be persisted to disk.
    @param shouldNoOpDuplicates If a message with the same uuid already exists in the queue, and shouldNoOpDuplicates is
            true, then this will be a no op.
 */
-(void)addMessage:(JoobMobileMessage*)joobMobileMessage withState:(NSObject*)state withTarget:(id)target withSuccessCallback:(SEL)successCallback withFailureCallback:(SEL)failureCallback willPersist:(BOOL)persist shouldNoOpDuplicates:(BOOL)noOpDuplicates;

/**
 A method to remove an item off the queue.
 @param identifier The UUID off the persistent message to remove. 
 */
-(void)purgeMessage:(NSString*)uuid;


/**
 A method to readd an item to the queue.
 @param identifier The UUID off the persistent message to readd. 
*/
-(void)retankMessage:(NSString*)uuid;


/**
 A method to retrieve the next item off the queue.
 @return A message object
 */
-(JoobMobileMessage*)nextMessage;


/**
 A method to access the transient instance in the queue itself.
 @param identifier The UUID off the persistent message to readd. 
 @return The requested JoobMobileQueueEntry 
 */
-(JoobMobileQueueEntry*)getQueueEntry:(NSString*)uuid;


/**
 Prunes messages that have both MESSAGE_PRIORITY_HIGH and TIMETOLIVE_TRYONCE.
 */
- (NSArray*) pruneHighPriorityTryOnceMessages;


/**
 A method to return the current queue depth.
 @return Integer value representing the number of items in the queue 
 */
-(int)currentQueueDepth;


/**
 A method to restore the queue from persistent messages in the Datastore.
 */
-(void)restoreQueue;


- (void)addMessage:(JoobMobileMessage *)message successBlock:(void (^)(JoobMobileHttpResult *))successBlock failureBlock:(void (^)(JoobMobileHttpResult *))failureBlock willPersist:(BOOL)persist shouldNoOpDuplicates:(BOOL)allowDuplicates;
@end
