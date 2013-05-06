/****************************************************************************
 
 P R O P R I E T A R Y   N O T I C E
 
 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.
 
 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED
 
 ****************************************************************************/

#import <Foundation/Foundation.h>
#import "JoobMobileHttpResult.h"
#import "JoobMobileConnectionDelegate.h"



@interface JoobMobileConnection : NSObject {
	

}

/**
 Initializes a new JoobMobileConnection using the provided delegate.
 @param connectionDelegate The delegate to set after initializaion.
 @return A new JoobMobileConnection.
 */
- (id)initWithDelegate:(id<JoobMobileConnectionDelegate>)connectionDelegate;

- (void)post:(NSURL *)url uuid:(NSString *)uuid postData:(NSData *)postData withTimeout:(int)timeout encrypt:(bool)encryptRequest headers:(NSDictionary *)customHeaders onSuccess:(void (^)(JoobMobileHttpResult *))successBlock onFailure:(void (^)(JoobMobileHttpResult *))failureBlock;

- (void)get:(NSURL *)url uuid:(NSString *)uuid withTimeout:(int)timeout encrypt:(bool)encryptRequest headers:(NSDictionary *)customHeaders onSuccess:(void (^)(JoobMobileHttpResult *))successBlock onFailure:(void (^)(JoobMobileHttpResult *))failureBlock;

- (void)post:(NSURL *)url uuid:(NSString *)uuid postData:(NSData *)postData withTimeout:(int)timeout encrypt:(bool)encryptRequest headers:(NSDictionary *)customHeaders;

- (void)get:(NSURL *)url uuid:(NSString *)uuid withTimeout:(int)timeout encrypt:(bool)encryptRequest headers:(NSDictionary *)customHeaders;
@end