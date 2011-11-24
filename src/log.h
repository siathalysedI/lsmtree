#ifndef _LOG_H
#define _LOG_H

struct log{
	int fd;
	size_t size;
};

struct log *log_new(char *name);
void log_append(struct log *log,char *key,int klen,char *val,int vlen);
void log_free(struct log *log);

#endif
