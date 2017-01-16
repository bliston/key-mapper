#include <iostream>
#include <algorithm>
#include <iterator> 
#include <math.h>
#include <vector>
#include <map>
#include <stdexcept>
using namespace std;

class SimpleVoiceLeader
{
public:
	SimpleVoiceLeader();
	SimpleVoiceLeader(int chordReferenceNoteValue);
	~SimpleVoiceLeader();
	void setChordReferenceNoteValue(int val);
	int getChordReferenceNoteValue();
	int fitNote(int note);
	vector<int> lead(vector<int> to);
	pair<vector<int>, vector<int>> leadInto(vector<int> to, bool isNoteOn, bool release);

private:
	int chordReferenceNoteValue;
	pair<vector<int>, vector<int>> last;
};
