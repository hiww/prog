#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <regex.h>

#define MAXLINE  1024
#define IP_LEN   30
#define TCP_PORT 8002
#define CN_LEN   25

static void *RecvThread (void *servsock) {
	char str[MAXLINE];
	char message[MAXLINE];
	while (recv((int)servsock, message, MAXLINE, 0) > 0) {
		printf("%s", message);
	}
}


int main (void) {
	struct sockaddr_in servaddr;
	char buf[MAXLINE], ip[IP_LEN]="127.0.0.1";
	char Cliname[CN_LEN];
	char err[2]; 
	const char regex[] = "\\S+";
	regex_t regexBuffer;
	int servsock, flag;
	int x; 
	pthread_t tid;

	servsock = socket (AF_INET, SOCK_STREAM, 0);
	servaddr.sin_family      = AF_INET;
	servaddr.sin_port        = htons(TCP_PORT);
	servaddr.sin_addr.s_addr = inet_addr(ip);
/*	int flag_loop = 0;
	while (flag_loop != 1) {
		printf("Name: ");
		fgets(Cliname, CN_LEN, stdin);
		char *tmp = strchr(Cliname, '\n');
		if (tmp != NULL) {
			*tmp = '\0';
		} else { //stdin < CN_LEN
			printf("Too long!\n");
			while (getchar() != '\n');
			continue;
		}

		if (regcomp(&regexBuffer, regex, REG_EXTENDED | REG_NOMATCH) != 0) {
			printf("正規表現のコンパイルが失敗しています.\n");
			return(1);
		}

		if (regexec(&regexBuffer, Cliname, 0, NULL, 0) != REG_NOMATCH) {
			flag_loop = 1;
		} else {
			return(-1);
		}
	}
*/

  int input_flag = 0;
  while(!input_flag){
		printf("Name: ");
		fgets(Cliname, CN_LEN, stdin);
		char *tmp = strchr(Cliname, '\n');
		if (tmp != NULL) {
			*tmp = '\0';
		} else { //stdin < CN_LEN
			printf("Too long!\n");
			while (getchar() != '\n');
			continue;
		}
  	if(regcomp( &regexBuffer, regex, REG_EXTENDED | REG_NOMATCH ) != 0 ){
  		printf("Failed.\n");
  	    return 1;
  	}
  	if(regexec(&regexBuffer, Cliname, 0, NULL, 0) != REG_NOMATCH) {  // Match
  	    input_flag = 1;
  	  } else {
  	    puts("Try again.");
  	  }
  }

	flag = connect(servsock, (struct sockaddr *)&servaddr, sizeof(servaddr));

	send(servsock, Cliname, strlen(Cliname)+1, 0);
	recv(servsock, err, 2, 0);
	if (flag == -1) {
		printf("サーバへの接続に失敗しました\n");
		return(-1);
	} else if (err[0] == 'N' && err[1] == 'G') {
		printf("そのユーザー名は既に存在します.プログラムを終了します\n");
		return(-1);
	} else {
		printf("アクセスしました．チャットを開始します\n");
	}

	pthread_create(&tid, NULL, &RecvThread, (void *)servsock);

	while (1) {
		fgets(buf, MAXLINE, stdin);
		if (buf[strlen(buf)-1] == '\n'){
			buf[strlen(buf)-1] = '\0'; 
		}
		if (buf[0] == 'e' && buf[1] == 'n' && buf[2] == 'd') {
			break;
		} else {
			send(servsock, buf, MAXLINE, 0);
		}
	}

	close(servsock);
	printf("通信を終了しました\n");
	return(0);
}
