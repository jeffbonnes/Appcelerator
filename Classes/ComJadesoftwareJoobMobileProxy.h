/**
 Copyright 2013 Quickstone Software LLC and Jade Software Corporation Ltd.
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#import <Foundation/Foundation.h>
#import "TiProxy.h"
#import "JoobMobile.h"

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
