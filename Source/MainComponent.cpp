/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#if JUCE_MAC
#include "AutoUpdater.h"
#endif

#if JUCE_MSVC
#include <winsparkle.h>
#endif



//==============================================================================
MainContentComponent::MainContentComponent()
{
    setSize (500, 400);
    
    button = new TextButton(L"Check for updates");
    button->setBounds(10, 10, 100, 40);
    button->addListener(this);
    
    label = new Label(L"label1", L"This is a label in 1.0.1");
    label->setBounds(10, 60, 200, 30);
    addAndMakeVisible(button);
    addAndMakeVisible(label);

}

MainContentComponent::~MainContentComponent()
{
    deleteAllChildren();

}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xffffffff));

    g.setFont (Font (16.0f));
    g.setColour (Colours::black);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainContentComponent::buttonClicked(Button* button)
{
    //label->setText(L"Hello World", juce::NotificationType::dontSendNotification);
#if JUCE_MAC
    AutoUpdater* updater = 0;
    updater = new SparkleAutoUpdater(L"http://localhost:8080/releases/mac/SparkTestAppcast.xml");
    updater->checkForUpdates();
#endif

#if JUCE_MSVC
	win_sparkle_check_update_with_ui();
#endif
    

}

