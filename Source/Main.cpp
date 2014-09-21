#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"
#if JUCE_MAC
#include "Sparkle/Mac/AutoUpdater.h"
#include "Sparkle/Mac/CocoaInitializer.h"
#endif

#if JUCE_MSVC
#include <Windows.h>
#include <winsparkle.h>
#include "Sparkle\Win\VersionData.h"
void NewProjectApplication_CallbackFunction_Wrapper();
#endif


//==============================================================================
class NewProjectApplication  : public JUCEApplication
{
public:
    //==============================================================================
    NewProjectApplication() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    //==============================================================================
    void initialise (const String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..

#if JUCE_MAC
        AutoUpdater* updater = 0;
        CocoaInitializer cocoaInitiarizer;
        updater = new SparkleAutoUpdater(L"http://localhost:8080/releases/mac/SparkTestAppcast.xml");
        updater->checkForUpdatesBackground();
#endif
        mainWindow = new MainWindow();

#if JUCE_MSVC
		win_sparkle_set_appcast_url("http://localhost:8080/releases/win/SparkTestAppcast.xml");
		// OMG, see http://www.parashift.com/c++-faq-lite/memfnptr-vs-fnptr.html how to pass a member function as a callback to external lib
		win_sparkle_set_shutdown_request_callback(NewProjectApplication_CallbackFunction_Wrapper);
		win_sparkle_set_app_details(L"MyCompany", L"NewProduct", VERSION_DISPLAY);
		win_sparkle_set_app_build_version(VERSION_BUILD);
		win_sparkle_init();
#endif
        
    }

#if JUCE_MSVC
	win_sparkle_shutdown_request_callback_t callbackOnShutdown()
	{
		OutputDebugStringW(L"Shutdown callback is called by winsparkle!");
		quit();
		return 0;
	}
#endif

    void shutdown() override
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainContentComponent class.
    */
    class MainWindow    : public DocumentWindow
    {
    public:
        MainWindow()  : DocumentWindow ("MainWindow",
                                        Colours::lightgrey,
                                        DocumentWindow::allButtons)
        {
            setContentOwned (new MainContentComponent(), true);

            centreWithSize (getWidth(), getHeight());
            setVisible (true);
        }

        void closeButtonPressed()
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    ScopedPointer<MainWindow> mainWindow;
};

#if JUCE_MSVC
NewProjectApplication* object_which_will_handle_signal;
void NewProjectApplication_CallbackFunction_Wrapper()
{
	object_which_will_handle_signal->callbackOnShutdown();
}
#endif


//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (NewProjectApplication)
