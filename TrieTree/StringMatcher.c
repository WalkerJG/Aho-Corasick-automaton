#include "StringMatcher.h"
#include "malloc.h"
#include "time.h"
#include "stdlib.h"
#pragma warning(disable:4996)
void matchKeywords(StringMatcher * this, char * keywords, char * pat)
{
	clock_t start, end;
	double duration;
	char *ptn;
	if (!openPatFile(this->io_, pat)) {
		printf("Failed to open %s\n", pat);
		return;
	}

	if (!openKeywordFile(this->io_, keywords)) {
		printf("Failed to open %s\n", keywords);
		return;
	}

	start = clock();
	while ((ptn = getPattern(this->io_)) != NULL) {
		insertKeyword(this->trie_, ptn);
	}
	end = clock();
	duration = ((double)end - start) / CLOCKS_PER_SEC;
	printf("建立自动机时间 time=%f seconds\n", duration);

	start = clock();
	char *keyword = NULL;
	while ((keyword = getKeyword(this->io_)) != NULL) {
		matchKeywordAndPattern(this->trie_, keyword);
	}
	end = clock();
	duration = ((double)end - start) / CLOCKS_PER_SEC;
	printf("匹配时间 time=%f seconds\n", duration);
}

int _cmp_key_count(const key_count *a, const key_count *b)
{
	if (a->count > b->count)
		return -1;
	else if (a->count < b->count)
		return 1;
	else
		return 0;
}


void outPutResult(StringMatcher *this, char * file_name)
{
	long total_num = this->trie_->key_num_;
	char **keywords = this->trie_->keyword_;
	long *count = this->trie_->key_count_;
	key_count *index = (key_count *)(malloc(sizeof(key_count)*total_num));

	// Initialize array.
	long i = 0;
	for (i = 0; i < total_num; ++i) {
		index[i].count = count[i];
		index[i].keyId = i;
	}
	qsort(index, total_num, sizeof(key_count), _cmp_key_count);
	//[DICT_SIZE][MAX_WORD_LEGNTH]
	printf("统计结果:\n");
	FILE *file = fopen(file_name, "w");
	if (!file) {
		printf("Failed to open output file");
		return;
	}
	for (i = 0; i < total_num; ++i) {
		printf("%s %d\n", this->trie_->keyword_[index[i].keyId], this->trie_->key_count_[index[i].keyId]);
		fprintf(file, "%s %d\n", this->trie_->keyword_[index[i].keyId], this->trie_->key_count_[index[i].count]);
	}
	fclose(file);
	free(index);
}

void _constructStringMatcher(StringMatcher * this)
{
	this->trie_ = (Trie *)malloc(sizeof(Trie));
	_constructTrie(this->trie_);
	this->io_ = (IOManager *)malloc(sizeof(IOManager));
	_constructIO(this->io_);
}


void _deconstructStringMatcher(StringMatcher *this)
{
	//if (this->trie_ != NULL) {
	//	_deconstructTrie(this->trie_);
	//	free(this->trie_);
	//}
	//if (this->io_ != NULL) {
	//	_deconstructIO(this->io_);
	//	free(this->io_);
	//}
}
