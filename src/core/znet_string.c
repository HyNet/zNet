
/*
 * Copyright (C) zhao
 */

#include<znet_string.h>

char* 
znet_strncpy(char *dst, char *src, int n)
{
	if (0 == n) {
		return dst;
	}
	while(--n) {
		*dst = *src;
		if (*dst == '\0') {
			return dst;
		}
		dst++;
		src++;
	}
	*dst = '\0';
	return dst;
}

