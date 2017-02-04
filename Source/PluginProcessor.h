/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "MiddleCore.h"
#include <vector>

//==============================================================================
/**
*/
class MiddlePluginAudioProcessor  : public AudioProcessor
{
public:
	MiddleCore mc;
    //==============================================================================
    MiddlePluginAudioProcessor();
    ~MiddlePluginAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet);
   #endif
	MidiBuffer allBlackNotesOff(const int time);
	MidiBuffer mappedEvents(MidiMessage m, const int time);
    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
	void getStateInformation(MemoryBlock& destData) override;
	void setStateInformation(const void* data, int sizeInBytes) override;

private:
    //==============================================================================
	AudioProcessorValueTreeState parameters;
	vector<int> blackNotesOn;
	int whiteNotesChannel;
	int blackNotesChannel;
	vector<int> stringToVectorOfDigits(string id);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MiddlePluginAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
