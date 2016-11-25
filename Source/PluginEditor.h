/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class MiddlePluginAudioProcessorEditor  : public AudioProcessorEditor
{
public:
	enum
	{
		paramControlHeight = 40,
		paramLabelWidth = 80,
		paramComponentWidth = 300
	};

	typedef AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;
	typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
	MiddlePluginAudioProcessorEditor(AudioProcessor& parent, AudioProcessorValueTreeState& vts);
    ~MiddlePluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
	void setProgression(int prog);
	int getProgression(int prog);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

	AudioProcessorValueTreeState& valueTreeState;

	Label scalesLabel;
	ComboBox scalesComboBox;
	ScopedPointer<ComboBoxAttachment> scalesAttachment;

	Label keyLabel;
	ComboBox keyComboBox;
	ScopedPointer<ComboBoxAttachment> keyAttachment;

	Label chordOctaveLabel;
	ComboBox chordOctaveComboBox;
	ScopedPointer<ComboBoxAttachment> chordOctaveAttachment;

	Label chordSizeLabel;
	ComboBox chordSizeComboBox;
	ScopedPointer<ComboBoxAttachment> chordSizeAttachment;

	Label progressionLabel;
	Slider progressionSlider;
	ScopedPointer<SliderAttachment> progressionAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MiddlePluginAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
