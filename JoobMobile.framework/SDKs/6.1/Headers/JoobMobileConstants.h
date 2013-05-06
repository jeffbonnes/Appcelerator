/****************************************************************************

 P R O P R I E T A R Y   N O T I C E

 This software, in whole and in every part, is proprietary to Jade Software
 Corporation Limited at Christchurch, New Zealand and is not to be reproduced,
 used or disclosed except upon prior written permission of Jade Software
 Corporation Limited.

 COPYRIGHT (c) JADE SOFTWARE CORPORATION LIMITED 2013 - ALL RIGHTS RESERVED

 ****************************************************************************/

// Authentication Notification constant
extern NSString *const JoobMobileAuthenticationStatusChanged;
extern NSString *const JoobMobileMultiFactorAuthenticationRequired;
extern NSString *const JoobMobileDeviceRegistrationRequired;

// Authentication Status constants
extern NSString *const Authenticating;
extern NSString *const Authenticated;
extern NSString *const Unauthenticated;
extern NSString *const AuthenticationFailed;

// Authentication Failure Reason constants
extern NSString *const NoFailureReason;
extern NSString *const InvalidCredentials;
extern NSString *const NoNetworkConnection;
extern NSString *const NetworkProblem;
extern NSString *const EndpointUnavailable;
extern NSString *const InvalidRootDocument;
extern NSString *const InvalidSettingsDocument;
extern NSString *const ApplicationDisabled;
extern NSString *const DeviceInformationUnavailable;

// Error constants
extern NSString *const ErrorInformationKey;
extern NSString *const ErrorDomain;

// HTTP verbs
extern NSString *const POST;
extern NSString *const GET;

// JoobMobile constants
extern NSString *const JoobMobileKey;

// Message constants
typedef enum messageStates
        {
            PENDING,
            INPROGRESS,
            FAILED,
            MFAREQUIRED
        } MessageState;
