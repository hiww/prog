/* FTP-Client */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>  /* inet_xxx 関数のため追加(KW) */
#include <unistd.h>     /* close 関数のため追加(KW) */

#define MAXLINE  1024   /* バッファ長 */
#define IP_LEN   30     /* IPアドレス文字列長 */
#define TCP_PORT 8001   /* TCPポート番号 */
#define CMD_MAX  64     /* コマンド長 */
#define END "\0"        /* バッファの終端を示すメッセージ */

#define RECV_FILENAME "recv.dat"  /* 受信後格納ローカルファイル名 */

int main (void) {
  int servsock, flag, recvlen;
  int statement = 0;    /* 状態変数であり、接続 = 1, 切断 = 0 */
  struct sockaddr_in servaddr;
  char buf[MAXLINE], cmd[CMD_MAX], cmd1[CMD_MAX], cmd2[CMD_MAX], *tok;
  FILE *fp;

	while(1) {
		/* コマンド入力 */
		printf(">");
		fgets(cmd, 256, stdin);
		tok = strtok(cmd," \n");
		strcpy(cmd1,tok);

		/* openコマンドが入力されたとき
		   接続に失敗したらエラーメッセージを表示する
		   成功したらIPとPORTを表示、状態変数を1にする */

		if (strcmp(cmd1,"open") == 0) {
			tok = strtok(NULL," \n");
			strcpy(cmd2,tok);
			servsock = socket(AF_INET, SOCK_STREAM, 0);
  			servaddr.sin_family = AF_INET;
  			servaddr.sin_port = htons(TCP_PORT);
  			servaddr.sin_addr.s_addr = inet_addr(cmd2);
			flag = connect(servsock, (struct sockaddr *)&servaddr, sizeof(servaddr));
			if (flag == -1) {
			  	printf("Failed connect.\n");
			  	continue;
			}
			printf("accessed!\nserverIP: %s\nPORT: %d\n", inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port));
			statement = 1;
			continue;
		}

		/* lsコマンドが入力されたとき
		   切断状態ならエラーメッセージを表示する
		   接続状態ならコマンドを送信し受信したバッファを表示する */

		else if (strcmp(cmd1,"ls") == 0) {
			if (statement != 1){
				printf("not connect.\n");
				continue;
			}
			send(servsock, cmd1, CMD_MAX, 0);
			while ((recvlen = recv(servsock, buf, MAXLINE, 0)) > 0 && strcmp(buf,END) != 0) {
		  	printf("%s", buf);
			}
			continue;
		}

		/* getコマンドが入力されたとき
		   切断状態ならエラーメッセージを表示する
		   接続状態ならコマンドを送信し格納用ファイルを開く
		   受信したバッファをファイルに書き込む
		   最後に受信したデータサイズを表示する */

		else if (strcmp(cmd1,"get") == 0) {
			if (statement != 1) {
				printf("not connect.\n");
				continue;
			}
			send(servsock, cmd1, CMD_MAX, 0);
			int recvsize = 0;
			tok = strtok(NULL," \n");
			strcpy(cmd2,tok);
			if ((fp = fopen(RECV_FILENAME, "w")) == NULL) {
		  		printf("file is not open.\n");
		  		break;
			}
			send(servsock, cmd2, CMD_MAX, 0);
			while ((recvlen = recv(servsock, buf, MAXLINE, 0)) > 0 && strcmp(buf,END) != 0) {
		  		fwrite(buf, 1, recvlen, fp);
		  		recvsize += recvlen;
			}
			printf("%d bytes recieved.\n", recvsize);
			fclose(fp);
			continue;
		}

		/* helpコマンドが入力されたとき
		   受け付けるコマンドを表示する */

		else if (strcmp(cmd1, "help") == 0) {
			printf("open aaa.aaa.aaa.aaa\nls\nget xxxxx\nman\nclose\nquit\n");
			continue;
		}

		/* manコマンドが入力されたとき
		   FTPコマンドについての説明を表示する */
		else if (strcmp(cmd1, "man") == 0) {
			printf("ftp -- Internet file transfer program\n");
			continue;
		}

		/* closeコマンドが入力されたとき
		   切断状態ならエラーメッセージを表示する
		   接続状態ならサーバとの通信を切断し、状態変数を0にする */

		else if (strcmp(cmd1, "close") == 0) {
			if (statement != 1) {
				printf("not connect.\n");
				continue;
			}
			send(servsock, cmd1, CMD_MAX, 0);
			printf("Disconnected.\n");
			close(servsock);
			statement = 0;
			continue;
		}

		/* quitコマンドが入力されたとき
		   接続状態のときコマンドを送信しサーバ、
		   クライアント両方のプログラムを終了する
		   切断状態のときクライアントのみプログラムを終了する */

		else if (strcmp(cmd1, "quit") == 0) {
			if (statement == 1) {
				send(servsock, cmd1, CMD_MAX, 0);
			}
			close(servsock);
			printf("quited.\n");
			break;
  	}
  	/* 上記以外のコマンドが入力されたとき
  	   エラーメッセージを送信する */
  	else {
  		printf("incorrect command.\n");
  		continue;
		}
	}
	return 0;
}

