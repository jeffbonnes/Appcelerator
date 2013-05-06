/****************************************************************************
 
 P R O P R I E T A R Y   N O T I C E
 
 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.
 
 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED
 
 ****************************************************************************/

#import <Foundation/Foundation.h>

@interface JoobMobileHardware : NSObject {

}

/**
 Returns a unique identifier for the current device that is consistent across Joob Mobile applications.
 @return A unique identifier for the current device.
 */
- (NSString*)deviceId;

/**
 Returns the phone number of the device if available.
 @return The devices phone number if available.
 */
- (NSString*)phoneNumber;

/**
 Returns the iOS version.
 @return The current iOS version the device is running.
 */
- (NSMutableString*)operatingSystemVersion;

/**
 Returns the device type.
 @return Returns the type of device the application is running on.
 */
- (NSString*)deviceType;

/**
* Returns a dictionary containing device information.
* @return NSDictionary A dictionary containing device information.
*/
- (NSDictionary *)getDeviceInformation;

/**
* Returns full model of the iOS device.
* @return NSDictionary A String representation of the device type and model.
*/
- (NSDictionary *)getModelInformation;

@end
