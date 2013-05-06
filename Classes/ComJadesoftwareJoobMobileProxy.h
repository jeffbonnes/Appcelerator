//
//  ComJadesoftwareJoobMobileProxy.h
//  JOOB Mobile
//
//  Created by Dale Anderson on 6/05/13.
//
//

#import <Foundation/Foundation.h>
#import "TiProxy.h"
#import <JoobMobile/JoobMobile.h>

@interface ComJadesoftwareJoobMobileProxy : TiProxy<JoobMobileDelegate> {

}

@property(nonatomic,readwrite,assign) NSString *rootDocumentUrl;

/**
 A generic method to trigger the javascript callback via the Appcelerator framework and pass the response.
 @param state The state object passed to the Joob Mobile API when the request was invoked.
 @param result The JoobMobileHttpResult object returned from the request.
 @param success BOOL indicating whether the response indicated the request was successful.
 */
-(void)fireJavascriptCallback:(NSObject*)state httpResult:(JoobMobileHttpResult*)result wasSuccessful:(BOOL)success;

/**
 A method to pull the javascript callback from the Joob Mobile http result object.
 @param state The state object passed to the Joob Mobile API when the request was invoked.
 @param type Basically the name of the javascript function "success" or "failure"
 @returns The Appcelerator callback object.
 */
-(KrollCallback*)getJavascriptCallbackFromState:(NSObject*)state type:(NSString*)type;

/**
 A method to generate an event object to pass to the javascript callback.
 @param result The JoobMobileHttpResult object returned from the request.
 @returns A NSDictionary object representing the event.
 */
-(NSDictionary*)createEventFromJoobMobileHttpResult:(JoobMobileHttpResult*)result;

@end
