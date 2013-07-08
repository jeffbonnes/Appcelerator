/****************************************************************************
 
 P R O P R I E T A R Y   N O T I C E
 
 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.
 
 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED
 
 ****************************************************************************/

#import "asl.h"
#import <Foundation/Foundation.h>

@interface JoobMobileRemoteLogger : NSObject
{
    aslclient loggingClient;
    dispatch_source_t pollingTimer;
}

/**
 Used to access the JoobMobileLogging class
 @return JoobMobileLogging A reference to the current JoobMobileLogging instance.
 */
+(JoobMobileRemoteLogger *)sharedLogManager;

/**
 Starts JoobMobile Remote Logging 
 */
-(void)start;

/**
 Stops JoobMobile Remote Logging
 */
-(void)stop;

/**
 Forces the JoobMobile Remote Logging to start reading log entries at the new level provided.
 @param int The new log level
 */
-(void)updateLogLevel:(int)level;

@end
