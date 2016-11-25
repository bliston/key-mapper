/*
  ==============================================================================

    MiddleCore.cpp
    Created: 19 Oct 2016 1:07:03am
    Author:  blist

  ==============================================================================
*/

#include "MiddleCore.h"
// constructor of MiddleCore,
MiddleCore::MiddleCore()
{

	key = 4;
	chordOctave = 4;
	chordSize = 4;
	progressionId = 1;
	blackAnchorIndex = 0;
	WHITE_INDICES = { 0, 2, 4, 5, 7, 9, 11 };
	BLACK_INDICES = { 1, 3, 6, 8, 10 };
	blackScaleVec = { 0, 2, 4, 5, 7, 9, 11 };
	whiteScaleVec = { 0, 2, 4, 7, 9 };
	initScales();
	initPresets();
	updatePreset(1);
	vl = SimpleVoiceLeader(getChordReferenceNoteValue());
	progressions = { { 1, 4, 5, 1 }, {1, 5, 6, 4}, {1, 6, 4, 5}, {1, 4, 6, 5}, {1, 5, 4, 5} };
	
	
}

MiddleCore::~MiddleCore()                 // destructor, just an example
{

}

// definition of methods

void MiddleCore::initScales()
{
	scales[321] = { "Iwato Japan",{ 0, 1, 5, 6, 10 } };
	scales[323] = { "Japanese",{ 0, 1, 5, 7, 8 } };
	scales[371] = { "Hirajoshi Japan",{ 0, 2, 3, 7, 8 } };
	scales[393] = { "Major Pentatonic",{ 0, 2, 4, 7, 9 } };
	scales[400] = { "Unknown",{ 0, 2, 4, 9, 11 } };
	scales[408] = { "Ritusen Japan",{ 0, 2, 5, 7, 9 } };
	scales[465] = { "Minor Blues Pentatonic",{ 0, 3, 5, 7, 10 } };
	scales[673] = { "Raga Simantini",{ 0, 1, 3, 5, 7, 8 } };
	scales[785] = { "Major Blues",{ 0, 2, 3, 4, 7, 9 } };
	scales[823] = { "Hawaiian",{ 0, 2, 3, 7, 9, 11 } };
	scales[936] = { "Minor Blues",{ 0, 3, 5, 6, 7, 10 } };
	scales[1191] = { "Locrian",{ 0, 1, 3, 5, 6, 8, 10 } };
	scales[1193] = { "Locrian Natural Maj 6",{ 0, 1, 3, 5, 6, 9, 10 } };
	scales[1197] = { "Phryigian",{ 0, 1, 3, 5, 7, 8, 10 } };
	scales[1232] = { "Phrygian Dominant",{ 0, 1, 4, 5, 7, 8, 10 } };
	scales[1323] = { "Minor",{ 0, 2, 3, 5, 7, 8, 10 } };
	scales[1324] = { "Harmonic Minor",{ 0, 2, 3, 5, 7, 8, 11 } };
	scales[1326] = { "Melodic Minor",{ 0, 2, 3, 5, 7, 9, 11 } };
	scales[1361] = { "Major",{ 0, 2, 4, 5, 7, 9, 11 } };
	scales[1364] = { "Harmonic Major",{ 0, 2, 4, 5, 8, 9, 11 } };
}

void MiddleCore::initPresets()
{

	presets[1] = { "Major", 1361, 1361 };
	presets[2] = { "Major Solo 1", 1361, 393 };
	presets[3] = { "Minor", 1323, 1323 };
	presets[4] = { "Minor Solo 1", 1323, 465 };
	presets[5] = { "Harmonic Minor", 1324, 1324 };
	presets[6] = { "Harmonic Minor Solo 1", 1324, 371 };
	presets[7] = { "Major Blues Solo 1", 1361, 785 };
	presets[8] = { "Minor Blues Solo 1", 1323, 936 };
}

void MiddleCore::updatePreset(int id)
{
	if (!presets.count(id)) {
		return;
	}
	presetItem selPreset = presets.at(id);
	blackScaleVec = addAmountToVectorValues(scales.at(selPreset.blackId).pitch_set, getChordReferenceNoteValue());
	whiteScaleVec = addAmountToVectorValues(scales.at(selPreset.whiteId).pitch_set, key);
}

