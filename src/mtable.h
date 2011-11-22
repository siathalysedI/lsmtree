#ifndef _MTABLE_H
#define _MTABLE_H

#define KEYSIZE (64)

#include <stdint.h>

typedef enum {ADD,DEL}OPT;

struct mtable_item{
	char key[KEYSIZE];
	size_t offset;
	uint8_t mark;
};

struct mtable{
	int seq;
	int argc;
	int active;
	int size;
	struct mtable_item *items;
};


struct mtable *mtable_new(int max_size);
int mtable_notfull(struct mtable *tbl);
int	mtable_add(struct mtable *tbl,char *k,size_t offset);
int mtable_remove(struct mtable *tbl,char *k);
void mtable_dump(struct mtable *tbl);
void mtable_free(struct mtable *tbl);

#endif
