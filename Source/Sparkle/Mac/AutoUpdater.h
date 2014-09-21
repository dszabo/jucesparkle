//
//  AutoUpdater.cpp
//  NewProject
//
//  Created by Daniel Szabo on 21/09/14.
//
//

#include <codecvt>

class AutoUpdater
{
public:
    virtual void checkForUpdates() = 0;
    virtual void checkForUpdatesBackground() = 0;
};

class SparkleAutoUpdater : public AutoUpdater
{
public:
    SparkleAutoUpdater(const std::wstring &aUrl);
    ~SparkleAutoUpdater();
    virtual void checkForUpdatesBackground();
    virtual void checkForUpdates();
private:
    class Private;
    Private* d;
};

