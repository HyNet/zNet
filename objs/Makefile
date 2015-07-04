
CC =		cc
CFLAGS = -pipe  -O -W -Wall -Wpointer-arith -Wno-unused-parameter -Werror -g
LINK = $(CC)

CORE_DEPS = src/core/znet.h

CORE_INCS = -I src/core \
	-I objs


objs/znet:	objs/src/core/znet.o
	$(LINK) -o objs/znet \
	objs/src/core/znet.o
	



objs/src/core/znet.o:	$(CORE_DEPS) \
	src/core/znet.c
	$(CC) -c $(CFLAGS) $(CORE_INCS)\
		-o objs/src/core/znet.o\
		src/core/znet.c