void MiddleCore::updateProgression(int id)
{
	progressionId = id;
}

void MiddleCore::updateKey(int k)
{
	key = k;
}

void MiddleCore::updateChordOctave(int oct)
{
	chordOctave = oct;
}

void MiddleCore::updateChordSize(int size)
{
	chordSize = size;
}

void MiddleCore::updateBlackAnchorIndex(int blackNoteValue)
{
	piano_key_info pianoKey = pianoKeyInfo(blackNoteValue);
	blackAnchorIndex = pianoKey.index;

}

vector<int> MiddleCore::addAmountToVectorValues(vector<int> values, int amount)
{
	vector<int> result;
	for (int v : values) {
		result.push_back(v + amount);
	}
	return result;
}

void MiddleCore::printVector(vector<int> vec)
{
	for (int v : vec)
		cout << v << ' ';
	cout << '\n';
}

int MiddleCore::indexOf(vector<int> vec, int val)
{
	auto it = find(vec.begin(), vec.end(), val);
	if (it == vec.end()) return -1;
	return distance(vec.begin(), it);

}

int MiddleCore::scaleNoteValueAtIndex(vector<int> scale, int index)
{
	int n = scale.size();
	int i = index;
	int posResult = 12 * floor(i / n) + scale[i % n];
	int negResult = 12 * ceil((i + 1) / n - 1) + scale[posMod(i, n)];
	int result = i >= 0 ? posResult : negResult;
	cout << "scaleNoteValAtIndex " << result << endl;
	return result;
}

int MiddleCore::scaleIndexOfNoteValue(vector<int> scale, int val)
{
	int modIndex = indexOf(scale, val % 12);
	int numLoops = floor(val / 12);
	int result = numLoops * scale.size() + modIndex;
	cout << "scaleIndexOfNoteVal " << result << endl;
	return result;
}

bool MiddleCore::isBlack(int val)
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

piano_key_info MiddleCore::pianoKeyInfo(int val)
{
	bool black = isBlack(val);
	vector<int> scale;
	scale = black ? BLACK_INDICES : WHITE_INDICES;
	int index = scaleIndexOfNoteValue(scale, val);
	piano_key_info result;
	result.isBlack = black;
	result.index = index;
	cout << "pianoKeyInfo " << result.isBlack << " " << result.index << endl;
	return result;
}

int MiddleCore::getChordReferenceNoteValue()
{
	return key + 12 * (chordOctave + 1);
}

vector<int> MiddleCore::chord(int size, vector<int> scale, int degree)
{
	int one = scaleNoteValueAtIndex(scale, degree - 1);
	int three = scaleNoteValueAtIndex(scale, degree - 1 + 2);
	int five = scaleNoteValueAtIndex(scale, degree - 1 + 4);
	int seven = scaleNoteValueAtIndex(scale, degree - 1 + 6);
	vector<int> triad = { one, three, five };
	vector<int> seventh = { one, three, five, seven };

	return size == 3 ? triad : seventh;
}

int MiddleCore::posMod(int m, int n)
{
	return (m % n + n) % n;
}

vector<int> MiddleCore::integerToVectorOfDigits(int id)
{
	vector<int> digits;

	while (id)
	{
		int d = id % 10;
		if (d != 0)
			digits.push_back(d);

		id /= 10;
	}

	std::reverse(digits.begin(), digits.end());
	return digits;
}

vector<int> MiddleCore::get(int val)
{
	vl.setChordReferenceNoteValue(getChordReferenceNoteValue());
	vector<int> result;
	piano_key_info keyInfo = pianoKeyInfo(val);
	if (keyInfo.isBlack) {
		vector<int> progression = integerToVectorOfDigits(progressionId);
		int blackKeyIndexPosMod = posMod(keyInfo.index, progression.size());
		int blackAnchorIndexPosMod = posMod(blackAnchorIndex, progression.size());
		result = vl.leadInto(chord(chordSize, blackScaleVec, progression[posMod(blackKeyIndexPosMod - blackAnchorIndexPosMod, progression.size())]));
	}
	else {
		result = { scaleNoteValueAtIndex(whiteScaleVec, keyInfo.index) };
	}
	return result;
}