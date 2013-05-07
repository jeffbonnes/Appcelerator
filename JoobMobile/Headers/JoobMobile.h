/****************************************************************************
 
 P R O P R I E T A R Y   N O T I C E
 
 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.
 
 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED
 
 ****************************************************************************/

#import "JoobMobileHttpResult.h"
#import "JoobMobileAuthentication.h"
#import "JoobMobileAuthenticationDelegate.h"
#import "JoobMobileMultiFactorToken.h"

/**
 Implement this protocol to be notified when JoobMobile requires action.
 */
@protocol JoobMobileDelegate <NSObject>

@optional

/**
 A delegate method called once the client has successfully logged out.
 */
- (void) logoutCompleted;


/**
* A delegate method called when the server requests multi factor authentication.
*/
- (void) multiFactorAuthenticationRequired:(JoobMobileMultiFactorToken *)token;


/**
* a delegate method called when the server requests device registration post login.
*/
- (void) deviceRegistrationRequired;
 

/**
 A delegate method called when the device has been disabled by an administrator.
 Designed to allow application developers to clean up sensitive data prior to the 
 framework terminating the application.
 */
- (void) applicationDisabled:(NSString*) reason;

@end


/**
 The central Joob Mobile class, use this to send and retrieve data from the Joob Mobile Gateway.
 */
@interface JoobMobile : NSObject <JoobMobileAuthenticationDelegate>


/**
 The delegate class that will be notified when login and logout have completed.
 */
@property (nonatomic, retain) id <JoobMobileDelegate> delegate;


/**
 Initializes a new JoobMobile using the specified delegate.
 */
- (id) initWithDelegate:(id<JoobMobileDelegate>)joobMobileDelegate;


/**
 Sends a DataItem to the JoobMobile Gateway. The DataItem will contain metadata about the time and location of the device
 when it was submitted, it will also contain the payload embedded within it that will be made available to the DataItem plugin
 on the server.

 @param payload A dictionary that will be serialized to JSON and embedded within the DataItem.
 @param dataType The type of data contained within the payload. This value will be used by the server to identify the payload.
 @param userState An object that will be passed to the success and failure callbacks, it may be used to preserve state throughout
 the asynchronous operations of JoobMobile.

 @param callbackTarget An object that will be notified on success or failure of this request.
 @param successCallback The selector that will be invoked on the target object on success. The signature of this selector must match
 methodName:joobMobileHttpResult: and accept an NSOject as the first parameter and a JoobMobileHttpResult as the second.
 @param failureCallback The selector that will be invoked on the target object on failure. The signature of this selector must match
 methodName:joobMobileHttpResult: and accept an NSOject as the first parameter and a JoobMobileHttpResult as the second.

 @return A unique identifier that is used to keep track of this request, the identifier will be available on the JoobMobileHttpResult object within the success and failure callbacks.
 */
- (NSString *)sendDataItem:(id)payload dataType:(NSString *)dataType userState:(NSObject *)state callbackTarget:(id)target successCallback:(SEL)successSelector failureCallback:(SEL)failureSelector;



/**
 Sends a DataItem to the JoobMobile Gateway. The DataItem will contain metadata about the time and location of the device
 when it was submitted, it will also contain the payload embedded within it that will be made available to the DataItem plugin
 on the server.

 @param payload A dictionary that will be serialized to JSON and embedded within the DataItem.
 @param dataType The type of data contained within the payload. This value will be used by the server to identify the payload.
 @param successBlock Block to execute on a successful response.
 @param failureBlock Block to execute on a unsuccessful response.
 */
- (NSString *)sendDataItem:(id)payload dataType:(NSString *)dataType onSuccess:(void (^)(JoobMobileHttpResult *))successBlock onFailure:(void (^)(JoobMobileHttpResult *))failureBlock;



/**
 Performs a standard HTTP Get to the supplied url.
 
 @param url The url to retrieve.
 @param userState An object that will be passed to the success and failure callbacks, it may be used to preserve state throughout
 the asynchronous operations of JoobMobile.
 
 @param callbackTarget An object that will be notified on success or failure of this request.
 @param successCallback The selector that will be invoked on the target object on success. The signature of this selector must match 
 methodName:joobMobileHttpResult: and accept an NSOject as the first parameter and a JoobMobileHttpResult as the second.
 @param failureCallback The selector that will be invoked on the target object on failure. The signature of this selector must match 
 methodName:joobMobileHttpResult: and accept an NSOject as the first parameter and a JoobMobileHttpResult as the second.
 
 @param priority A JoobMobileMessage priority constant, higher priority requests will be sent first.
 In general requests should be low or normal priority, high priority requests should be preserved for interactive operations that
 a user may be waiting on i.e. Querying for data to display to the user. The recommended priority for a get is high as in general it will
 be an interactive operation.
 
 @param timeToLive Time in milliseconds that this request will be allowed to be active for before being marked as failed and permanently
 abandoned. See JoobMobileMessage Time To Live constants for special values, otherwise any millisecond value may be provided.
 The time to live value is only evaluated in two circumstances - 1. A request has failed due to a non-fatal error, if it has exceeded its time to live it will not be requeued. 2. If the device has no network connectivity then requests that are both high priority and have a time to live equal to the TIMETOLIVE_TRYONCE constant will be immediatley failed and removed from the queue. It is important to understand these conditions as it may lead to confusion when a request that has a time to live of say 30 seconds is initiated 2 minutes after being submitted, this is expected behaviour. The recommended time to live for a get is TIMETOLIVE_TRYONCE as in general it will be an interactive operation.
 
 @return A unique identifier that is used to keep track of this request, the identifier will be available on the JoobMobileHttpResult object within the success and failure callbacks.
 */
