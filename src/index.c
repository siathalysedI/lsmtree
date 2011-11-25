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

#include "index.h"
#include "skiplist.h"
#include "log.h"
#include "debug.h"

#include "platform.h"


struct index *index_new(char *name,int max_mtbl,int max_mtbl_size)
{
	struct index *idx=malloc(sizeof(struct index));
	
	idx->lsn=0;
	idx->max_mtbl=max_mtbl;
	idx->max_mtbl_size=max_mtbl_size;
	memset(idx->name,0,INDEX_NSIZE);
	memcpy(idx->name,name,INDEX_NSIZE);

	/*mtable*/
	idx->mtbls=calloc(idx->max_mtbl,sizeof(struct skiplist*));
	idx->mtbls[0]=skiplist_new(idx->max_mtbl_size);

	/*log*/
	idx->log=log_new(name);

	return idx;
}


int index_add(struct index *idx,struct slice *sk,struct slice *sv)
{
	int i;
	UINT db_offset;
	struct skiplist *list;

	db_offset = log_append(idx->log,sk,sv);
	list = idx->mtbls[idx->lsn];

	if(!list){
		__DEBUG("list<%d> is NULL",idx->lsn);
		return 0;
	}

	if(!skiplist_notfull(list)){
		if(idx->lsn < idx->max_mtbl-1)
			idx->lsn++;
		else{
			__DEBUG("%s","To do merge...");

			for(i=0;i<idx->max_mtbl;i++){
				/*TODO:merge*/
				skiplist_free(idx->mtbls[i]);
			}

			__DEBUG("%s","Finished free all mtables");

			idx->lsn=0;

			log_free(idx->log);
			idx->log=log_new(idx->name);
		}

		__DEBUG("%s","create new mtable");

		list=skiplist_new(idx->max_mtbl_size);
		idx->mtbls[idx->lsn]=list;
	}
	skiplist_insert(list,sk,db_offset,ADD);

	return 1;
}
