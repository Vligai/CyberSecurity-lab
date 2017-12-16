/* 
   SSL stuff for proxy
   Vladislav Ligai
*/
#include "sockets.h"
//#include <arpa/inet.h>

int sslstuff(char* srvadd, int nport, int clientfd)
{
  /*ssl stuff for connecting to server*/
  SSL_CTX *serverctx;
  SSL *serversslobj;
  const SSL_METHOD *srvmeth;
  int use_cert;
  int use_prv;
  int srvconfd;
  /* ssl stuff for overlay on clientfd */
  SSL_CTX *clientctx;
  SSL *clientsslobj;
  const SSL_METHOD *clientmeth;
  /* other stuff */
  int nbytes;
  char buff[4096];
  int ssl_err;
  /* ssl setups */
  SSL_library_init();
  OpenSSL_add_all_algorithms();
  SSL_load_error_strings();

  srvmeth = SSLv3_server_method();
  clientmeth = SSLv3_client_method();
  serverctx = SSL_CTX_new(srvmeth);
  clientctx = SSL_CTX_new(clientmeth);
  /*load cert/keys for serverctx here*/
  use_cert = SSL_CTX_use_certificate_file(serverctx, "./proxycert.pem", SSL_FILETYPE_PEM);
  use_prv  = SSL_CTX_use_PrivateKey_file(serverctx, "./proxykey.pem", SSL_FILETYPE_PEM);
  if(use_cert <= 0)
    {
      puts("couldn't load certificates");
      exit(0);
    }
  if(use_prv <= 0)
    {
      puts("couldn't load private key");
      exit(0);
    }
  /*overlay dat ssl on clientfd*/
  serversslobj = SSL_new(serverctx);
  SSL_set_fd(serversslobj,clientfd);
  
  ssl_err = SSL_accept(serversslobj);
  
  if(ssl_err <= 0 )
    {
      puts("couldn't accept SSL");
      exit(0);
    }
  
  /*setup underlying socket fd for our connection to the server*/
  struct sockaddr_in srv;
  struct hostent* bserv;
  int n;
  int con;
  int sockfd;
  //int nport;	
  //char buff[MAX];
  //char nick[MAX];
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    {
    puts("invalid socket\n");
    exit(0);
    }
  bserv = gethostbyname(srvadd);
  if (bserv == NULL)
    {
    puts("no host\n");
    exit(0);
    }
  memset(&srv, 0, sizeof(srv));
  srv.sin_family = AF_INET;
  srv.sin_port = htons(nport);
  memcpy(&srv.sin_addr.s_addr, bserv->h_addr, bserv->h_length);
  con = connect(sockfd,  (struct sockaddr *)&srv, sizeof(srv)); 
  if(con<0)
    {
      close(sockfd);
      puts("couldn't connect to proxy");
      exit(0);
    }
  //puts("yay connected to server yayayayay");
  /* overlay ssl on serverfd */
  clientsslobj = SSL_new(clientctx);
  SSL_set_fd(clientsslobj,sockfd);
  SSL_connect(clientsslobj);
  
  FILE *f = fopen("log.txt", "w");
  if (f==NULL)
    {
      puts("Couldn't open log.txt\n");
      exit(0);
    }
  while(1)
    {
      nbytes = SSL_read(serversslobj, buff, 4096);
      fprintf(f, "log: %s\n", buff);
      if(nbytes < 0)
	{
	  puts("read error");
	  exit(0);
	}
      else
	{
	  SSL_write(clientsslobj, buff, nbytes);

	  fflush(f);
	}
      //sigprocmask(SIG_UNBLOCK, &clientsslobj, NULL);
      nbytes = SSL_read(clientsslobj, buff, 4096);
      fprintf(f, "log: %s\n", buff);
      if(nbytes < 0)
	{
	  puts("read error");
	  exit(0);
	}
      else
	{
	  SSL_write(serversslobj, buff, nbytes);
	  fflush(f);
	}
      
      //sigprocmask(SIG_UNBLOCK, &serversslobj, NULL);
      usleep(2000);
    }
  
}
