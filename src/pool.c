#include "pool.h"

struct pool *pool_new(size_t size)
{
	struct pool *pool=malloc(sizeof(struct pool));
	pool->next=NULL;
	pool->ptr=malloc(size);
	
	return pool;
}

void *pool_alloc(struct pool *p,size_t size)
{
	struct pool *pool;
	void *ptr;
	
	pool=pool_new(size);
	pool->next=p;
	p=pool;
	ptr=pool->ptr;
	return ptr;
}

void pool_destory(struct pool *p)
{
	struct pool *pool=p;
	while(pool->next!=NULL){
		struct pool *next=pool->next;
		free(pool->ptr);
		free(pool);
		pool=next;
	}
}