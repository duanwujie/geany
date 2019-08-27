/*
*
*   Copyright (c) 2009, Jon Strait
*
*   This source code is released for free distribution under the terms of the
*   GNU General Public License.
*
*   This module contains functions for generating tags for Markdown files.
*/

/*
*   INCLUDE FILES
*/
#include "general.h"	/* must always come first */

#include <ctype.h>
#include <string.h>

#include "parse.h"
#include "read.h"
#include "vstring.h"
#include "routines.h"
#include "entry.h"

/*
*   DATA DEFINITIONS
*/

static kindDefinition MarkdownKinds[] = {
	{ true, 'v', "variable", "sections" }
};

/*
*   FUNCTION DEFINITIONS
*/

/* checks if str is all the same character */
static bool issame(const char *str)
{
	char first = *str;

	while (*(++str))
	{
		if (*str && *str != first)
			return false;
	}
	return true;
}

static void makeMarkdownTag (const vString* const name, bool name_before)
{
	tagEntryInfo e;
	initTagEntry (&e, vStringValue(name), 0);

	if (name_before)
		e.lineNumber--;	/* we want the line before the underline chars */

	makeTagEntry(&e);
}


//dwj

static bool iszhNumber(const unsigned char *line,int begin)
{
	unsigned char b1 =line[begin];
	unsigned char b2 =line[begin+1];
	unsigned char b3 = line[begin+2];
#if 0
	static unsigned zhNumber[13][3]={
		{0xE4,0xB8,0x80}, //1
		{0xE4,0xB8,0x89}, //3
		{0xE4,0xB8,0x83}, //7
		{0xE4,0xBA,0x8C}, //2
		{0xE4,0xBA,0x94}, //5
		{0xE4,0xB9,0x9D}, //9

		{0xE5,0x9B,0x9B}, //4
		{0xE5,0x85,0xAD}, //6
		{0xE5,0x85,0xAB}, //8
		{0xE5,0x8D,0x81}, //10
		{0xE5,0x8D,0x83}, //1000

		{0xE7,0x99,0xBE}, //100
		{0xE9,0x9B,0xB6}, //0
	};
#endif

	if(b1 == 0xE4){//1,3,7,2,5,9
		if(b2 == 0xB8 && (b3 == 0x80 || b3 == 0x89 || b3 == 0x83))
			return true;
		else if(b2 == 0xBA && (b3 == 0x8C || b3 == 0x94))
			return true;
		else if(b2 == 0xB9 && b3 == 0x9D )
			return true;
		return false;
	}
	else if(b1 == 0xE5){//4,6,8,10,1000
		if(b2 == 0x9B && b3 == 0x9B)
			return true;
		else if(b2 == 0x85 && (b2 == 0xAD || b3 == 0xAB))
			return true;
		else if(b2 == 0xBD && (b3 == 0x81 || b3 == 0x83))
			return true;
		return false;
	}
	else if(b1 == 0xE7 && b2 == 0x99 && b3 == 0xBE){
		return true;
	}
	else if(b1 == 0xE9 && b2 == 0x9B && b3 == 0xB6){
		return true;
	}
	return false;
}

static bool isAllzhNumber(const unsigned char * line,int end_offset)
{
	for(int i = 3;i<end_offset;i+=3){
		if(iszhNumber(line,i)){
			return true;
		}
	}
	return false;
}

static bool isStoryChapter(const unsigned char *line)
{
	int i=0;
	int line_len = strlen((const char *)line);
	if(line[0] == 0xe7){
		if(line[1] == 0xac && line[2] == 0xac){
			for(int i=3;i<line_len-3;i++){
				if(line[i] == 0xE7 && line[i+1] == 0xAB && line[i+2] == 0xA0){
					return isAllzhNumber(line,i+3);
					//return true;
				}
			}
			
		}
	}
	return false;
}

static void findMarkdownTags (void)
{
	vString *name = vStringNew();
	const unsigned char *line;

	while ((line = readLineFromInputFile()) != NULL)
	{
		int name_len = vStringLength(name);
		/* underlines must be the same length or more */
		if (name_len > 0 &&	(line[0] == '=' || line[0] == '-') && issame((const char*) line))
		{
			makeMarkdownTag(name, true);
		}
        	else if (isStoryChapter(line)){
            		vStringClear(name);
            		vStringCatS(name, (const char *) line);
            		makeMarkdownTag(name, false);
        	}
	}
	vStringDelete (name);
}

extern parserDefinition* MarkdownParser (void)
{
	static const char *const patterns [] = { "*.md", NULL };
	static const char *const extensions [] = { "md", NULL };
	parserDefinition* const def = parserNew ("Markdown");

	def->kindTable = MarkdownKinds;
	def->kindCount = ARRAY_SIZE (MarkdownKinds);
	def->patterns = patterns;
	def->extensions = extensions;
	def->parser = findMarkdownTags;
	return def;
}

