//
//  AutoUpdater.mm
//  NewProject
//
//  Created by Daniel Szabo on 21/09/14.
//
//

#include "AutoUpdater.h"
#include <Sparkle/Sparkle.h>
#include "NSStringAdditions.h"



class SparkleAutoUpdater::Private {
public:
    SUUpdater* updater;
};

SparkleAutoUpdater::SparkleAutoUpdater(const std::wstring& aUrl) {
    d = new Private;
    d->updater = [[SUUpdater sharedUpdater] retain];
    
    
    
    NSURL* url = [NSURL URLWithString:
                  [NSString stringWithCPPWString:aUrl]];
    [d->updater setFeedURL: url];
}

SparkleAutoUpdater::~SparkleAutoUpdater() {
    [d->updater release];
    delete d;
}

void SparkleAutoUpdater::checkForUpdates() {
    [d->updater checkForUpdates:NULL];
}

void SparkleAutoUpdater::checkForUpdatesBackground() {
    [d->updater checkForUpdatesInBackground];
}