/*
  ==============================================================================

    ScaleMidiMap.cpp
    Created: 20 Feb 2017 12:10:10pm
    Author:  blist

  ==============================================================================
*/

#include "ScaleMidiMap.h"

ScaleMidiMap::ScaleMidiMap()
{

}
ScaleMidiMap::ScaleMidiMap(Scale s, int key)
{
	setScale(s);
	setKey(key);
}
ScaleMidiMap::~ScaleMidiMap()
{

}
void ScaleMidiMap::setScale(Scale s)
{
	scale = s;
}
Scale ScaleMidiMap::getScale()
{
	return scale;
}
void ScaleMidiMap::setKey(int k)
{
	key = k;
}
int ScaleMidiMap::getKey()
{
	return key;
}
Array<int> ScaleMidiMap::map(int note)
{
	piano_key_info keyInfo = MidiUtils::pianoKeyInfo(note);
	return { scaleValueAtIndex(keyInfo.index) };
}

int ScaleMidiMap::scaleValueAtIndex(int index)
{
	return { key + MidiUtils::scaleNoteValueAtIndex(scale, index) };
}