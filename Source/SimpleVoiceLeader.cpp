/*
==============================================================================

VoiceLeader.cpp
Created: 19 Oct 2016 1:07:21am
Author:  blist

==============================================================================
*/

#include "SimpleVoiceLeader.h"
SimpleVoiceLeader::SimpleVoiceLeader()
{
	setChordReferenceNoteValue(36);
}

SimpleVoiceLeader::SimpleVoiceLeader(int chordReferenceNoteVal)
{
	setChordReferenceNoteValue(chordReferenceNoteVal);
}

SimpleVoiceLeader::~SimpleVoiceLeader()
{

}

void SimpleVoiceLeader::setChordReferenceNoteValue(int val)
{
	chordReferenceNoteValue = val;
}

int SimpleVoiceLeader::getChordReferenceNoteValue()
{
	return chordReferenceNoteValue;
}

int SimpleVoiceLeader::fitNote(int note)
{
	return chordReferenceNoteValue + note % 12 - chordReferenceNoteValue % 12;
}

vector<int> SimpleVoiceLeader::lead(vector<int> to)
{
	vector<int> result;
	for (int n : to) {
		result.push_back(fitNote(n));
	}
	return result;
}

pair<vector<int>, vector<int>> SimpleVoiceLeader::leadInto(vector<int> to, bool isNoteOn, bool release)
{
	pair<vector<int>, vector<int>> result;
	vector<int> lead_result = lead(to);
	if (isNoteOn) {
		if (!last.second.empty()) {//noteOn last noteOns not empty
			result.first = last.second;//turn off last noteOns
			result.second = lead_result;
		}
		else {//1. noteOn last noteOns is empty case
			result.first = {};//offs
			result.second = to;//ons
		}
		last = result;
	}
	else {
		result.first = {};
		if (release) {
			result.first = last.second;
			result.second = {};
		}
		else {
			result.first = {};
			result.second = {};
		}
	}
	return result;
}