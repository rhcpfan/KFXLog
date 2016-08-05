
/**********************************************************************
 *
 Copyright (c) 2016 Christian Fox <christianfox890@icloud.com>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 *
 **********************************************************************/


#import <Foundation/Foundation.h>
// Descriptors
#import "KFXBasicLogDescriptor.h"
#import "KFXCleanLogDescriptor.h"
#import "KFXFileLogDescriptor.h"
#import "KFXAlertLogDescriptor.h"
#import "KFXServiceLogDescriptor.h"
// Loggers
#import "KFXServiceLoggerInterface.h"

NS_ASSUME_NONNULL_BEGIN
@interface KFXLogConfigurator : NSObject

// # global Log settings #
/// Manually defined build configuration (None / Debug / AdHoc / Release) If set to none we will attempt to work it out from preprocessor macros
@property (nonatomic) KFXBuildConfiguration buildConfiguration;
/// KFXLogMediums bitmask for when in debug configuration (ToConsole, ToAlert, ToFile, ToService)
@property (nonatomic) KFXLogMediums debugLogMediums;
/// KFXLogMediums bitmask for when in adHoc configuration (ToConsole, ToAlert, ToFile, ToService)
@property (nonatomic) KFXLogMediums adHocLogMediums;
/// KFXLogMediums bitmask for when in release configuration (ToConsole, ToAlert, ToFile, ToService)
@property (nonatomic) KFXLogMediums releaseLogMediums;
/// Basic or Clean aka NSLog or print
@property (nonatomic) KFXConsoleLogType consoleLogType;

@property (nonatomic) BOOL shouldCatchUncaughtExceptions;

// # Log Type descriptors - (Lazily loaded except serviceLogDesciptor) #
/// The descriptor for when using basic console logging (aka NSLog)
@property (strong ,nonatomic, readonly) KFXBasicLogDescriptor *basicLogDescriptor;
/// The descriptor for when using clean console logging (aka print)
@property (strong ,nonatomic, readonly) KFXCleanLogDescriptor *cleanLogDescriptor;
/// The descriptor for logging to a file
@property (strong ,nonatomic, readonly) KFXFileLogDescriptor *fileLogDescriptor;
/// The log descriptor for logging to a UIAlertController
@property (strong ,nonatomic, readonly) KFXAlertLogDescriptor *alertLogDescriptor;
/// The log descriptor for logging to a service such as a 3rd party analytics service or to a private backend
@property (strong ,nonatomic, readwrite) KFXServiceLogDescriptor *serviceLogDescriptor;

// # Loggers #
/// The object that handles logging to a service. Create a object that conforms to KFXServiceLogger protocol and set this property.
@property (strong ,nonatomic, readwrite) id<KFXServiceLoggerInterface> serviceLogger;




/**
 *  The only way you should access this object. If you initilise this configurator directly then your settings will not be read by KFXLogger.
 *
 *  @return An instance of KFXLoggerConfigurator.
 *
 *  @since 0.1.0
 */
+(instancetype)sharedConfigurator;


/// Logs settings to the console using NSLog
-(void)printSettings;

@end
NS_ASSUME_NONNULL_END