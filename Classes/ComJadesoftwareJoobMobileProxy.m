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

#import "ComJadesoftwareJoobMobileProxy.h"
#import "TiUtils.h"
#import "JoobMobileFactory.h"
#import "JoobMobileAuthenticationUtils.h"
#import "JoobMobileMessage.h"
#import "JoobMobileRemoteLogger.h"
#import "JoobMobileParser.h"

@interface ComJadesoftwareJoobMobileProxy()

@property (nonatomic, retain) JoobMobile *joobMobile;

@property (nonatomic, retain) KrollCallback *logoutCompleteCallback;

@end

@implementation ComJadesoftwareJoobMobileProxy


-(void) _configure
{
    
    _joobMobile = [[JoobMobileFactory getApi:self] retain];
    
    NSLog(@"[INFO] JoobMobile is initialized - %@", _joobMobile);
    
    [super _configure];
}


-(void) _destroy
{
    RELEASE_TO_NIL(_joobMobile);
    [super _destroy];
}


#pragma -mark JOOB Mobile delegate methods


- (void) multiFactorAuthenticationRequired:(JoobMobileMultiFactorToken *)token
{
    if ([self _hasListeners:@"multifactorAuthenticationRequiredEvent"]) {
        
        NSDictionary *event = @{@"token": token};
        
        [self fireEvent:@"multifactorAuthenticationRequiredEvent" withObject:event];
        
        NSLogDebug(@"MultiFactor Authentication Required Event Fired.");
    }
}

- (void) deviceRegistrationRequired
{
    if ([self _hasListeners:@"deviceRegistrationRequiredEvent"]) {
        
        [self fireEvent:@"deviceRegistrationRequiredEvent" withObject:nil];
        
        NSLogDebug(@"Device Registration Required Event Fired.");
    }
    
}

- (void) applicationDisabled:(NSString*) reason
{
    if ([self _hasListeners:@"applicationDisabledEvent"]) {
        
        NSDictionary *event = @{@"reason": reason};
        
        [self fireEvent:@"applicationDisabledEvent" withObject:event];
        
        NSLogDebug(@"Application Disabled Event Fired.");
    }
}

- (void) deviceInformationUpdated:(NSDictionary*) information
{
    if ([self _hasListeners:@"deviceInformationUpdated"]) {

        NSDictionary *event = @{@"information": information};

        [self fireEvent:@"deviceInformationUpdated" withObject:event];

        NSLogDebug(@"Device Information Updated Event Fired.");
    }

}

-(void)logoutCompleted
{
    NSLog(@"[INFO] Received logout callback");
    if (_logoutCompleteCallback)
    {
        [self _fireEventToListener:@"completed" withObject:nil listener:_logoutCompleteCallback
                        thisObject:nil];
    }
}

#pragma -mark CallBacks


-(KrollCallback*)getJavascriptCallbackFromState:(NSObject*)state type:(NSString*)type
{
    return [(NSDictionary*)state objectForKey:type];
}


-(NSDictionary*)createEventFromJoobMobileHttpResult:(JoobMobileHttpResult*)result
{
    // Nasty for the moment but ...

    id body = nil;

    NSString *bodyString = [[NSString alloc] initWithData:result.responseBody encoding:NSUTF8StringEncoding];

    NSLogDebug(@"BodyString: %@", bodyString);

    if (bodyString != nil) {
        body = bodyString;
    }  else {
        body =  [[TiBlob alloc] initWithData:result.responseBody mimetype:@"application/octet-stream"];
    }

    NSDictionary *event = [NSDictionary dictionaryWithObjectsAndKeys:
                           result.uuid,@"uuid",
                           result.responseHeaders, @"headers",
                           body, @"body",
                           [NSNumber numberWithInt:result.statusCode],@"status",
                           nil];
    return event;
}


#pragma -mark Exposed methods

- (id) parseMicrosoftDate:(id)arg
{
    ENSURE_SINGLE_ARG(arg,NSString);

    return [JoobMobileParser getDateFromMSDate:[TiUtils stringValue:arg]];
}

- (void) registerDevice:(id)token
{
    ENSURE_SINGLE_ARG(token,NSString);
    
    [_joobMobile registerDevice:token];
}


