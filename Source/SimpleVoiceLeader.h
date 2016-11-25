#include <iostream>
#include <algorithm>
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
	vector<int> leadInto(vector<int> to);

private:
	int chordReferenceNoteValue;
	vector<int> from; //the chord to lead from
};
