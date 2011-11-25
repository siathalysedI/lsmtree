#ifndef _LOG_H
#define _LOG_H

#include "util.h"
#include "buffer.h"
#include "platform.h"

struct log{
	int fd;
	int fd_db;
	size_t size;
	UINT db_alloc;
	struct buffer *buffer;
};

struct log *log_new(char *name);
UINT log_append(struct log *log,struct slice *sk,struct slice *sv);
void log_free(struct log *log);

#endif
