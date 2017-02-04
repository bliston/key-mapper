/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

MiddlePluginAudioProcessorEditor::MiddlePluginAudioProcessorEditor(AudioProcessor& parent, AudioProcessorValueTreeState& vts)
	: AudioProcessorEditor(parent),
	valueTreeState(vts)
{
	scalesLabel.setText("Scales Selection", dontSendNotification);
	addAndMakeVisible(scalesLabel);

	scalesComboBox.addItem("1: Major", 1);
	scalesComboBox.addItem("2: Major Solo", 2);
	scalesComboBox.addItem("3: Minor", 3);
	scalesComboBox.addItem("4: Minor Solo", 4);
	scalesComboBox.addItem("5: Harmonic Minor", 5);
	scalesComboBox.addItem("6: Harmonic Minor Solo", 6);
	scalesComboBox.addItem("7: Major Blues Solo", 7);
	scalesComboBox.addItem("8: Minor Blues Solo", 8);

	addAndMakeVisible(scalesComboBox);
	scalesAttachment = new ComboBoxAttachment(valueTreeState, "scalesId", scalesComboBox);

	keyLabel.setText("Key:", dontSendNotification);
	addAndMakeVisible(keyLabel);

	keyComboBox.addItem("C", 1);
	keyComboBox.addItem("C#", 2);
	keyComboBox.addItem("D", 3);
	keyComboBox.addItem("D#", 4);
	keyComboBox.addItem("E", 5);
	keyComboBox.addItem("F", 6);
	keyComboBox.addItem("F#", 7);
	keyComboBox.addItem("G", 8);
	keyComboBox.addItem("G#", 9);
	keyComboBox.addItem("A", 10);
	keyComboBox.addItem("A#", 11);
	keyComboBox.addItem("B", 12);

	addAndMakeVisible(keyComboBox);
	keyAttachment = new ComboBoxAttachment(valueTreeState, "key", keyComboBox);


	chordOctaveLabel.setText("Chord Octave", dontSendNotification);
	addAndMakeVisible(chordOctaveLabel);

	chordOctaveComboBox.addItem("2", 1);
	chordOctaveComboBox.addItem("3", 2);
	chordOctaveComboBox.addItem("4", 3);

	addAndMakeVisible(chordOctaveComboBox);
	chordOctaveAttachment = new ComboBoxAttachment(valueTreeState, "chordOctave", chordOctaveComboBox);


	chordSizeLabel.setText("Chord Size", dontSendNotification);
	addAndMakeVisible(chordSizeLabel);

	chordSizeComboBox.addItem("3", 1);
	chordSizeComboBox.addItem("4", 2);

	addAndMakeVisible(chordSizeComboBox);
	chordSizeAttachment = new ComboBoxAttachment(valueTreeState, "chordSize", chordSizeComboBox);


	progressionLabel.setText("Progression: ex: 14526", dontSendNotification);
	addAndMakeVisible(progressionLabel);

	progressionInputLabel.setEditable(true);
	progressionInputLabel.setText("14526", dontSendNotification);
	addAndMakeVisible(progressionInputLabel);
	progressionAttachment = new ValueTreeLabelAttachment(valueTreeState.state, &progressionInputLabel, "progressionString");
	setSize(paramComponentWidth + paramLabelWidth, paramControlHeight * 5);
}

MiddlePluginAudioProcessorEditor::~MiddlePluginAudioProcessorEditor()
{
}

//==============================================================================
void MiddlePluginAudioProcessorEditor::resized()
{
	juce::Rectangle<int> r = getLocalBounds();
	const int padding = 10;

	juce::Rectangle<int> scalesRect = r.removeFromTop(paramControlHeight);
	scalesLabel.setBounds(scalesRect.removeFromLeft(paramLabelWidth));
	scalesComboBox.setBounds(scalesRect.reduced(padding));

	juce::Rectangle<int> keyRect = r.removeFromTop(paramControlHeight);
	keyLabel.setBounds(keyRect.removeFromLeft(paramLabelWidth));
	keyComboBox.setBounds(keyRect.reduced(padding));

	juce::Rectangle<int> chordOctaveRect = r.removeFromTop(paramControlHeight);
	chordOctaveLabel.setBounds(chordOctaveRect.removeFromLeft(paramLabelWidth));
	chordOctaveComboBox.setBounds(chordOctaveRect.reduced(padding));

	juce::Rectangle<int> chordSizeRect = r.removeFromTop(paramControlHeight);
	chordSizeLabel.setBounds(chordSizeRect.removeFromLeft(paramLabelWidth));
	chordSizeComboBox.setBounds(chordSizeRect.reduced(padding));

	juce::Rectangle<int> progressionRect = r.removeFromTop(paramControlHeight);
	progressionLabel.setBounds(progressionRect.removeFromLeft(paramLabelWidth));
	progressionInputLabel.setBounds(progressionRect.reduced(padding));

}

void MiddlePluginAudioProcessorEditor::paint(Graphics& g)
{
	g.setColour(Colours::white);
	g.fillRect(getLocalBounds());
}