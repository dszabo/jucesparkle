//
//  NSStringAdditions.h
//  NewProject
//
//  Created by Daniel Szabo on 21/09/14.
//
//

#ifndef __NewProject__NSStringAdditions__
#define __NewProject__NSStringAdditions__

#import <Cocoa/Cocoa.h>

#import <string>

@interface NSString (NSStringAdditions)

+ (NSString *)stringWithCPPString:(const std::string&)s;
- (std::string)cppString;

+ (NSString *)stringWithCPPWString:(const std::wstring&)ws;
- (std::wstring)cppWString;

@end

#endif /* defined(__NewProject__NSStringAdditions__) */
