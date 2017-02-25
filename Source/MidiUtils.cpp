/*
  ==============================================================================

    PianoKeyInfo.cpp
    Created: 20 Feb 2017 3:28:45pm
    Author:  blist

  ==============================================================================
*/

#include "MidiUtils.h"
const Scale MidiUtils::WHITE_INDICES = { 0, 2, 4, 5, 7, 9, 11 };
const Scale MidiUtils::BLACK_INDICES = { 1, 3, 6, 8, 10 };
piano_key_info MidiUtils::pianoKeyInfo(int val)
{
	bool black = MidiUtils::isBlack(val);
	Scale scale;
	scale = black ? MidiUtils::BLACK_INDICES : MidiUtils::WHITE_INDICES;
	int index = MidiUtils::scaleIndexOfNoteValue(scale, val);
	piano_key_info result;
	result.isBlack = black;
	result.index = index;
	return result;
}
int MidiUtils::posMod(int m, int n)
{
	return (m % n + n) % n;
}
bool MidiUtils::isBlack(int val)
{
	bool result;
	switch (val % 12) {
	case 1:
	case 3:
	case 6:
	case 8:
	case 10: {
		result = true;
	}
			 break;
	default: {
		result = false;
	}
	}
	return result;
}
int MidiUtils::scaleNoteValueAtIndex(Scale scale, int index)
{
	int n = scale.size();
	int i = index;
	int posResult = 12 * floor(i / n) + scale[i % n];
	int negResult = 12 * ceil((i + 1) / n - 1) + scale[posMod(i, n)];
	int result = i >= 0 ? posResult : negResult;
	return result;
}
int MidiUtils::scaleIndexOfNoteValue(Array<int> scale, int val)
{
	int modIndex = indexOf(scale, val % 12);
	int numLoops = floor(val / 12);
	int result = numLoops * scale.size() + modIndex;
	return result;
}

int MidiUtils::indexOf(Array<int> vec, int val)
{
	auto it = find(vec.begin(), vec.end(), val);
	if (it == vec.end()) return -1;
	return distance(vec.begin(), it);

}