-(NSString*)get:(NSURL*)url userState:(NSObject*)state callbackTarget:(id)target successCallback:(SEL)successSelector failureCallback:(SEL)failureSelector  priority:(NSString*)priority timeToLive:(int)timeToLive;


/**
 Performs a standard HTTP Get to the supplied url.

 @param url The url to retrieve.
 @param successBlock Block to execute on a successful response.
 @param failureBlock Block to execute on a unsuccessful response.

 @param priority A JoobMobileMessage priority constant, higher priority requests will be sent first.
 In general requests should be low or normal priority, high priority requests should be preserved for interactive operations that
 a user may be waiting on i.e. Querying for data to display to the user. The recommended priority for a get is high as in general it will
 be an interactive operation.

 @param timeToLive Time in milliseconds that this request will be allowed to be active for before being marked as failed and permanently
 abandoned. See JoobMobileMessage Time To Live constants for special values, otherwise any millisecond value may be provided.
 The time to live value is only evaluated in two circumstances - 1. A request has failed due to a non-fatal error, if it has exceeded its time to live it will not be requeued. 2. If the device has no network connectivity then requests that are both high priority and have a time to live equal to the TIMETOLIVE_TRYONCE constant will be immediatley failed and removed from the queue. It is important to understand these conditions as it may lead to confusion when a request that has a time to live of say 30 seconds is initiated 2 minutes after being submitted, this is expected behaviour. The recommended time to live for a get is TIMETOLIVE_TRYONCE as in general it will be an interactive operation.

 @return A unique identifier that is used to keep track of this request, the identifier will be available on the JoobMobileHttpResult object within the success and failure callbacks.
 */
-(NSString*)get:(NSURL*)url onSuccess:(void (^)(JoobMobileHttpResult *))successBlock onFailure:(void (^)(JoobMobileHttpResult *))failureBlock  priority:(NSString*)priority timeToLive:(int)timeToLive;

/**
 Performs a standard HTTP Get to the supplied url.

 @param url The url to post to.
 @param postData The data that will be posted to the supplied url.
 @param userState An object that will be passed to the success and failure callbacks, it may be used to preserve state throughout
 the asynchronous operations of JoobMobile.

 @param callbackTarget An object that will be notified on success or failure of this request.
 @param successCallback The selector that will be invoked on the target object on success. The signature of this selector must match
 methodName:joobMobileHttpResult: and accept an NSOject as the first parameter and a JoobMobileHttpResult as the second.
 @param failureCallback The selector that will be invoked on the target object on failure. The signature of this selector must match
 methodName:joobMobileHttpResult: and accept an NSOject as the first parameter and a JoobMobileHttpResult as the second.

 @param priority A JoobMobileMessage priority constant, higher priority requests will be sent first.
 In general requests should be low or normal priority, high priority requests should be preserved for interactive operations that
 a user may be waiting on i.e. Querying for data to display to the user. The recommended priority for a post is normal as in general it will not
 be an interactive operation. If however, the user is waiting on the response, then the priority should be high.

 @param timeToLive Time in milliseconds that this request will be allowed to be active for before being marked as failed and permanently
 abandoned. See JoobMobileMessage Time To Live constants for special values, otherwise any millisecond value may be provided.
 The time to live value is only evaluated in two circumstances - 1. A request has failed due to a non-fatal error, if it has exceeded its time to live it will not be requeued. 2. If the device has no network connectivity then requests that are both high priority and have a time to live equal to the TIMETOLIVE_TRYONCE constant will be immediatley failed and removed from the queue. It is important to understand these conditions as it may lead to confusion when a request that has a time to live of say 30 seconds is initiated 2 minutes after being submitted, this is expected behaviour. The recommended time to live for a post is an appropriate millisecond value specific to the situation. If the post is an interactive operation i.e. A query, then the time to live should be TIMETOLIVE_TRYONCE.

 @return A unique identifier that is used to keep track of this request, the identifier will be available on the JoobMobileHttpResult object within the success and failure callbacks.
 */
-(NSString*)post:(NSURL*)url postData:(NSString*)postData userState:(NSObject*)state callbackTarget:(id)target successCallback:(SEL)successSelector failureCallback:(SEL)failureSelector priority:(NSString*)priority timeToLive:(int)timeToLive;


