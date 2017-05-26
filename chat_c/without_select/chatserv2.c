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
#define CN_LEN   50		/* Client Name Length */

/* Global */
int CliNo;              /* [0..MAXCLIENT] */
int Clisock[MAXCLIENT]; /* [0..MAXCLIENT] */
char Cliname[MAXCLIENT][CN_LEN]; /* Client Name Array */

/* Message transmission / reception processing thread */
static void *RecvThread (void *number) {
	char str[MAXLINE];
	char message[MAXLINE + 50];
	int i, selfno;

	selfno = (int)number;
	while (recv(Clisock[selfno], str, MAXLINE, 0) > 0) {
		for (i = 0; i < CliNo; i++) {
			sprintf(message,"発言 #%d (%s) : %s\n", selfno, Cliname[selfno], str);
			send(Clisock[i], message, MAXLINE+50, 0); /* メッセージ送信 */
		}
	}

	close(Clisock[selfno]);
	printf("クライアント %d : 通信終了\n", selfno);
}

/* Main（Client wait, instantiation of send / receive thread）*/
int main (void) {
	struct sockaddr_in servaddr, cliaddr;
	int servsock, num, cliaddrlen = sizeof(cliaddr), i;
	pthread_t tid[MAXCLIENT];
	int dup; /* 重複チェック用 */

	servsock = socket (AF_INET, SOCK_STREAM, 0);
	servaddr.sin_family      = AF_INET;
	servaddr.sin_port        = htons(TCP_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(servsock, (struct sockaddr *)&servaddr, sizeof(servaddr));

	listen(servsock, 5); /* Length = 5 wait */
	printf("クライアントからのアクセスを待ちます\n");

	for (CliNo = 0; CliNo < MAXCLIENT; ) {
		dup = 0;
		Clisock[CliNo] = accept(servsock, (struct sockaddr *)&cliaddr, &cliaddrlen);
		/* Recieve Client Name */
		recv(Clisock[CliNo], Cliname[CliNo], CN_LEN, 0);
		/* Name Check */
		for (i = 0; i < CliNo; i++){
			if(strcmp(Cliname[CliNo], Cliname[i]) == 0){
				send(Clisock[CliNo], "NG", 3, 0);
				dup = 1;
				break;
			}else if(strcmp(Cliname[CliNo], Cliname[i]) != 0){
			}
		}

		if(dup == 1){ continue; }
		printf("アクセスがありました (CliNo=%d)\n", CliNo);
		printf("ユーザ名 : [%s]\n", Cliname[CliNo]);
		send(Clisock[CliNo], "OK", 3, 0);
		num = CliNo;
		CliNo++; /* Client Number = CliNo */
		/* Generate instance of send / receive thread (tid [num]) */
		pthread_create(&tid[num], NULL, &RecvThread, (void *)num);
	}

	/* Join */
	for(i=0; i<MAXCLIENT; i++) {
		pthread_join(tid[i], NULL);
	}

	close(servsock);
	printf("通信を終了しました\n");
	return(0);
}
