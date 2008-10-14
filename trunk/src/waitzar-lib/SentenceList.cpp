/*
 * Copyright 2008 by Seth N. Hetu
 *
 * Please refer to the end of the file for licensing information
 */

#include "SentenceList.h"



SentenceList::SentenceList ()
{
	this->clear();
}

SentenceList::~SentenceList()
{
}


void SentenceList::clear()
{
	prevTypedWords.clear();
	cursor = prevTypedWords.begin();
	cursorIndex = -1;
}

void SentenceList::insert(int val)
{
	prevTypedWords.insert(cursor, val);
	cursorIndex++;
}

int SentenceList::getCursorIndex()
{
	return cursorIndex;
}

size_t SentenceList::size()
{
	return prevTypedWords.size();
}

bool SentenceList::moveCursorRight(int amt, bool allowSameIndex, WordBuilder *model)
{
	//Any words?
	if (prevTypedWords.size()==0)
		return false;

	//Are we in bounds?
	int newCursorIndex = cursorIndex + amt;
	newCursor = cursor;
	while (amt!=0) {
		if (amt>0 && newCursor!=prevTypedWords.end()) {
			newCursor++;
			amt--;
		} else if (amt<0 && newCursor!=prevTypedWords.begin()) {
			newCursor--;
			amt++;
		} else {
			//Ignore this update
			return false;
		}
	}

	//Did we make any change?
	if (newCursor==cursor && !allowSameIndex)
		return false;

	//Update our model
	cursor = newCursor;
	cursorIndex = newCursorIndex;

	//Set the trigram
	this->updateTrigrams(model);
	
	//Success indicator
	return true;
}

bool SentenceList::moveCursorRight(int amt, WordBuilder *model)
{
	return this->moveCursorRight(amt, false, model);
}


bool SentenceList::deleteNext()
{
	//No words?
	if (prevTypedWords.size()==0)
		return false;

	//At end?
	if (cursor == prevTypedWords.end())
		return false;

	//Ok, delete it. No need to advance the cursor
	cursor = prevTypedWords.erase(cursor);
	return true;
}


bool SentenceList::deletePrev(WordBuilder *model)
{
	//No words?
	if (prevTypedWords.size()==0) 
		return false;

	//At beginning?
	if (cursor == prevTypedWords.begin())
		return false;

	//Ok, delete it, update the cursor.
	cursor--;
	cursorIndex--;
	cursor = prevTypedWords.erase(cursor);

	//Update the trigrams...
	this->updateTrigrams(model);
	return true;
}



void SentenceList::updateTrigrams(WordBuilder *model)
{
	unsigned short trigram[3];
	int trigram_count = 0;
	std::list<int>::iterator considered = cursor;
	while (considered!=prevTypedWords.begin() && trigram_count<3) {
		considered--;
		trigram[trigram_count++] = *considered;
	}
	model->insertTrigram(trigram, trigram_count);
}




//Iterate
std::list<int>::iterator SentenceList::begin()
{
	return prevTypedWords.begin();
}
std::list<int>::iterator SentenceList::end()
{
	return prevTypedWords.end();
}





/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
