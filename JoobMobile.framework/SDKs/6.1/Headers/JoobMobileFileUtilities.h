/****************************************************************************
 
 P R O P R I E T A R Y   N O T I C E
 
 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.
 
 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED
 
 ****************************************************************************/

#import <Foundation/Foundation.h>


@interface JoobMobileFileUtilities : NSObject {
    
}

/**
 A method to find or create the requested directory.
 @param searchPath The path to create the directory at. 
 @param domainMask The domain type can be NSUserDomainMask, NSLocalDomainMask, NSNetworkDomainMask, NSSystemDomainMask or NSAllDomainsMask
 @param appendPath The name of the requested directory
 @returns A NSString representation of the fully qualified path to the new directory.
 */
+(NSString *)findOrCreateDirectory:(NSSearchPathDirectory)searchPath
                           inDomain:(NSSearchPathDomainMask)domainMask
                           appendPath:(NSString *)appendPath 
                           error:(NSError **)errorDetails;

/**
 A method to create a directory
 @param path The fully qualified path to the directory to create
 @param withIntermediateDirectories BOOL to specifiy whether to create non existent parent directories to the one you requested
 @param attributes A NSDictionary contains attributes to apply to the directory when created
 @param errorDetails A pointer to an NSError object to be populated should an error occur
 @returns A BOOL declaring whether the directory was successfully created or not.
 */
+(BOOL)createDirectory:(NSString*)path createIntermediateDirectories:(BOOL)withIntermediateDirectories 
        withAttributes:(NSDictionary*)attributes 
                 error:(NSError **)errorDetails;

/** 
 A method to check whether a directory currently exists
 @param path The fully qualified path you wish to check
 @param isDirectory A pointer to a BOOL which gets set to indicate whether the path is a directory
 returns A BOOL declaring whether the path exists
 */
+(BOOL)directoryExists:(NSString*)path isDirectory:(BOOL*)isDirectory;

/**
 A method to get the path to the current applications support directory, it will create it if it doesnt currently exist
 @returns A NSString representatoin of the fully qualified path to the application support directory
 */
+(NSString *)applicationSupportDirectory;

@end
