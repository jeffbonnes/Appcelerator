//
//  ComJadesoftwareJoobMobileProxy.m
//  JOOB Mobile
//
//  Created by Dale Anderson on 6/05/13.
//
//

#import "ComJadesoftwareJoobMobileProxy.h"
#import "TiUtils.h"
#import "TiBlob.h"
#import <JoobMobile/JoobMobileFactory.h>
#import <JoobMobile/JoobMobileAuthenticationUtils.h>
#import <JoobMobile/JoobMobileMessage.h>
#import <JoobMobile/JoobMobileSettings.h>

@interface ComJadesoftwareJoobMobileProxy()

@property (nonatomic, retain) JoobMobile *joobMobile;

@property (nonatomic, retain) KrollCallback *logoutCompleteCallback;

@end

@implementation ComJadesoftwareJoobMobileProxy

@synthesize rootDocumentUrl;


-(void) _configure
{
    
    _joobMobile = [JoobMobileFactory getApi:self];
    
    NSLog(@"[INFO] JoobMobile is initialized - %@", _joobMobile);
    
    [super _configure];
}


-(void) _destroy
{
    RELEASE_TO_NIL(rootDocumentUrl);
    RELEASE_TO_NIL(_joobMobile);
    [super _destroy];
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
    
    NSLog(@"Setting basic authentication token");
    
    enum Args {
        argUsername = 0,
        argPassword,
        argCount
    };
    
    ENSURE_ARG_COUNT(args, argCount);
    
    [JoobMobileAuthenticationUtils setBasicAuthenticationToken:[TiUtils stringValue:[args objectAtIndex:argUsername]] password:[TiUtils stringValue:[args objectAtIndex:argPassword]]];
}


#pragma JOOB Mobile delegate methods

-(void)logoutCompleted
{
    NSLog(@"[INFO] Received logout callback");
    if (_logoutCompleteCallback)
    {
        [self _fireEventToListener:@"completed" withObject:nil listener:_logoutCompleteCallback
                        thisObject:nil];
    }
}

#pragma CallBacks


-(void)fireJavascriptCallback:(NSObject*)state httpResult:(JoobMobileHttpResult*)result wasSuccessful:(BOOL)success
{
    
    // Define callback.
    KrollCallback* callback;
    
    
    // If it is a successful response call getJavascriptCallbackFromState with appropriate parameters.
    if (success) {
        callback = [self getJavascriptCallbackFromState:state type:@"success"];
    } else {
        callback = [self getJavascriptCallbackFromState:state type:@"failure"];
    }
    
    
    // If we have a callback attempt to fire it.
    if (callback) {
        NSDictionary *event = [self createEventFromJoobMobileHttpResult:result];
        [self _fireEventToListener:@"success" withObject:event listener:callback thisObject:nil];
    } else {
        NSLog(@"[INFO] - No callback provided to the JoobMobile Appcelerator Module.");
    }
}


-(KrollCallback*)getJavascriptCallbackFromState:(NSObject*)state type:(NSString*)type
{
    return [(NSDictionary*)state objectForKey:type];
}


-(NSDictionary*)createEventFromJoobMobileHttpResult:(JoobMobileHttpResult*)result
{
    NSDictionary *event = [NSDictionary dictionaryWithObjectsAndKeys:
                           result.uuid,@"uuid",
                           result.responseHeaders, @"headers",
                           [[[TiBlob alloc] initWithData:result.responseBody mimetype:@"application/octet-stream"] autorelease], @"body",
                           [NSNumber numberWithInt:result.statusCode],@"status",
                           nil];
    return event;
}


-(void)sendDataItemSuccessCallback:(NSObject*) userState joobMobileHttpResult:(JoobMobileHttpResult*) result
{
    NSLog(@"[INFO] Received sendDataItem success callback: %@",result);
    
    [self fireJavascriptCallback:userState httpResult:result wasSuccessful:true];
}


-(void)sendDataItemFailureCallback:(NSObject*) userState joobMobileHttpResult:(JoobMobileHttpResult*) result
{
    NSLog(@"[INFO] Received sendDataItem failure callback: %@",result);
    
    [self fireJavascriptCallback:userState httpResult:result wasSuccessful:false];
}


-(void)postSuccessCallback:(NSObject*) userState joobMobileHttpResult:(JoobMobileHttpResult*) result
{
    NSLog(@"[INFO] Received post success callback: %@",result);
    
    [self fireJavascriptCallback:userState httpResult:result wasSuccessful:true];
}


-(void)postFailureCallback:(NSObject*) userState joobMobileHttpResult:(JoobMobileHttpResult*) result
{
    NSLog(@"[INFO] Received post failure callback: %@",result);
    
    [self fireJavascriptCallback:userState httpResult:result wasSuccessful:false];
}


-(void)getSuccessCallback:(NSObject*) userState joobMobileHttpResult:(JoobMobileHttpResult*) result
{
    NSLog(@"[INFO] Received get success callback: %@",result);
    
    [self fireJavascriptCallback:userState httpResult:result wasSuccessful:true];
}


-(void)getFailureCallback:(NSObject*) userState joobMobileHttpResult:(JoobMobileHttpResult*) result
{
    NSLog(@"[INFO] Received get failure callback: %@",result);
    
    [self fireJavascriptCallback:userState httpResult:result wasSuccessful:false];
}


#pragma Exposed methods


