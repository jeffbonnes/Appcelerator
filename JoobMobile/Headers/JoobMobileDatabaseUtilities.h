/****************************************************************************
 
 P R O P R I E T A R Y   N O T I C E
 
 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.
 
 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED
 
 ****************************************************************************/

#import <UIKit/UIKit.h>
#import <CoreData/CoreData.h>


@interface JoobMobileDatabaseUtilities : NSObject {
    
}

/**
 A method to access/create the persistent store coordinator for the JoobMobile Datastore.
 @returns The current persistent store coordinator for the JoobMobile Datastore.
 */
+(NSPersistentStoreCoordinator*)persistentStoreCoordinator;

/**
 A method to access/generate the persistent object model for the JoobMobile Datastore.
 @returns The current JoobMobile Datastore object model.
 */
+(NSManagedObjectModel*)managedObjectModel;

/**
 A method to access a connection to the JoobMobile Datastore.
 @returns A NSManagedObjectContext to access the JoobMobile DataStore with.
 */
+(NSManagedObjectContext*)getContext;


/**
 Fetches all objects of the specified entity type from Core Data.
 @return An array of matched objects.
 */
+ (NSArray*)getObjects:(NSString*)entity;


/**
  Fetches all objects of the specified entity type from Core Data using the specified predicate search pattern.
  @return An array of matched objects.
 */
+ (NSArray*)getObjects:(NSString*)entity matching:(NSPredicate*)searchPredicate;


/**
 A method to save state to the context passed in.
 @param A NSManagedObjectContext to save state against.
 */
+(void)saveContext:(NSManagedObjectContext*)context;

/**
 A method to retreieve a JoobMobileMessage object from the Datastore using a UUID.
 @param uri The unique uri for the object required. 
 @param context A valid NSManagedObjectContext to perform operations on
 @returns The object matching the uri provided or nil if not found.
 */
+(NSManagedObject *)getObjectWithURI:(NSURL *)uri usingContext:(NSManagedObjectContext*)context;

/**
 A method to delete a JoobMobileMessage object from the Datastore using a UUID.
 @param uri The unique uri for the object targeted for deletion. 
 @param context A valid NSManagedObjectContext to perform operations on
 @returns A Bool indicating whether the operation was successfull.
 */
+(BOOL)deleteObjectWithURI:(NSURL*)uri usingContext:(NSManagedObjectContext*)context;


@end
