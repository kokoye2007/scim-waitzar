/*
 * Copyright 2008 by Seth N. Hetu
 *
 * Please refer to the end of the file for licensing information
 */

#ifndef _SENTENCELIST
#define _SENTENCELIST

//Necessary libraries
#include <wchar.h>
#include <string.h>
#include <stdio.h>
#include <list>
#include "WordBuilder.h"



/**
 * Intended to encapsulate the cursor & the list of possible words into a single class,
 *   and to fix the reverse-insertion error at the same time.
 */
class SentenceList
{
public:
	//Constructor/destructor
	SentenceList();
	~SentenceList();

	//Extracted interface
	void clear();
	void insert(int val);
	int getCursorIndex();
	bool moveCursorRight(int amt, bool allowSameIndex, WordBuilder *model);
	bool moveCursorRight(int amt, WordBuilder *model);
	size_t size();
	bool deleteNext();
	bool deletePrev(WordBuilder *model);

	//Iterating
	std::list<int>::iterator begin();
	std::list<int>::iterator end();


private:
	//Main wrapped variables
	int cursorIndex;
	std::list<int> prevTypedWords;
	std::list<int>::iterator cursor;

	//Helper
	std::list<int>::iterator newCursor;

	//Helper methods
	void updateTrigrams(WordBuilder *model);
};

#endif //_SENTENCELIST



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

