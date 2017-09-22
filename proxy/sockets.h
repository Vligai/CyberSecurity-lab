/*
  header file for Sockets
*/
#ifndef _SOCKETS_H_
#define _SOCKETS_H_
#include <signal.h>
#define MAX 1024

#include <fcntl.h>
#include <openssl/bio.h> 
#include <openssl/ssl.h> 
#include <openssl/err.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/ioctl.h>
//#include <arpa/inet.h>
//#include <sys/time.h>
//#include <memory.h>
#include <ifaddrs.h>
#include <net/if.h>
//#include <stdarg.h>

void sfault1(int sig);
int main(int argc, char **argv);
int sslstuff(char *srvadd, int nport, int clientfd);

#endif
