 /* Copyright (c) 2011, BohuTANG <overred.shuttler at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of lsmtree nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mtable.h"


struct mtable *mtable_new(int size)
{
	struct mtable *tbl=malloc(sizeof(struct mtable));

	tbl->seq=0;
	tbl->argc=0;
	tbl->active=1;
	tbl->size=size;
	tbl->items=malloc(tbl->size*sizeof(struct mtable_item));
	if(tbl->items==NULL){
		free(tbl);
		return NULL;
	}

	return tbl;
}

int mtable_notfull(struct mtable *tbl)
{
	if(tbl->argc<tbl->size)
		return 1;
	return 0;
}

static int __add(struct mtable *tbl,char *k,size_t offset,OPT opt)
{
	size_t left = 0, right = tbl->argc;

	if(tbl->argc>tbl->size-1)
		return 0;

	while (left < right) {
		size_t i = (left + right) / 2;
		int cmp = strcmp(k, tbl->items[i].key);
		if (cmp == 0) {
			if(opt==ADD){
				tbl->items[i].mark=0;
				tbl->items[i].offset=offset;
			}
			else
				tbl->items[i].mark=1;

			return 1;
		}
		if (cmp < 0)
			right = i;
		else
			left = i + 1;
	}
	size_t i = left;

	if(opt==ADD){
		tbl->argc++;
		memmove(&tbl->items[i + 1], &tbl->items[i],(tbl->argc - i) * sizeof(struct mtable_item));
		memcpy(&tbl->items[i].key,k,KEYSIZE);
		tbl->items[i].offset=offset;
	}

	return 1;
}

int mtable_add(struct mtable *tbl,char *k,size_t offset)
{
	return __add(tbl,k,offset,ADD);
}

int mtable_remove(struct mtable *tbl,char *k)
{
	return __add(tbl,k,0,DEL);
}

void mtable_dump(struct mtable *tbl)
{
	int i;

	printf("--mtable dump:argc<%d>,maxsize<%d>\n",tbl->argc,tbl->size);
	for(i=0;i<tbl->argc;i++)
		printf("	[%d] k:<%s>,v:<%d>,MARK:%s\n",i,
				tbl->items[i].key,
				tbl->items[i].offset,
				tbl->items[i].mark==0?"ADD":"DEL");

}

void mtable_free(struct mtable *tbl)
{
	free(tbl->items);
	free(tbl);
}
