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

// Based on Peter Hosey's series on asl_log and example by Karl Kuehn

#ifndef ASL_KEY_FACILITY
    #define ASL_KEY_FACILITY "JoobMobile Facility"
#endif

#define NSLog_level(log_level, format, ...) asl_log(asl_open(NULL, NULL, ASL_OPT_STDERR), NULL, log_level, "%s", [[NSString stringWithFormat:format, ##__VA_ARGS__] UTF8String]);

#define NSLogEmergency(format, ...) NSLog_level(ASL_LEVEL_EMERG, format, ##__VA_ARGS__)
#define NSLogAlert(format, ...) NSLog_level(ASL_LEVEL_ALERT, format, ##__VA_ARGS__)
#define NSLogCritical(format, ...) NSLog_level(ASL_LEVEL_CRIT, format, ##__VA_ARGS__)
#define NSLogError(format, ...) NSLog_level(ASL_LEVEL_ERR, format, ##__VA_ARGS__)
#define NSLogWarning(format, ...) NSLog_level(ASL_LEVEL_WARNING, format, ##__VA_ARGS__)
#define NSLogNotice(format, ...) NSLog_level(ASL_LEVEL_NOTICE, format, ##__VA_ARGS__)
#define NSLogInfo(format, ...) NSLog_level(ASL_LEVEL_INFO, format, ##__VA_ARGS__)
#define NSLogDebug(format, ...) NSLog_level(ASL_LEVEL_DEBUG, format, ##__VA_ARGS__)

#define Emergency = 0;
#define Alert = 1;
#define Critical = 2;
#define Error = 3;
#define Warning = 4;
#define Notice = 5;
#define Info = 6;
#define Debug = 7;

// Prints to stdout only
#define NSLogPrint(format, ...) printf("%s\n", [[NSString stringWithFormat:format, ##__VA_ARGS__] UTF8String])

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
