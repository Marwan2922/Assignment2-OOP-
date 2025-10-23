

#include "PlayerGUI.h"
using namespace std;
using namespace juce;

PlayerGUI::PlayerGUI()
{
    // Add buttons
    for (auto* btn : { &loadButton, &endButton , &stopButton , &playButton , &muteButton,&gotostartButton })
    {
        btn->addListener(this);
        addAndMakeVisible(btn);
    }

    // Volume slider
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

    // muted button 
    muteButton.setButtonText("Mute");
    muteButton.setToggleState(true, juce::dontSendNotification);
    muteButton.setClickingTogglesState(true);

    muteButton.onClick = [this]() {
        const bool ismuted = muteButton.getToggleState();
        muteButton.setButtonText(ismuted ? "mute" : "unmute");
        playerAudio.setGain(ismuted ? 1.0f : 0.0f);
        };
    addAndMakeVisible(&muteButton);
}
PlayerGUI::~PlayerGUI()
{
}

void PlayerGUI::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    playerAudio.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerGUI::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    playerAudio.getNextAudioBlock(bufferToFill);
}

void PlayerGUI::releaseResources()
{
    playerAudio.releaseResources();
}
void PlayerGUI::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
}


void PlayerGUI::resized()
{
    int y = 20;
    loadButton.setBounds(20, y, 100, 40);
    stopButton.setBounds(240, y, 80, 40);
    muteButton.setBounds(340, y, 80, 40);
    playButton.setBounds(440, y, 80, 40);
    endButton.setBounds(540, y, 80, 40);
    gotostartButton.setBounds(640, y, 100, 40);
    /*prevButton.setBounds(340, y, 80, 40);
    nextButton.setBounds(440, y, 80, 40);*/

    volumeSlider.setBounds(20, 100, getWidth() - 40, 30);

}

void PlayerGUI::buttonClicked(juce::Button* button)
{
    if (button == &loadButton)
    {
        juce::FileChooser chooser("Select audio files...",
            juce::File{},
            "*.wav;*.mp3");

        fileChooser = std::make_unique<juce::FileChooser>(
            "Select an audio file...",
            juce::File{},
            "*.wav;*.mp3");

        fileChooser->launchAsync(
            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file.existsAsFile())
                {
                    playerAudio.loadFile(file);
                }
            });
    }


    if (button == &stopButton)
    {
        playerAudio.stop();
        playerAudio.setPosition(0.0);
    }

    if (button == &playButton)
    {
        playerAudio.start();
    }


    if (button == &muteButton)
    {
        playerAudio.mute();
    }
    if (button == &gotostartButton) {
        playerAudio.start();
        playerAudio.setPosition(0.0);
    }
    if (button == &endButton) {
        playerAudio.getLength();
        playerAudio.setPosition(playerAudio.getLength());
    }



}


void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
        playerAudio.setGain((float)slider->getValue());


}