/*
 @param url The url to post to.
 @param postData The data that will be posted to the supplied url.
 @param successBlock Block to execute on a successful response.
 @param failureBlock Block to execute on a unsuccessful response.

 @param priority A JoobMobileMessage priority constant, higher priority requests will be sent first.
 In general requests should be low or normal priority, high priority requests should be preserved for interactive operations that
 a user may be waiting on i.e. Querying for data to display to the user. The recommended priority for a post is normal as in general it will not
 be an interactive operation. If however, the user is waiting on the response, then the priority should be high.

 @param timeToLive Time in milliseconds that this request will be allowed to be active for before being marked as failed and permanently
 abandoned. See JoobMobileMessage Time To Live constants for special values, otherwise any millisecond value may be provided.
 The time to live value is only evaluated in two circumstances - 1. A request has failed due to a non-fatal error, if it has exceeded its time to live it will not be requeued. 2. If the device has no network connectivity then requests that are both high priority and have a time to live equal to the TIMETOLIVE_TRYONCE constant will be immediatley failed and removed from the queue. It is important to understand these conditions as it may lead to confusion when a request that has a time to live of say 30 seconds is initiated 2 minutes after being submitted, this is expected behaviour. The recommended time to live for a post is an appropriate millisecond value specific to the situation. If the post is an interactive operation i.e. A query, then the time to live should be TIMETOLIVE_TRYONCE.

 */
-(NSString*)post:(NSURL*)url postData:(NSString*)postData onSuccess:(void (^)(JoobMobileHttpResult *))successBlock onFailure:(void (^)(JoobMobileHttpResult *))failureBlock  priority:(NSString*)priority timeToLive:(int)timeToLive;


/**
 Performs a standard HTTP Get to the supplied url.
 
 @param url The url to post to.
 @param postData The data that will be posted to the supplied url.
 @param userState An object that will be passed to the success and failure callbacks, it may be used to preserve state throughout
 the asynchronous operations of JoobMobile.
 
 @param callbackTarget An object that will be notified on success or failure of this request.
 @param successCallback The selector that will be invoked on the target object on success. The signature of this selector must match 
 methodName:joobMobileHttpResult: and accept an NSOject as the first parameter and a JoobMobileHttpResult as the second.
 @param failureCallback The selector that will be invoked on the target object on failure. The signature of this selector must match 
 methodName:joobMobileHttpResult: and accept an NSOject as the first parameter and a JoobMobileHttpResult as the second.
 
 @param priority A JoobMobileMessage priority constant, higher priority requests will be sent first.
 In general requests should be low or normal priority, high priority requests should be preserved for interactive operations that
 a user may be waiting on i.e. Querying for data to display to the user. The recommended priority for a post is normal as in general it will not
 be an interactive operation. If however, the user is waiting on the response, then the priority should be high.
 
 @param timeToLive Time in milliseconds that this request will be allowed to be active for before being marked as failed and permenantly 
 abandoned. See JoobMobileMessage Time To Live constants for special values, otherwise any millisecond value may be provided.
 The time to live value is only evaluated in two circumstances - 1. A request has failed due to a non-fatal error, if it has exceeded its time to live it will not be requeued. 2. If the device has no network connectivity then requests that are both high priority and have a time to live equal to the TIMETOLIVE_TRYONCE constant will be immediatley failed and removed from the queue. It is important to understand these conditions as it may lead to confusion when a request that has a time to live of say 30 seconds is initiated 2 minutes after being submitted, this is expected behaviour. The recommended time to live for a post is an appropriate millisecond value specific to the situation. If the post is an interactive operation i.e. A query, then the time to live should be TIMETOLIVE_TRYONCE.

 @param persistToDisk BOOL Set this option to false to disable writing requests to disk.
 This will ensure requests are only kept in-memory and will instantly be destroyed if the application is closed or the device is powered off.

 @return A unique identifier that is used to keep track of this request, the identifier will be available on the JoobMobileHttpResult object within the success and failure callbacks.
 */
-(NSString*)post:(NSURL*)url postData:(NSString*)postData userState:(NSObject*)state callbackTarget:(id)target successCallback:(SEL)successSelector failureCallback:(SEL)failureSelector priority:(NSString*)priority timeToLive:(int)timeToLive persistToDisk:(BOOL)persist;


/**
 Begins the asynchronous login process. This should be invoked early in your applications life-cycle and the success or failure
 of the login should determine how your application presents itself to the user.
 @param rootDocumentUrl The url to the root document.
 @param onSuccess The block to invoke on success.
 @param onFailure The block to invoke on failure.
 @param timeout The maximum amount of time you want to attempt a login.
*/
- (void) login:(NSURL*)rootDocumentUrl onSuccess:(void (^)(NSString *))successBlock onFailure:(void (^)(NSString *))failureBlock withTimeout:(int)timeout;


/**
 Begins the asynchronous logout process. First attempts perform a server side logout against the Joob Mobile server,
 if server side logout fails then a client side logout will be performed.
 */
- (void) logout;

/**
* The token supplied by the appropriate plugin implemented server side. ( email / sms / vasco / rsa / etc)
*/
- (void) registerDevice:(NSString *)token;


/**
 Provide a response to a Multi Factor Authentication challenge.
 */
- (void) respondToMultiFactorChallenge:(JoobMobileMultiFactorToken*)token withResponse:(NSDictionary*)response;
@end