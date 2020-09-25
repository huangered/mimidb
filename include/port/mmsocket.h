#ifndef _MM_SOCKET_H_
#define _MM_SOCKET_H_

#ifdef _WIN32
#include <winsock2.h>
#endif

SOCKET mm_socket(int af, int type, int protocol);
int mm_bind(SOCKET s, const struct sockaddr* name, int namelen);
int mm_listen(SOCKET s, int backlog);
SOCKET mm_accept(SOCKET s, struct sockaddr* addr, int* addrlen);
int mm_recv(SOCKET s, char* buf, int len, int flags);
int send(SOCKET s, const char* buf, int len, int flags);
int mm_close(SOCKET s);
#endif