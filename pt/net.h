#ifndef PTNET_H
#define PTNET_H

#include "types.h"
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <poll.h>

int  ptnetcon(const char *ip, u16 prt);
int  ptnetbind(const char *ip, u16 prt);
int  ptnetacc(int s);
int  ptnetsnd(int s, u8 *buf, u32 bufs);
int  ptnetrcv(int s, u8 *buf, u32 bufs);
void ptnetcls(int s);
int  ptnetnonblk(int s, bool nb);
int  ptnetdns(const char *host, char *ip);
int  ptnetpollr(int s, int tmo);
int  ptnetpollw(int s, int tmo);

#endif
