#ifndef _LOG_H
#define _LOG_H

#include "util.h"
#include "platform.h"

#define LOG_NSIZE (256)

struct log{
	int fd;
	int fd_db;
	char name[LOG_NSIZE];
	UINT db_alloc;
	struct buffer *buf;
};

struct log *log_new(char *name);
UINT log_append(struct log *log,struct slice *sk,struct slice *sv);
void log_free(struct log *log);

#endif
