/*
  ==============================================================================

    ScaleMidiMap.h
    Created: 20 Feb 2017 12:10:10pm
    Author:  blist

  ==============================================================================
*/

#ifndef SCALEMIDIMAP_H_INCLUDED
#define SCALEMIDIMAP_H_INCLUDED
#include "../JuceLibraryCode/JuceHeader.h"
#include "MidiMap.h"
#include "Scale.h"
#include <math.h>
#include <map>
#include <stdexcept>
#include "MidiUtils.h"
class ScaleMidiMap : public MidiMap {
public:
	ScaleMidiMap();
	ScaleMidiMap(Scale s, int key, bool normalizeOutput);
    ~ScaleMidiMap();
    void setScale(Scale s);
	Scale getScale();
	void setKey(int k);
	int getKey();
    Array<int> map(int index);
	using MidiMap::map;
	int scaleValueAtIndex(int index);
	void setShouldNormalizeTheOutput(bool normalize);

private:
    Scale scale;
	int key;
	std::map<int, int> scaleSizeDegreeOffsetMap;
	bool shouldNormalizeTheOutput;
};



#endif  // SCALEMIDIMAP_H_INCLUDED
