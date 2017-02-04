#include "../JuceLibraryCode/JuceHeader.h"
#include <iostream>      // for cout and cin
#include <math.h>
#include <vector>
#include <map>
#include <stdexcept>
#include "VoiceLeader.h"
#include "SimpleVoiceLeader.h"
#include <sstream>

using namespace std;

struct piano_key_info {
	bool isBlack;
	int index;
};

struct scaleItem {
	string name;
	vector<int> pitch_set;
};

struct presetItem {
	string name;
	int blackId;
	int whiteId;
};

class MiddleCore                   // begin declaration of the class
{
public:                  // begin public section
	vector<int>  WHITE_INDICES;
	vector<int> BLACK_INDICES;
	MiddleCore();     // constructor
	~MiddleCore();                  // destructor
	void initScales();
	void initPresets();
	void updatePreset(int id);
	void updateProgression(vector<int> p);
	void updateKey(int k);
	void updateChordOctave(int oct);
	void updateChordSize(int size);
	void updateBlackAnchorIndex(int blackNoteValue);
	vector<int> addAmountToVectorValues(vector<int> values, int amount);
	void printVector(vector<int> vec);
	int indexOf(vector<int> vec, int val);
	int scaleNoteValueAtIndex(vector<int> scale, int index);
	int scaleIndexOfNoteValue(vector<int> scale, int val);
	bool isBlack(int val);
	piano_key_info pianoKeyInfo(int val);
	int getChordReferenceNoteValue();
	vector<int> chord(int size, vector<int> scale, int degree);
	int posMod(int m, int n);
	pair<vector<int>, vector<int>> get(int val, bool isNoteOn);


private:
	int key;
	int chordOctave;
	int chordSize;
	string progressionId;
	int blackAnchorIndex;
	int lastBlackIndex = -1;
	vector<int> blackScaleVec;
	vector<int> whiteScaleVec;
	map<int, scaleItem> scales;
	map<int, presetItem> presets;
	SimpleVoiceLeader vl;
	vector<int> progression;
	vector<vector<int>> progressions;
};
