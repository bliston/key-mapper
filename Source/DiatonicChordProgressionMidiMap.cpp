/*
  ==============================================================================

    DiatonicChordProgressionMidiMap.cpp
    Created: 19 Feb 2017 2:28:41pm
    Author:  blist

  ==============================================================================
*/

#include "DiatonicChordProgressionMidiMap.h"

DiatonicChordProgressionMidiMap::DiatonicChordProgressionMidiMap()
{
	key = 4;
	chordOctave = 4;
	chordSize = 4;
	chordAnchorIndex = 0;
	scaleMidiMap.setScale(MidiUtils::WHITE_INDICES);
	progression = { 1,2,3,5,4 };
}

DiatonicChordProgressionMidiMap::~DiatonicChordProgressionMidiMap()
{
}

void DiatonicChordProgressionMidiMap::setProgression(Array<int> _progression)
{
	progression = _progression;
}

Array<int> DiatonicChordProgressionMidiMap::getProgression()
{
	return progression;
}

void DiatonicChordProgressionMidiMap::setScale(Scale s)
{
	scaleMidiMap.setScale(s);
}

Array<int> DiatonicChordProgressionMidiMap::map(int note)
{
	piano_key_info keyInfo = MidiUtils::pianoKeyInfo(note);
	int blackKeyIndexPosMod = MidiUtils::posMod(keyInfo.index, progression.size());
	int blackAnchorIndexPosMod = MidiUtils::posMod(chordAnchorIndex, progression.size());
	int modChordIndex = MidiUtils::posMod(blackKeyIndexPosMod - blackAnchorIndexPosMod, progression.size());
	Chord chord = getChord(progression[modChordIndex]);
	return chord;
}

Chord DiatonicChordProgressionMidiMap::getChord(int degree)
{
	int index = degree - 1;
	int one = scaleMidiMap.scaleValueAtIndex(index);
	index += 2;
	int three = scaleMidiMap.scaleValueAtIndex(index);
	index += 2;
	int five = scaleMidiMap.scaleValueAtIndex(index);
	index += 2;
	int seven = scaleMidiMap.scaleValueAtIndex(index);
	Chord triad = { one, three, five };
	Chord seventh = { one, three, five, seven };

	return chordSize == 3 ? triad : seventh;
}

void DiatonicChordProgressionMidiMap::setKey(int k)
{
	key = k;
	scaleMidiMap.setKey(getChordReferenceNoteValue());
}

void DiatonicChordProgressionMidiMap::setChordOctave(int oct)
{
	chordOctave = oct;
}

void DiatonicChordProgressionMidiMap::setChordSize(int size)
{
	chordSize = size;
}

void DiatonicChordProgressionMidiMap::setChordAnchorIndex(int blackNoteValue)
{
	piano_key_info pianoKey = MidiUtils::pianoKeyInfo(blackNoteValue);
	chordAnchorIndex = pianoKey.index;

}

int DiatonicChordProgressionMidiMap::getChordReferenceNoteValue()
{
	return key + 12 * (chordOctave + 1);
}