#ifndef _INDEX_H
#define _INDEX_H

#include "mtable.h"

struct index{
	int lsn;
	int fd;

	char *idx_name;

	struct mtable *mtbls;
};

struct index *index_new(char *name);
int index_add(struct index *idx,void *k,void *v);
void *index_get(struct index *idx,void *k);
void index_remove(struct index *idx,void *k);
void index_free(struct index *idx);

#endif