- (void) respondToMultiFactorChallenge:(id)args
{
    enum Args {
        argToken = 0,
        argResponse,
        argCount
    };
    
    ENSURE_ARG_COUNT(args, argCount);
    
    JoobMobileMultiFactorToken *token = [args objectAtIndex:argToken];
    
    NSDictionary *response = [args objectAtIndex:argResponse];
    
    [_joobMobile respondToMultiFactorChallenge:token withResponse:response];
    
}

// Returns the Uri from the root document for the key provided.
-(id)getRootDocumentUri:(id)value
{
    ENSURE_SINGLE_ARG(value,NSString);
    NSURL *url = [JoobMobileSettings getRootDocumentUri:[TiUtils stringValue:value]];
    return [url absoluteString];
}


// Sets default basic authentication credentials.
-(void)setBasicAuthenticationToken:(id)args
{
    ENSURE_UI_THREAD(setBasicAuthenticationToken, args)
    
    NSLog(@"Setting basic authentication token");
    
    enum Args {
        argUsername = 0,
        argPassword,
        argCount
    };
    
    ENSURE_ARG_COUNT(args, argCount);
    
    NSString *username = [TiUtils stringValue:[args objectAtIndex:argUsername]];
    
    NSString *password = [TiUtils stringValue:[args objectAtIndex:argPassword]];
    
    [JoobMobileAuthenticationUtils setBasicAuthenticationToken:username password:password];
}

// Sets an authentication token for use with custom authentication server side.
-(void)setUserToken:(id)args
{
    ENSURE_SINGLE_ARG(args,NSDictionary);
    
    // As the args are already converted to a NSDictionary type pass straight through,
    // Mobile will throw an exception if the token is invalid.
    [JoobMobileSettings setUserToken:args];
}


// Calls login on the Joob Mobile API
-(void)login:(id)args
{
    NSLog(@"[INFO] JoobMobile Login method");
    
    ENSURE_UI_THREAD(login, args)
    
    enum Args {
        argRootDocumentUri = 0,
        argSuccessCallback,
        argFailureCallback,
        argTimeout,
        argCount
    };
    
    ENSURE_ARG_COUNT(args, argCount);

    KrollCallback* successCallback = [[args objectAtIndex:argSuccessCallback] retain];
    KrollCallback* failureCallback = [[args objectAtIndex:argFailureCallback] retain];
    NSString *rootDocumentUri = [TiUtils stringValue:[args objectAtIndex:argRootDocumentUri]];
    int timeToLive = [TiUtils intValue:[args objectAtIndex:argTimeout]];

    [_joobMobile login:[NSURL URLWithString:rootDocumentUri] onSuccess:^(NSString *result) {
        NSLog(@"login success callback hit");
        
        NSArray* returnArray = [NSArray arrayWithObjects: result, nil];
        dispatch_async(dispatch_get_main_queue(), ^{
            [successCallback call:returnArray thisObject:nil];
        });

    } onFailure:^(NSString *result) {
        NSLog(@"login failure callback hit");
        
        NSArray* returnArray = [NSArray arrayWithObjects: result, nil];
        dispatch_async(dispatch_get_main_queue(), ^{
            [failureCallback call:returnArray thisObject:nil];
        });
        
    } withTimeout:timeToLive];
}


// Calls logout on the Joob Mobile API.
-(void)logout:(id)args
{
    ENSURE_SINGLE_ARG(args,NSDictionary);
    id complete = [args objectForKey:@"completed"];
    
    RELEASE_TO_NIL(_logoutCompleteCallback);
    
    _logoutCompleteCallback = [complete retain];
    [_joobMobile logout];
}


-(id)sendDataItem:(id)args
{
    ENSURE_SINGLE_ARG(args,NSDictionary);
    
    // Make sure the payload IS a NSDictionary
    NSDictionary *payload = [args valueForKey:@"payload"];
    
    // Define callbacks for success and failure.
    KrollCallback *successCallback = [args valueForKey:@"onSuccess"];
    KrollCallback *failureCallback = [args valueForKey:@"onFailure"];
    
    // Set priority and time to live values.
    NSString *priority = [TiUtils stringValue:[args valueForKey:@"priority"]];
    NSInteger timeToLive = [TiUtils intValue:[args valueForKey:@"timeToLive"]];
    
    // Set default persist value so if its not passed in we go with the safe option.
    BOOL persistToDisk = true;
    
    if ([args valueForKey:@"persistToDisk"] != NULL) {
        persistToDisk =  [TiUtils boolValue:[args valueForKey:@"persistToDisk"]];
    }
    
    NSLog(@"[INFO] Calling JoobMobile API to send Dataitem", _joobMobile);
    
    return [_joobMobile sendDataItem:payload dataType:[TiUtils stringValue:[args valueForKey:@"dataType"]] onSuccess:^(JoobMobileHttpResult *result) {
        NSDictionary *resultDictionary = [self createEventFromJoobMobileHttpResult:result];
        NSArray *returnArray = @[resultDictionary];
        [successCallback call:returnArray thisObject:self];
        
    } onFailure:^(JoobMobileHttpResult *result) {
        NSDictionary *resultDictionary = [self createEventFromJoobMobileHttpResult:result];
        NSArray *returnArray = @[resultDictionary];
        [failureCallback call:returnArray thisObject:self];
    }];
}


