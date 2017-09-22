/*
  pre cond: choose port number, which is more than 0 and less than 2^16-1
  post cond: prints string recied from the client
*/
#include "sockets.h"
int sockfd;

//char nick[MAX];s
void sfault1(int sig)
{
  if(sig == SIGINT)
    {
      usleep(3000);
      puts("\nclosing server\n");
      exit(0);
    }
}
/*
void sfault2(int sig)
{
  if(sig == SIGINT)
    {
      usleep((getpid()%100+50)*10);
      //str("*** ");
      //str(nick);
      // panic(" disconnected \n", 1);
    }
}
*/
int main(int argc, char** argv)
{
  struct sockaddr_in srv;
  struct sockaddr_in cli;
  int sockfd;
  int sockfd2;
  int nport;
  int scli;
  int n;
  int counter; 
  int pid;
  char *srvadd;
  char *buff;
  char *connestablished = "HTTP/1.0 200 Connection established\n\n";
  signal(SIGINT, sfault1);
  if (argc < 2)
    {
      puts ("Use: nport\n");
      exit(0);
    }
  buff = (char *)malloc(MAX*sizeof(char));
  srvadd = (char *)malloc(MAX*sizeof(char));
  
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0)
    {
      puts("Invalid socket\n");
      exit(0);
    }
  memset(&srv, 0, sizeof(srv));
  nport = atoi(argv[1]);
  
  srv.sin_family = AF_INET;
  srv.sin_port = htons(nport);
  srv.sin_addr.s_addr = INADDR_ANY;
  if(bind(sockfd, (struct sockaddr *)&srv, sizeof(srv)) < 0)
    {
      puts("Invalid bind\n");
      exit(0);
    }
  listen(sockfd, 5);
  while(1)
    {
      scli = sizeof(cli);
      sockfd2 = accept(sockfd, (struct sockaddr *)&cli, &scli);
      if(sockfd2  < 0)
	{
	  puts("Invalid connection\n");
	  exit(0);
	}
      if((pid = fork()) < 0)
	{
	  puts("Bad Fork\n");
	  exit(0);
	}
      else if(pid==0)
	{
	  close(sockfd);
	  if ((n = read(sockfd2,buff,MAX-1)) < 0)
	    /*lolerr;*/;
	  buff[n] = '\0';
	  /*parse*/
	  if (strncmp("CONNECT",buff,7) == 0)
	    {
	      /* buff contains CONNECT host:port .... \n */
	      /* buff = "CONNECT host:port" */
	      //spaceptr = strchr(buff,' ');
	      //colonptr = strchr(buff,':');
	      const char *sptr = strstr(buff, "CONNECT")+8;
	      const char *cptr = strchr(buff, ':');
	      size_t len = cptr - sptr;
	      strncpy(srvadd, sptr, len);
	      puts(srvadd);
	      puts("");
	      nport = atoi(cptr+1);
	      /*get dat hostname and get dat port*/
	    }
	  if(nport <= 0 || nport > 65535)
	    {
	      puts("Invalid port num\n");
	      exit(0);
	    }
	  if ( (n = write(sockfd2, connestablished, strlen(connestablished))) < 0)
	    {
	      puts("Connection was not established");
	      exit(0);
	    }
	  else
	    puts("Connection with proxy client established!");
	  
	  sslstuff(srvadd, nport, sockfd2);
	}
    }
}


