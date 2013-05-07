/****************************************************************************
 
 P R O P R I E T A R Y   N O T I C E
 
 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.
 
 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED
 
 ****************************************************************************/

#import <Foundation/Foundation.h>
#import "JoobMobileMessageStoreDelegate.h"
#import "JoobMobileMessage.h"
#import "JoobMobilePersistentMessage.h"

@interface JoobMobileMessageStore : NSObject {
    
}


/*
    The delegate that will be called during messages restoration.
 */
@property (nonatomic, retain) id<JoobMobileMessageStoreDelegate> delegate;


/*
    Initializes a new JoobMobileMessageStore using the specified delegate.
 */
- (id) initWithDelegate:(id<JoobMobileMessageStoreDelegate>)messageStoreDelegate;


/*
    Restores all messages from disk. This is an asynchronous operation.
 */
- (void) restoreMessages;


/*
    Saves a single message to disk. This is a synchronous operation.
 */
- (void) saveMessage:(JoobMobileMessage*)joobMobileMessage;


/*
    Deletes a single message from disk. This is a synchronous operation.
    If no message is found with the specified uuid then this is a no op.
 */
- (void) deleteMessage:(NSString*)messageUuid;


/*
 Converts a JoobMobilePersistentMessage to a JoobMobileMessage that has no ties to CoreData.
 */
-(JoobMobileMessage*) persistentJoobMobileMessageToPoco:(JoobMobilePersistentMessage*)joobMobilePersistentMessage;

@end
