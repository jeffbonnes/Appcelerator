/****************************************************************************
 
 P R O P R I E T A R Y   N O T I C E
 
 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.
 
 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED
 
 ****************************************************************************/

#import <Foundation/Foundation.h>


@interface JoobMobileDataItemUtilities : NSObject {
    
}


/**
 A method to create a new JoobMobileMessage and include dataitem wrapper.
 @param payload A NSDictionary representing the object to send. 
 @param dataType A NSString defining the type of object the payload represents
 @return A NSDictionary representation of the payload contained within metadata.
 */
+(NSMutableDictionary *)generateDataItemDictionary:(id)payload dataType:(NSString *)dataType withUuid:(NSString *)uuid;


/**
 A method to generate a UUID for each mesage sent via the api 
 @return A UUID.
 */
+(NSString*)createUUID;


/**
 A method that contains code to generate a suitable device id and construct representation of the SetDeviceEndpoint document
 @param deviceToken The device token as returned by Apples Push Notification Service
 @return A NSMutableDictionary ready for serialisation 
 */
+(NSMutableDictionary*)createSetDeviceEndpointDocument:(NSData*)deviceToken;

/**
 A method that contains code to generate a suitable device id and construct representation of the SetDeviceEndpoint document
 @return A string representation of the current time GMT suitable to send to the JOOB mobile server.
 */
+(NSString*)getCurrentTimestampGmt;

@end
