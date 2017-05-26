/* Easy-Chat-Client */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>  /* inet_xxx */
#include <unistd.h>     /* close */

#define MAXLINE  1024   /* Buffer Length */
#define IP_LEN   30     /* IP-Length */
#define TCP_PORT 8002   /* TCP Port */

/* Reception processing thread  */
static void *RecvThread (void *servsock) {
  char str[MAXLINE];

  while (recv((int)servsock, str, MAXLINE, 0) > 0) {
    printf("相手の発言 : %s\n", str);
  }
}

/* Main（Client wait, instantiation of send / receive thread） */
int main (void) {
  struct sockaddr_in servaddr;
  char buf[MAXLINE], ip[IP_LEN]="127.0.0.1";
  int servsock, flag;
  pthread_t tid;

  while(1){
  	printf("ユーザ名を入力してください : ");
  	fgets(buf, MAXLINE, stdin);
  	if(strcmp(buf," ") == 0 || strcmp(buf,"\n") == 0){
  		printf("正しいユーザ名を入力してください\n");
  	} else {
  		servsock = socket (AF_INET, SOCK_STREAM, 0);
 	 	servaddr.sin_family = AF_INET;
  		servaddr.sin_port = htons(TCP_PORT);
  		servaddr.sin_addr.s_addr = inet_addr(ip);

  		flag = connect(servsock, (struct sockaddr *)&servaddr, sizeof(servaddr));
  		if (flag == -1) {
    		printf("サーバへの接続に失敗しました\n");
    		return(-1);
  		} else {
    		printf("アクセスしました. \n");
  			strtok(buf,"\n");
  			send(servsock, buf, MAXLINE, 0);
  			recv(servsock, buf, MAXLINE, 0);
  			if (strcmp(buf,"NG") == 0) {
  				printf("そのユーザ名は既に使用されています\n");
  				return(-1);
  			} else {
  				recv(servsock, buf, MAXLINE, 0);
  				printf("ルームを選択してください %s : ", buf);
  				fgets(buf, MAXLINE, stdin);
  				send(servsock, buf, MAXLINE, 0);
  				recv(servsock, buf, MAXLINE, 0);
  				if(strcmp(buf,"NG") == 0){
  					printf("ルームに入れませんでした\n");
  					return(-1);
  				} else {
  					printf("チャットを開始します\n");
  					pthread_create(&tid, NULL, &RecvThread, (void *)servsock);
  					break;
  				}
  			}
			}
		}
	}

  /* Generate instance (tid) of the receiving thread */
  pthread_create(&tid, NULL, &RecvThread, (void *)servsock);

  /* Until "end" is input, send a message to the server */
  while (1) {
    fgets(buf, MAXLINE, stdin);
    strtok(buf,"\n");
    if (strcmp(buf, "end") == 0) {
      break;
    } else {
      send(servsock, buf, MAXLINE, 0);
    }
  }

  close(servsock);
  printf("通信を終了しました\n");
  return(0);
}