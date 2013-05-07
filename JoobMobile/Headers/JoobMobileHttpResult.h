/****************************************************************************
 
 P R O P R I E T A R Y   N O T I C E
 
 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.
 
 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED
 
 ****************************************************************************/

#import <Foundation/Foundation.h>

/**
 A Class to represent the HTTP response information that is passed back to the calling Class 
 in the info dictionary
 */
@interface JoobMobileHttpResult : NSObject {
    
}

/**
 The request associated with this http result completed successfully (HTTP Status code 200).
 */
extern NSString *const HTTPRESULT_SUCCESSFUL;


/**
  The request associated with this http result failed (All status codes except 200).
 */
extern NSString *const HTTPRESULT_FAILED;


/*
    The returned status code from the http request
 */
@property (assign) NSInteger statusCode;


/*
    The HTTP headers as sent via JoobMobile when it dispatched the request
 */
@property (nonatomic, copy) NSDictionary *requestHeaders;


/*
    The HTTP body as sent in the JoobMobile request when it dispatched the event
 */
@property (nonatomic, copy) NSData *requestBody;


/*
    The HTTP headers as returned by the targeted endpoint
 */
@property (nonatomic, copy) NSDictionary *responseHeaders;


/*
    The HTTP document body as returned by the targeted endpoint
 */
@property (nonatomic, copy) NSData *responseBody;


/*
    The UUID of the current request/message
 */
@property (nonatomic, copy) NSString *uuid;


/*
    The targeted endpoint passed in to JoobMobile when the request was made
 */
@property (nonatomic, copy) NSURL *requestUri;


/*
    The type of http request.
 */
@property (nonatomic, copy) NSString *verb;


/*
    A simple property to indicate the status of the request when completed
 */
@property (nonatomic, copy) NSString *status;

@end
