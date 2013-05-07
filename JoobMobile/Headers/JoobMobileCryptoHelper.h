/****************************************************************************

 P R O P R I E T A R Y   N O T I C E

 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.

 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED

 ****************************************************************************/


#import <Foundation/Foundation.h>
#import <CommonCrypto/CommonCryptor.h>


extern NSString *const Salt;

@interface JoobMobileCryptoHelper : NSObject

/**
 Method to AES Encrypt a string.
 @param string The string to encrypt
 @param password A unique key 
 @param salt A value to salt the encryption routine
 @param iv A value for the initialisation vector
 @param error Pointer to NSError for call
 @returns NSString A base64 encoded string of the encrypted value.
 */
+ (NSString *)encryptString:(NSString *)string
                   password:(NSData *)password
                       salt:(NSString *)salt
                         iv:(NSData*)iv
                      error:(NSError **)error;

+(NSString *)decryptString:(NSString *)string
                     error:(NSError **)error;

+ (NSString *)decryptString:(NSString *)string
                   password:(NSData *)password
                       salt:(NSString *)salt
                         iv:(NSData*)iv
                      error:(NSError **)error;

+ (NSData *)encryptData:(NSData *)data
               password:(NSData *)password
                     iv:(NSData *)iv
                   salt:(NSData *)salt
                  error:(NSError **)error;

+ (NSData *)decryptData:(NSData *)data
               password:(NSData *)password
                     iv:(NSData *)iv
                   salt:(NSData *)salt
                  error:(NSError **)error;

+ (NSData *)getRandomIv;

+ (NSData *)getIvFromPayload:(NSString*)payload;

+ (NSString*)getMessageFromPayload:(NSString*)payload;

+ (NSData*)generateKey:(NSString *)password salt:(NSString*)salt;

+ (NSData*)getKey;

@end