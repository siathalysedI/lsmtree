#ifndef _SKIPLIST_H
#define _SKIPLIST_H

#define MAXLEVEL (15)
#define KEYSIZE (20)

typedef enum {ADD,DEL} OPT;

struct skipnode{
    char key[KEYSIZE];
	size_t offset;
	OPT opt;                   
    struct skipnode *forward[1]; 
	struct skipnode *next;
};

struct skiplist{
	struct  skipnode *hdr;                 
	size_t count;
	size_t size;
	int level; 
	char pool_embedded[1024];
	struct pool *pool;
};

struct skiplist *skiplist_new(size_t size);
void skiplist_init(struct skiplist *list);
int skiplist_insert(struct skiplist *list,char *data,size_t offset,OPT opt);
void skiplist_dump(struct skiplist *list);
void skiplist_free(struct skiplist *list);


#endif
