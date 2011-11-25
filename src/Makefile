UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	DEBUG = -g -rdynamic -ggdb -DDEBUG
else
	DEBUG =	-g -ggdb -DDEBUG
endif

CC = gcc
CFLAGS =  -c -std=c99 -Wall $(DEBUG)	

LIB_OBJS =     \
	./index.o  \
	./log.o	   \
	./stable.o \
	./buffer.o    \
	./skiplist.o

TEST_OBJS =\
	./test_skiplist.o \
	./test_index.o    \
	./test_buffer.o

TESTS = \
	./test_skiplist \
	./test_index    \
	./test_buffer

LIBRARY = liblsmtree.a

all: $(LIBRARY)

clean:
	-rm -f $(LIBRARY)  
	-rm -f $(LIB_OBJS)
	-rm -f $(TEST_OBJS)
	-rm -f $(TESTS)

cleanall:
	-rm -f $(LIBRARY)  
	-rm -f $(LIB_OBJS)
	-rm -f $(TEST_OBJS)
	-rm -f $(TESTS)
	
	-rm -f *.log
	-rm -f *.db

$(LIBRARY): $(LIB_OBJS)
	rm -f $@
	$(AR) -rs $@ $(LIB_OBJS)

test_skiplist: ./test_skiplist.o  $(TEST_OBJS) $(LIB_OBJS)
	$(CC)	./test_skiplist.o $(SVR_OBJS) $(LIB_OBJS) -o $@

test_index: ./test_index.o $(TEST_OBJS) $(LIB_OBJS)
	$(CC) 	 ./test_index.o $(SVR_OBJS) $(LIB_OBJS) -o $@

test_buffer: ./test_buffer.o $(TEST_OBJS) $(LIB_OBJS)
	$(CC) 	 ./test_buffer.o $(SVR_OBJS) $(LIB_OBJS) -o $@
