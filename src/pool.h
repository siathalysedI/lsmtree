#ifndef _POOL_H
#define _POOL_H

#include <stdlib.h>

struct pool{
	struct pool *next;
	char *ptr;
};

struct pool *pool_new(size_t size);

void *pool_alloc(struct pool *p,size_t size);

void pool_destory(struct pool *p);

#endif