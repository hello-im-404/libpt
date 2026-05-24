#include "net.h"
#include <string.h>
#include <fcntl.h>

int ptnetcon(const char *ip, u16 prt) {
	int s;
	struct sockaddr_in addr;
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(prt);
	if (inet_pton(AF_INET, ip, &addr.sin_addr) <= 0) { close(s); return -1; }
	if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) { close(s); return -1; }
	return s;
}

int ptnetbind(const char *ip, u16 prt) {
	int s;
	struct sockaddr_in addr;
	int opt = 1;
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(prt);
	if (inet_pton(AF_INET, ip, &addr.sin_addr) <= 0) { close(s); return -1; }
	if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) { close(s); return -1; }
	if (listen(s, 10) < 0) { close(s); return -1; }
	return s;
}

int ptnetacc(int s) {
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);
	return accept(s, (struct sockaddr *)&addr, &addrlen);
}

int ptnetsnd(int s, u8 *buf, u32 bufs) { return send(s, buf, bufs, 0); }
int ptnetrcv(int s, u8 *buf, u32 bufs) { return recv(s, buf, bufs, 0); }
void ptnetcls(int s) { close(s); }

int ptnetnonblk(int s, bool nb) {
	int fl = fcntl(s, F_GETFL, 0);
	if (fl < 0) return -1;
	return fcntl(s, F_SETFL, nb ? (fl | O_NONBLOCK) : (fl & ~O_NONBLOCK));
}

int ptnetdns(const char *host, char *ip) {
    struct hostent *he = gethostbyname(host);
    if (!he) return -1;
    struct in_addr **addr_list = (struct in_addr **)he->h_addr_list;
    if (addr_list[0]) {
        strcpy(ip, inet_ntoa(*addr_list[0]));
        return 0;
    }
    return -1;
}

int ptnetpollr(int s, int tmo) {
    struct pollfd fds;
    fds.fd = s;
    fds.events = POLLIN;
    return poll(&fds, 1, tmo);
}

int ptnetpollw(int s, int tmo) {
    struct pollfd fds;
    fds.fd = s;
    fds.events = POLLOUT;
    return poll(&fds, 1, tmo);
}
