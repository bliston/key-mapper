/*
  ==============================================================================

    MidiUtils.h
    Created: 20 Feb 2017 3:28:45pm
    Author:  blist

  ==============================================================================
*/

#ifndef MIDIUTILS_H_INCLUDED
#define MIDIUTILS_H_INCLUDED
#include "../JuceLibraryCode/JuceHeader.h"
#include "Scale.h"
using namespace std;
struct piano_key_info {
	bool isBlack;
	int index;
};

class MidiUtils {
public:
	static const Scale WHITE_INDICES;
	static const Scale BLACK_INDICES;
	static piano_key_info pianoKeyInfo(int val);
	static int posMod(int m, int n);
	static bool isBlack(int val);
	static int scaleIndexOfNoteValue(Array<int> scale, int val);
	static int scaleNoteValueAtIndex(Scale scale, int index);
	static int indexOf(Array<int> vec, int val);
};



#endif  // MIDIUTILS_H_INCLUDED
