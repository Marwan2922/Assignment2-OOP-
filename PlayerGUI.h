#pragma once // PlayerGUI.h
#include <JuceHeader.h>
#include "PlayerAudio.h"
using namespace std;
using namespace juce;

class PlayerGUI : public juce::Component,
	public Button::Listener,
	public Slider::Listener
{
public:
	PlayerGUI();
	~PlayerGUI() override;

	void resized() override;
	void paint(Graphics& g) override;

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill);
	void releaseResources();
private:
	PlayerAudio playerAudio;
	// GUI elements
	TextButton stopButton{ "Stop" };
	TextButton playButton{"play"};
	TextButton loadButton{ "Load File" };
TextButton gotostartButton{ "go to start" };
TextButton endButton{ "End" };
	TextButton muteButton;

	juce::Slider volumeSlider;


	std::unique_ptr<juce::FileChooser> fileChooser;
	// Event handlers
	void buttonClicked(Button* button) override;
	void sliderValueChanged(Slider* slider) override;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)
}; 


