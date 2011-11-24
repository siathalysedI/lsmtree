#ifndef _INDEX_H
#define _INDEX_H
#include "skiplist.h"
#include "log.h"

#define INDEX_NSIZE (64)

struct index{
	int lsn;
	int max_mtbl;
	int max_mtbl_size;
	char name[INDEX_NSIZE];
	struct skiplist **mtbls;
	struct log *log;
};

struct index *index_new(char *name,int max_mtbls,int max_mtbl_size);
int index_add(struct index *idx,char *k,int klen,void *v,int vlen);
void *index_get(struct index *idx,void *k);
void index_remove(struct index *idx,void *k);
void index_free(struct index *idx);

#endif
