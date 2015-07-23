
CC =		cc
CFLAGS = -pipe  -O -W -Wall -Wpointer-arith -Wno-unused-parameter -Werror -g
LINK = $(CC)

CORE_DEPS =  \
	src/core/znet.h \
	src/core/znet_core.h \
	src/core/znet_string.h \
	src/os/unix/znet_process_cycle.h \
	src/os/unix/znet_process.h \
	src/os/unix/znet_setproctitle.h \
	src/os/unix/znet_channel.h \
	src/os/unix/znet_event.h \
	src/os/unix/znet_socket.h

CORE_INCS = -I src/core \
	-I src/os/unix \
	-I objs


objs/znet:	objs/src/core/znet.o \
	objs/src/core/znet_string.o \
	objs/src/os/unix/znet_process_cycle.o \
	objs/src/os/unix/znet_process.o \
	objs/src/os/unix/znet_setproctitle.o \
	objs/src/os/unix/znet_channel.o \
	objs/src/os/unix/znet_event.o \
	objs/src/os/unix/znet_socket.o
	$(LINK) -o objs/znet \
	objs/src/core/znet.o \
	objs/src/core/znet_string.o \
	objs/src/os/unix/znet_process_cycle.o \
	objs/src/os/unix/znet_process.o \
	objs/src/os/unix/znet_setproctitle.o \
	objs/src/os/unix/znet_channel.o \
	objs/src/os/unix/znet_event.o \
	objs/src/os/unix/znet_socket.o
	



objs/src/core/znet.o:	$(CORE_DEPS) \
	src/core/znet.c
	$(CC) -c $(CFLAGS) $(CORE_INCS) \
		-o objs/src/core/znet.o \
		src/core/znet.c


objs/src/core/znet_string.o:	$(CORE_DEPS) \
	src/core/znet_string.c
	$(CC) -c $(CFLAGS) $(CORE_INCS) \
		-o objs/src/core/znet_string.o \
		src/core/znet_string.c


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


objs/src/os/unix/znet_setproctitle.o:	$(CORE_DEPS) \
	src/os/unix/znet_setproctitle.c
	$(CC) -c $(CFLAGS) $(CORE_INCS) \
		-o objs/src/os/unix/znet_setproctitle.o \
		src/os/unix/znet_setproctitle.c


objs/src/os/unix/znet_channel.o:	$(CORE_DEPS) \
	src/os/unix/znet_channel.c
	$(CC) -c $(CFLAGS) $(CORE_INCS) \
		-o objs/src/os/unix/znet_channel.o \
		src/os/unix/znet_channel.c


objs/src/os/unix/znet_event.o:	$(CORE_DEPS) \
	src/os/unix/znet_event.c
	$(CC) -c $(CFLAGS) $(CORE_INCS) \
		-o objs/src/os/unix/znet_event.o \
		src/os/unix/znet_event.c


objs/src/os/unix/znet_socket.o:	$(CORE_DEPS) \
	src/os/unix/znet_socket.c
	$(CC) -c $(CFLAGS) $(CORE_INCS) \
		-o objs/src/os/unix/znet_socket.o \
		src/os/unix/znet_socket.c

