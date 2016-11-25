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

vector<int> SimpleVoiceLeader::leadInto(vector<int> to)
{
	vector<int> result;
	for (int n : to) {
		result.push_back(fitNote(n));
	}
	return result;
}