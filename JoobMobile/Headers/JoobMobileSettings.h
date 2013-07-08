/****************************************************************************
 
 P R O P R I E T A R Y   N O T I C E
 
 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.
 
 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED
 
 ****************************************************************************/

#import <Foundation/Foundation.h>


@interface JoobMobileSettings : NSObject {
    
}

/**
 Gets the current mobile data preference.
 @return A bool indicating whether or not to allow data over 3/4G network.
 **/
+ (bool) mobileData;


/**
 Enables or disables the use of 3/4G when sending requests through Joob Mobile.
 @param enable Set to true to allow mobile data. Default is disabled.
 */
+ (void) mobileData:(bool)enable;


/**
 Sets the log level for remote logging through Joob Mobiles.
 @param logLevel Follows the standard syslog levels, set to define the filter for logs being sent
 Level 0 – “Emergency”
 Level 1 – “Alert”
 Level 2 – “Critical”
 Level 3 – “Error”
 Level 4 – “Warning”
 Level 5 – “Notice”
 Level 6 – “Info”
 Level 7 – “Debug”
 */
+ (void) setRemoteLoggingLevel:(int)logLevel;


/**
 Returns the current log level preference for remote logging.
 */
+ (int) remoteLoggingLevel;

/**
 Gets the current httpRequestInitialRetryPeriod.
 @return The current httpRequestInitialRetryPeriod.
 */
+ (int) httpRequestInitialRetryPeriod;

/**
 Sets the initial retry period that will be waited before retrying Http requests that have failed
 for the first time due to non-fatal error conditions.
 @param initialRetryPeriod The amount of time in milliseconds to wait. Default is 60000, or 1 minute.
 */
+ (void) setHttpRequestInitialRetryPeriod:(int)initialRetryPeriod;


/**
 Gets the current httpRequestMaxRetryPeriod.
 @return The current httpRequestMaxRetryPeriod.
 */
+ (int) httpRequestMaxRetryPeriod;


/**
 Sets the maximum amount of time to wait between retrying Http requests that have previously failed
 with non-fatal error conditions. 
 @param maxRetryPeriod The maximum amount of time in milliseconds to wait. Default is 43200000, or 12 hours.
 */
+ (void) setHttpRequestMaxRetryPeriod:(int)maxRetryPeriod;


/**
 Gets the current maxConcurrentHttpRequests value.
 @return The current maxConcurrentHttpRequests value.
 */
+ (int) maxConcurrentHttpRequests;


/**
 Sets the maxConcurrentHttpRequests value. This is used to determine the maximum amount of asynchrounous http requests
 that will be running at any given point in time.
 @param max The value to set for maxConcurrentHttpRequests. Default is 2.
 */
+ (void) setMaxConcurrentHttpRequests:(int)max;


/**
 Gets the current httpRequestTimeout.
 @return The current httpRequestTimeout value.
 */
+ (int) httpRequestTimeoutPeriod;


/**
 Sets the httpRequestTimeoutPeriod value. This is used to determine the maximum amount of time an http request will be
 in progress before it is timed out and aborted.
 */
+ (void) setHttpRequestTimeoutPeriod:(int)timeoutPeriod;


/**
 A method to return the current root document
 @returns NSDictionary The current root document dictionary
*/
+ (NSDictionary*) rootDocument;


/**
* A method to return the current settings document
* @returns NSDictionary The current settings dictionary
*/
+ (NSDictionary*) settingsDocument;


/**
* Clears the currently stored server defined settings.
*/
+ (void) clearSettingsDocument;

/**
* Store the JoobMobile client settings dictionary
* @param settingsDictionary The NSDictionary containing settings key/value pairs
*/
+ (void) setDeviceInformationDocument:(NSDictionary *)settingsDocument;


/**
* Get the settings value for the key passed in
* @returns NSString The value of the requested client setting
*/
+ (NSString*) getClientSetting:(NSString*)name;

/**
 Gets the uri value for the specified name off the root document.
 @param name The name of the root document entry to retrieve.
 @return The value of the root document entry as a url.
 */
+ (NSURL*) getRootDocumentUri:(NSString*)name;


/**
 Stores the root document dictionary
 @param documentDictionary The NSDictionary containing the root document key/value pairs
 */
+ (void) setRootDocument:(NSDictionary *)documentDictionary;


/**
 Gets the NSDate representing the time the root document was persisted via setRootDocument.
 This is used to invalidate the persisted root document when appropriate as it needs to be kept
 relatively fresh to be effective.
 */
+ (NSDate*) rootDocumentPersistedDate;


/**
 Gets the current user token.
 @return The current user token or Nil if no user token has previously been set.
 */
+ (NSDictionary*) userToken;


/**
 Sets the user token to use when authenticating to the Joob Mobile Gateway. The user token must be set prior to 
 an authentication challange or an exception will be thrown.
 @param userToken The user token to use when authenticating to the JoobMobile Gateway.
 */
+ (void) setUserToken:(NSDictionary*)userToken;


/**
* Indicates whether the application should perform HTTP operations over a link using a self signed or non CA Root
* signed SSL certificate
*/
+ (bool) allowInvalidSsl;


/**
* Sets the value to indicate whether or not the application should perform HTTP operations over a link using a
* self signed or non CA Root signed SSL certificate
*/
+ (void) allowInvalidSsl:(bool)enable;


/**
* Set to false if not using the default JoobMobile encrypted login.
* @returns
*/
+ (void) setJoobMobileEncryption:(bool)enable;


/**
* Returns the current status.
*/
+ (bool) joobMobileEncryption;


/**
 * Returns the current JOOB Mobile release version.
 */
+ (NSString*)joobMobileVersion;

/**
* Returns the currently set application version, if not set defaults to JoobMobile version.
* @returns NSString A string representing the current application version.
*/
+ (NSString *) applicationVersion;


/**
* Set the application version to something relevant to an application using the JoobMobile framework.
*/
+ (void) setApplicationVersion:(NSString *)version;

@end
