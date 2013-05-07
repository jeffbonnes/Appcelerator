/****************************************************************************

 P R O P R I E T A R Y   N O T I C E

 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.

 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED

 ****************************************************************************/


#import <Foundation/Foundation.h>


@interface JoobMobileOperationProfiling : NSObject
{
    NSInteger executionStart;
    NSInteger executionStop;
    NSString *label;
    NSString *message;
    NSInteger timeSpan;
}

@property (assign) NSInteger executionStart;
@property (assign) NSInteger executionStop;
@property (retain) NSString *label;
@property (retain) NSString *message;
@property (assign) NSInteger timeSpan;


/**
 *  A method to wrap another method and time the block
 *  @param label An NSString to use as a label to identify the timed block
 *  @param block A block to time.
 *  @param message A message include with the JoobMobileOperationProfiling event.
 */
+(void)timedBlock:(NSString*)label block:(void (^)(void))block withMessage:(NSString*)message;


/**
*  A method to wrap another method and time the block
*  @param label An NSString to use as a label to identify the timed block
*  @param object The object the method to be timed resides on
*  @param selector The selector to time
*  @param message A message include with the JoobMobileOperationProfiling event.
*/
+(void)timedBlock:(NSString *)label usingObject:(NSObject*)object  withSelector:(SEL)selector withMessage:(NSString *)message;


/**
* A method to return a JoobMobileOperation profiling instance to use within async calls or similar.
* @param label A NSString to use as an identifier for the timed operation.
* @returns An initialised instance of a JoobMobileOperationProfiler.
*/
+(JoobMobileOperationProfiling *)startTimedBlock:(NSString*)label;

/** An instance method to signal a timed block has completed.
* @param A message to include with the JoobMobileOperationProfiling object that is sent to the server.
*/
-(void)endTimedBlock:(NSString *)message;

-(void)timerFlush;

+(void)flushQueue;

@end