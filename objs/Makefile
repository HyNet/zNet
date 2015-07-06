
CC =		cc
CFLAGS = -pipe  -O -W -Wall -Wpointer-arith -Wno-unused-parameter -Werror -g
LINK = $(CC)

CORE_DEPS =  \
	src/core/znet.h \
	src/core/znet_core.h \
	src/os/unix/znet_process_cycle.h \
	src/os/unix/znet_process.h

CORE_INCS = -I src/core \
	-I src/os/unix \
	-I objs


objs/znet:	objs/src/core/znet.o \
	objs/src/os/unix/znet_process_cycle.o \
	objs/src/os/unix/znet_process.o
	$(LINK) -o objs/znet \
	objs/src/core/znet.o \
	objs/src/os/unix/znet_process_cycle.o \
	objs/src/os/unix/znet_process.o
	



objs/src/core/znet.o:	$(CORE_DEPS) \
	src/core/znet.c
	$(CC) -c $(CFLAGS) $(CORE_INCS) \
		-o objs/src/core/znet.o \
		src/core/znet.c


objs/src/os/unix/znet_process_cycle.o:	$(CORE_DEPS) \
	src/os/unix/znet_process_cycle.c
	$(CC) -c $(CFLAGS) $(CORE_INCS) \
		-o objs/src/os/unix/znet_process_cycle.o \
		src/os/unix/znet_process_cycle.c


objs/src/os/unix/znet_process.o:	$(CORE_DEPS) \
	src/os/unix/znet_process.c
	$(CC) -c $(CFLAGS) $(CORE_INCS) \
		-o objs/src/os/unix/znet_process.o \
		src/os/unix/znet_process.c