-(id)GET:(id)args
{
    ENSURE_SINGLE_ARG(args,NSDictionary);
    
    // Define callbacks for success and failure.
    KrollCallback *successCallback = [args valueForKey:@"onSuccess"];
    KrollCallback *failureCallback = [args valueForKey:@"onFailure"];
    
    // Set priority and time to live values.
    NSString *priority = [TiUtils stringValue:[args valueForKey:@"priority"]];
    NSInteger timeToLive = [TiUtils intValue:[args valueForKey:@"timeToLive"]];
    
    // Set priority and time to live values to sane defaults if they are not passed in.
    if (priority == nil) {priority = MESSAGE_PRIORITY_NORMAL;}
    if ([args valueForKey:@"timeToLive"] == nil) {timeToLive = TIMETOLIVE_TRYONCE;}

    // Call JoobMobile and return UUID.
    return [_joobMobile get:[NSURL URLWithString:[TiUtils stringValue:[args valueForKey:@"url"]]]
            onSuccess:^(JoobMobileHttpResult *result) {
                NSDictionary *resultDictionary = [self createEventFromJoobMobileHttpResult:result];
                NSArray *returnArray = @[resultDictionary];
                [successCallback call:returnArray thisObject:self];
            } onFailure:^(JoobMobileHttpResult *result) {
                NSDictionary *resultDictionary = [self createEventFromJoobMobileHttpResult:result];
                NSArray *returnArray = @[resultDictionary];
                [failureCallback call:returnArray thisObject:self];
            } priority:priority timeToLive:timeToLive];
}


-(id)POST:(id)args
{
    ENSURE_SINGLE_ARG(args,NSDictionary);
    
    // Define callbacks for success and failure.
    KrollCallback *successCallback = [args valueForKey:@"onSuccess"];
    KrollCallback *failureCallback = [args valueForKey:@"onFailure"];
    
    // Set priority and time to live values.
    NSString *priority = [TiUtils stringValue:[args valueForKey:@"priority"]];
    NSInteger timeToLive = [TiUtils intValue:[args valueForKey:@"timeToLive"]];
    
    // Set priority and time to live values to sane defaults if they are not passed in.
    if (priority == nil) {priority = MESSAGE_PRIORITY_NORMAL;}
    if ([args valueForKey:@"timeToLive"] == nil) {timeToLive = TIMETOLIVE_TRYONCE;}
    
    // Set default persist value so if its not passed in we go with the safe option.
    BOOL persistToDisk = true;
    
    if ([args valueForKey:@"persistToDisk"] != NULL) {
        persistToDisk =  [TiUtils boolValue:[args valueForKey:@"persistToDisk"]];
    }

    // Call JoobMobile and return UUID.
    return [_joobMobile post:[NSURL URLWithString:[TiUtils stringValue:[args valueForKey:@"url"]]]
            postData:[TiUtils stringValue:[args valueForKey:@"postData"]]
            onSuccess:^(JoobMobileHttpResult *result) {
                NSDictionary *resultDictionary = [self createEventFromJoobMobileHttpResult:result];
                NSArray *returnArray = @[resultDictionary];
                [successCallback call:returnArray thisObject:self];
            } onFailure:^(JoobMobileHttpResult *result) {
                NSDictionary *resultDictionary = [self createEventFromJoobMobileHttpResult:result];
                NSArray *returnArray = @[resultDictionary];
                [failureCallback call:returnArray thisObject:self];
            } priority:priority timeToLive:timeToLive];
}

- (void)dealloc {
    [_joobMobile release];
    [_logoutCompleteCallback release];
    [super dealloc];
}

@end
