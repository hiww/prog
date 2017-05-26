/* Easy-Chat-Server */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>  /* inet_xxx */
#include <unistd.h>     /* close */

#define MAXLINE  1024   /* Buffer Length */
#define MAXCLIENT   3   /* Maximum Connectable Clients */
#define TCP_PORT 8002   /* TCP Port */
#define CHATROOM "[1..3]"

/* Global */
int CliNo;              /* [0..MAXCLIENT] */
int Clisock[MAXCLIENT]; /* [0..MAXCLIENT] */
int flag[MAXCLIENT];
struct vnode{
	char name[MAXLINE];
	char room[MAXLINE];
};

/* Message transmission / reception processing thread */
static void *RecvThread (void *number) {
  char str[MAXLINE];
  char buf[MAXLINE];
  int i, selfno;
	struct vnode name[MAXCLIENT];

	recv(Clisock[CliNo], buf, MAXLINE, 0);
	for(i = 0; i <= MAXCLIENT; i++){
    	if(buf == name[i].name){
    		send(Clisock[CliNo], "NG", MAXLINE, 0);
    	}
    }
    strcpy(name[CliNo].name, buf);
    send(Clisock[CliNo], "OK", MAXLINE, 0);
    send(Clisock[CliNo], CHATROOM, MAXLINE, 0);
    recv(Clisock[CliNo], buf, MAXLINE, 0);
    strtok(buf,"\n");
   	strcpy(name[CliNo].room, buf);
    printf("ユーザ名 : [%s] --> チャットルーム : [%s]\n", name[CliNo].name, name[CliNo].room);
    send(Clisock[CliNo], "OK", MAXLINE, 0);
  selfno = (int)number;
  while (recv(Clisock[selfno], str, MAXLINE, 0) > 0) {
    for (i=0; i<CliNo; i++) {
      if (i != selfno) {
				send(Clisock[i], str, MAXLINE+50, 0); /* Sending messages other than your own thread */
      }
    }
  }

  close(Clisock[selfno]);
  printf("クライアント %d : 通信終了\n", selfno);
  flag[selfno] = 0;
}

/* Main（Client wait, instantiation of send / receive thread）*/
int main (void) {
  struct sockaddr_in servaddr, cliaddr;
  int servsock, num, cliaddrlen = sizeof(cliaddr), i, maxclino = 0;
  pthread_t tid[MAXCLIENT];
  for(i = 0; i < MAXCLIENT; i++){
  	flag[i] = 0;
  }

  servsock = socket (AF_INET, SOCK_STREAM, 0);
  servaddr.sin_family      = AF_INET;
  servaddr.sin_port        = htons(TCP_PORT);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

  bind(servsock, (struct sockaddr *)&servaddr, sizeof(servaddr));
  listen(servsock, 5);
  printf("クライアントからのアクセスを待ちます\n");
  //Clisock[CliNo] = accept(servsock, (struct sockaddr *)&cliaddr, &cliaddrlen);

  //for (CliNo=0; CliNo<MAXCLIENT; ) {
  CliNo = 0;
  while(1){
    Clisock[CliNo] = accept(servsock, (struct sockaddr *)&cliaddr, &cliaddrlen);
    printf("アクセスがありました (CliNo=%d)\n", CliNo);
    flag[CliNo] = 1;
    num = CliNo;
    CliNo++;
    maxclino++;
    /* Generate instance of send / receive thread (tid [num]) */
    pthread_create(&tid[num], NULL, &RecvThread, (void *)num);
  	}
		/* Join */
  	for(i=0; i<maxclino; i++) {
  		if(flag[i] == 0){
				pthread_join(tid[i], NULL);
			}
		}

  close(servsock);
  printf("通信を終了しました\n");
  return(0);
}