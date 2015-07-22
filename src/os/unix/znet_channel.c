
/*
 * Copyright (C) zhao
 */

#include<znet_core.h>
#include<znet_channel.h>


znet_int_t 
znet_write_channel(znet_socket_t s, znet_channel_t *ch, size_t size)
{
	ssize_t             n;
	struct msghdr msg;
	struct iovec        iov[1];

	union {
		struct cmsghdr cm;
		char	space[CMSG_SPACE(sizeof(int))];
	}cmsg;

	if (ch->fd == -1) {
		msg.msg_control = NULL;
		msg.msg_controllen = 0;
	}else{
		msg.msg_control = (caddr_t)&cmsg;
		msg.msg_controllen = sizeof(cmsg);
		
		memset(&cmsg, 0, sizeof(cmsg));

		cmsg.cm.cmsg_len = CMSG_LEN(sizeof(int));
		cmsg.cm.cmsg_level = SOL_SOCKET;
		cmsg.cm.cmsg_type = SCM_RIGHTS;
		
		memcpy(CMSG_DATA(&cmsg.cm), &ch->fd, sizeof(int));
	}
	msg.msg_flags = 0;

	iov[0].iov_base = (char *) ch;
    iov[0].iov_len = size;

    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;

    n = sendmsg(s, &msg, 0);
	
	if (n == -1){
		if (errno == EAGAIN) {
			return -2;
		}
		return -1;
	}

	return 0;
}

znet_int_t 
znet_read_channel(znet_socket_t s, znet_channel_t *ch, size_t size)
{
	ssize_t             n;
    struct iovec        iov[1];
    struct msghdr       msg;
	
	union {
        struct cmsghdr  cm;
        char            space[CMSG_SPACE(sizeof(int))];
    } cmsg;

	iov[0].iov_base = (char *) ch;
    iov[0].iov_len = size;

    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;

	msg.msg_control = (caddr_t) &cmsg;
    msg.msg_controllen = sizeof(cmsg);

	n = recvmsg(s, &msg, 0);

	if (n == -1) {
        if (errno == EAGAIN) {
            return -2;
        }

        return -1;
    }

    if (n == 0) {
        return -1;
    }

    if ((size_t) n < sizeof(znet_channel_t)) {
        return -1;
    }

	if (ch->command == ZNET_CMD_OPEN_CHANNEL) {

        if (cmsg.cm.cmsg_len < (socklen_t) CMSG_LEN(sizeof(int))) {
            return -1;
        }

        if (cmsg.cm.cmsg_level != SOL_SOCKET || cmsg.cm.cmsg_type != SCM_RIGHTS)
        {
            return -1;
        }

        /* ch->fd = *(int *) CMSG_DATA(&cmsg.cm); */

        memcpy(&ch->fd, CMSG_DATA(&cmsg.cm), sizeof(int));
    }

    if (msg.msg_flags & (MSG_TRUNC|MSG_CTRUNC)) {
		printf("recvmsg() truncated data\n");
    }
	
	return n;

}


void znet_close_channel(int *fd)
{
	if (close(fd[0]) == -1) {
        printf("close() channel failed\n");
    }

    if (close(fd[1]) == -1) {
        printf("close() channel failed\n");
    }
}