// Sets an authentication token for use with custom authentication server side.
-(void)setUserToken:(id)args
{
    ENSURE_SINGLE_ARG(args,NSDictionary);
    
    // As the args are already converted to a NSDictionary type pass straight through,
    // Mobile will throw an exception if the token is invalid.
    [JoobMobileSettings setUserToken:args];
}


// Sets the default ( root document ) endpoint.
-(void)setRootDocumentUrl:(id)value
{
    rootDocumentUrl = [TiUtils stringValue:value];
    [self replaceValue:value forKey:@"rootDocumentUrl" notification:NO];
    NSLog(@"[INFO] stored rootDocument: %@",rootDocumentUrl);
}


// Returns the default ( root document ) endpoint.
-(NSString*)rootDocumentUrl
{
    return rootDocumentUrl;
}


// Calls login on the Joob Mobile API
-(void)login:(id)args
{
    ENSURE_SINGLE_ARG(args,NSDictionary);
    
    NSLog(@"[INFO] JoobMobile Login method - %@",_joobMobile);
    
    id successCallback = [args objectForKey:@"onSuccess"];
    id failureCallback = [args objectForKey:@"onFailure"];
    id url = [args valueForKey:@"url"];
    id timeToLive = [args valueForKey:@"timeToLive"];
    
    if (url != NULL) {
        [_joobMobile login:[NSURL URLWithString:url] onSuccess:^(NSString *result) {
            NSDictionary *event = [NSDictionary dictionaryWithObjectsAndKeys:
                                   result,@"result",
                                   nil];
            [self _fireEventToListener:@"completed" withObject:event listener:successCallback
                            thisObject:nil];
        } onFailure:^(NSString *result) {
            NSDictionary *event = [NSDictionary dictionaryWithObjectsAndKeys:
                                   result,@"result",
                                   nil];
            [self _fireEventToListener:@"completed" withObject:event listener:failureCallback
                            thisObject:nil];
        } withTimeout:timeToLive];
    }

    NSLog(@"[INFO] submitted login for processing");
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
    
    // Define callbacks for success and failure.
    SEL successCallback = @selector(sendDataItemSuccessCallback:joobMobileHttpResult:);
    SEL failureCallback = @selector(sendDataItemFailureCallback:joobMobileHttpResult:);
    
    // Set priority and time to live values.
    NSString *priority = [TiUtils stringValue:[args valueForKey:@"priority"]];
    NSInteger timeToLive = [TiUtils intValue:[args valueForKey:@"timeToLive"]];
    
    // If priority and time to live are not defined set sane defaults.
    if (priority == nil) {priority = MESSAGE_PRIORITY_NORMAL;}
    if ([args valueForKey:@"timeToLive"] == nil) {timeToLive = TIMETOLIVE_TRYONCE;}
    
    // Create the data item payload.
    NSMutableDictionary *messagePayload = [[NSMutableDictionary alloc] init];
    [messagePayload setValue:[TiUtils stringValue:[args valueForKey:@"payload"]]
                      forKey:[TiUtils stringValue:[args valueForKey:@"dataType"]]];
    
    // Set default persist value so if its not passed in we go with the safe option.
    BOOL persistToDisk = true;
    
    if ([args valueForKey:@"persistToDisk"] != NULL) {
        persistToDisk =  [TiUtils boolValue:[args valueForKey:@"persistToDisk"]];
    }
    
    NSLog(@"[INFO] Calling JoobMobile API to send Dataitem", _joobMobile);
    
    return [_joobMobile sendDataItem:messagePayload dataType:[TiUtils stringValue:[args valueForKey:@"dataType"]] onSuccess:^(JoobMobileHttpResult *result) {
        [self fireJavascriptCallback:nil httpResult:result wasSuccessful:true];
        
    } onFailure:^(JoobMobileHttpResult *result) {
        [self fireJavascriptCallback:nil httpResult:result wasSuccessful:false];
    }];
}


-(id)GET:(id)args
{
    ENSURE_SINGLE_ARG(args,NSDictionary);
    
    // Define callbacks for success and failure.
    SEL successCallback = @selector(getSuccessCallback:joobMobileHttpResult:);
    SEL failureCallback = @selector(getFailureCallback:joobMobileHttpResult:);
    
    // Set priority and time to live values.
    NSString *priority = [TiUtils stringValue:[args valueForKey:@"priority"]];
    NSInteger timeToLive = [TiUtils intValue:[args valueForKey:@"timeToLive"]];
    
    // Set priority and time to live values to sane defaults if they are not passed in.
    if (priority == nil) {priority = MESSAGE_PRIORITY_NORMAL;}
    if ([args valueForKey:@"timeToLive"] == nil) {timeToLive = TIMETOLIVE_TRYONCE;}
    
    // Call JoobMobile and return UUID
    return [_joobMobile get:[NSURL URLWithString:[TiUtils stringValue:[args valueForKey:@"url"]]]
                 userState:args
            callbackTarget:self
           successCallback:successCallback
           failureCallback:failureCallback
                  priority:priority
                timeToLive:timeToLive];
}


-(id)POST:(id)args
{
    ENSURE_SINGLE_ARG(args,NSDictionary);
    
    // Define callbacks.
    SEL successCallback = @selector(postSuccessCallback:joobMobileHttpResult:);
    SEL failureCallback = @selector(postFailureCallback:joobMobileHttpResult:);
    
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
                  userState:args
             callbackTarget:self
            successCallback:successCallback
            failureCallback:failureCallback
                   priority:priority
                 timeToLive:timeToLive
              persistToDisk:persistToDisk];
}

@end