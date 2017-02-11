/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <string>
#include <limits>
//==============================================================================

MiddlePluginAudioProcessor::MiddlePluginAudioProcessor() 
	: parameters(*this, nullptr)
{
	mc = MiddleCore();
	whiteNotesChannel = 1;
	blackNotesChannel = 2;

	parameters.createAndAddParameter("scalesId",       // parameterID
		"Scales Selection",       // parameter name
		String(),     // parameter label (suffix)
		NormalisableRange<float>(0.0f, 100.0f),    // range
		0.0f,         // default value
		nullptr,
		nullptr);

	parameters.createAndAddParameter("key",       // parameterID
		"Key",       // parameter name
		String(),     // parameter label (suffix)
		NormalisableRange<float>(0.0f, 100.0f),    // range
		0.0f,         // default value
		nullptr,
		nullptr);

	parameters.createAndAddParameter("chordOctave",       // parameterID
		"Chord Octave",       // parameter name
		String(),     // parameter label (suffix)
		NormalisableRange<float>(0.0f, 100.0f),    // range
		0.0f,         // default value
		nullptr,
		nullptr);

	parameters.createAndAddParameter("chordSize",       // parameterID
		"Chord Size",       // parameter name
		String(),     // parameter label (suffix)
		NormalisableRange<float>(0.0f, 100.0f),    // range
		0.0f,         // default value
		nullptr,
		nullptr);

	//parameters.createAndAddParameter("progression",       // parameterID
	//	"Progression",       // parameter name
	//	String(),     // parameter label (suffix)
	//	NormalisableRange<float>(1.0f, FLT_MAX, 1.0f),    // range
	//	(float) 1451,         // default value
	//	nullptr,
	//	nullptr);

	parameters.state = ValueTree(Identifier("MiddlePlugin"));
	parameters.state.setProperty("progressionString", "54236", nullptr);
}

MiddlePluginAudioProcessor::~MiddlePluginAudioProcessor()
{
}

//==============================================================================

const String MiddlePluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MiddlePluginAudioProcessor::acceptsMidi() const
{
    return true;
}

bool MiddlePluginAudioProcessor::producesMidi() const
{
    return true;
}

bool MiddlePluginAudioProcessor::isMidiEffect() const
{
    return true;
}

double MiddlePluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MiddlePluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MiddlePluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MiddlePluginAudioProcessor::setCurrentProgram (int index)
{
}

const String MiddlePluginAudioProcessor::getProgramName (int index)
{
    return String();
}

void MiddlePluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MiddlePluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MiddlePluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MiddlePluginAudioProcessor::setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet)
{
    // Reject any bus arrangements that are not compatible with your plugin

    const int numChannels = preferredSet.size();

   #if JucePlugin_IsMidiEffect
    if (numChannels != 0)
        return false;
   #elif JucePlugin_IsSynth
    if (isInput || (numChannels != 1 && numChannels != 2))
        return false;
   #else
    if (numChannels != 1 && numChannels != 2)
        return false;

    if (! setPreferredBusArrangement (! isInput, bus, preferredSet))
        return false;
   #endif

    return setPreferredBusArrangement (isInput, bus, preferredSet);
}
#endif

MidiBuffer MiddlePluginAudioProcessor::allBlackNotesOff(const int time)
{
	MidiBuffer events;
	for (int n = 0; n < 128; n++) {
		MidiMessage mm = MidiMessage::noteOff(blackNotesChannel, n);
		events.addEvent(mm, time);
	}
	return events;
}

MidiBuffer MiddlePluginAudioProcessor::mappedEvents(MidiMessage m, const int time)
{
	MidiBuffer events;
	bool isBlack = mc.isBlack(m.getNoteNumber());
	pair<vector<int>, vector<int>> notes;
	int channel = whiteNotesChannel;
	{// white scale notes
		if (m.isNoteOff()) {
			notes = mc.get(m.getNoteNumber(), false);
			if (isBlack) {
				channel = blackNotesChannel;
				blackNotesOn.clear();
			}
		}
		else if (m.isNoteOn()) {
			notes = mc.get(m.getNoteNumber(), true);
			if (isBlack) {
				channel = blackNotesChannel;
				blackNotesOn.push_back(m.getNoteNumber());
				if (blackNotesOn.size() > 2) {
					int minBlack = *std::min_element(blackNotesOn.begin(), blackNotesOn.end());
					mc.updateBlackAnchorIndex(minBlack);
					return allBlackNotesOff(time);
				}
			}
		}
		for (int n : notes.first) {
			MidiMessage mm = MidiMessage::noteOff(channel, n);
			events.addEvent(mm, time);
		}
		for (int n : notes.second) {
			MidiMessage mm = MidiMessage::noteOn(channel, n, m.getVelocity());
			events.addEvent(mm, time);
		}
		return events;
	}
}

void MiddlePluginAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	int scalesId = *parameters.getRawParameterValue("scalesId");
	int key = *parameters.getRawParameterValue("key");
	int chordOctave = *parameters.getRawParameterValue("chordOctave");
	int chordSize = *parameters.getRawParameterValue("chordSize");
	vector<int> progression = { 1,2,3,4,5,6,7 };
	if (parameters.state.hasProperty("progressionString"))
	{
		progression = decodeProperty(parameters.state.getProperty("progressionString").toString());
	}
	mc.updatePreset(scalesId + 1);
	mc.updateKey(key);
	mc.updateChordOctave(chordOctave + 3);
	mc.updateChordSize(chordSize + 3);
	mc.updateProgression(progression);
	buffer.clear();

	MidiBuffer processedMidi;
	int time;
	MidiMessage m;

	for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);)
	{
		MidiBuffer mEvents = mappedEvents(m, time);
		int mtime;
		MidiMessage mm;
		for (MidiBuffer::Iterator i(mEvents); i.getNextEvent(mm, mtime);)
		{
			processedMidi.addEvent(mm, mtime);
		}
	}

	midiMessages.swapWith(processedMidi);
}

//==============================================================================
bool MiddlePluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MiddlePluginAudioProcessor::createEditor()
{
    return new MiddlePluginAudioProcessorEditor(*this, parameters);
}

//==============================================================================
void MiddlePluginAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	ScopedPointer<XmlElement> xml(parameters.state.createXml());
	copyXmlToBinary(*xml, destData);
}

void MiddlePluginAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState != nullptr)
		if (xmlState->hasTagName(parameters.state.getType()))
			parameters.state = ValueTree::fromXml(*xmlState);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MiddlePluginAudioProcessor();
}

vector<int> MiddlePluginAudioProcessor::decodeProperty(String input)
{
	StringArray tokens;
	tokens.addTokens(input, " ", "");
	return stringToVectorOfDigits(tokens.joinIntoString("").toStdString());
}

vector<int> MiddlePluginAudioProcessor::stringToVectorOfDigits(string id)
{
	vector<int> digits;
	string::iterator it;
	for (it = id.begin(); it != id.end(); it++)
	{
		int d = *it;
		digits.push_back(d + 1);
	}
	return digits;
}