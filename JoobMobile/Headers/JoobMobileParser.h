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

@class JSONDecoder;

/**
 A helper class for parsing JSON documents returned via the JoobMobile framework.
 */
@interface JoobMobileParser : NSObject {

}

/**
A method to parse JSON documents returned via the JoobMobile framework.
@param json An NSString object as returned by the JoobMobile framework. 
@returns An appropriate native type based on the provided JSON i.e. An NSDictionary or NSArray etc.
*/
+ (id)parseJSON:(NSData *)json;

/**
 A method to convert Microsoft JSON Dates to native NSDate objects.
 @param dateString An NSString as returned in JoobMobile JSON to represent a date.
 @returns An NSDate object.
 */
+ (NSDate *)getDateFromMSDate:(NSString*)dateString;

/**
* A method to convert an ISO8601 date string to a NSDate
* @param dateString An NSString as returned in JoobMobile 3.0+ JSON to represent a date.
* @returns An NSDate object.
*/
+ (NSDate *)getDateFromISO8601Date:(NSString *)dateString;

/**
 Serializes an NSDictionary to a JSON string.
 @param dictionary The NSDictionary to serialize.
 */
+(NSString *)dictionaryToJSON:(NSDictionary *)dictionary;

/**
* Serializes an NSArray to a JSON string.
* @param array The NSArray to serialize.
*/
+(NSString *)arrayToJSON:(NSArray *)array;

/**
 Serializes any object that implements the JoobMobileParserDelegate to
 a JSON string.
 @param object The object to serialize.
 */
+(NSString *)objectToJSON:(id<JoobMobileParserDelegate>)object;

@end
