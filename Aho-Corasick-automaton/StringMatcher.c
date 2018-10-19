#include "StringMatcher.h"
#include "malloc.h"

void matchString(StringMatcher * this,char * str, char * pat, char * output)
{
	char *ptn;
	if (!openPatFile(this->io_, pat)) {
		printf("Failed to open %s\n", pat);
		return;
	}
	
	if (!openStrFile(this->io_, str)) {
		printf("Failed to open %s\n", str);
		return;

	}
	while ((ptn = getPattern(this->io_)) != NULL) {
		insertKeywordACA(this->aca_, ptn);
	}
	return;//delete!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void _constructStringMatcher(StringMatcher * this)
{
	this->aca_ = (ACAutomaton *)malloc(sizeof(ACAutomaton));
	_constructACA(this->aca_);
	this->io_ = (IOManager *)malloc(sizeof(IOManager));
	_constructIO(this->io_);
}


void _deconstructStringMatcher(StringMatcher *this)
{
	if (this->aca_ != NULL) {
		_deconstructACA(this->aca_);
		free(this->aca_);
	}
	if (this->io_ != NULL) { 
		_deconstructIO(this->io_);
		free(this->io_); 
	}
}
