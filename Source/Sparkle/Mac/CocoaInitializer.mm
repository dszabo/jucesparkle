//
//  CocoaInitializer.cpp
//  NewProject
//
//  Created by Daniel Szabo on 21/09/14.
//
//

#include "CocoaInitializer.h"
#include <Cocoa/Cocoa.h>


class CocoaInitializer::Private
{
public:
    NSAutoreleasePool* autoReleasePool_;
};

CocoaInitializer::CocoaInitializer()
{
    d = new CocoaInitializer::Private();
    NSApplicationLoad();
    d->autoReleasePool_ = [[NSAutoreleasePool alloc] init];
}

CocoaInitializer::~CocoaInitializer()
{
    [d->autoReleasePool_ release];
    delete d;
}