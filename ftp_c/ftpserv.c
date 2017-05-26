/* FTP-Server */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>  /* inet_xxx 関数のため追加(KW) */
#include <unistd.h>     /* close 関数のため追加(KW) */

#define MAXLINE  1024   /* バッファ長 */
#define FN_MAX   256    /* filename長 */
#define TCP_PORT 8001   /* TCPポート番号 */
#define IP "127.0.0.1"  /* IPアドレス */
#define END "\0"        /* バッファの終端を示すメッセージ */

int main (void) {
  struct sockaddr_in servaddr, cliaddr;
  int servsock, clisock, readlen, cliaddrlen = sizeof(cliaddr);
  int statement = 0;    /* 状態変数であり、接続 = 1, 切断 = 0 */
  char buf[MAXLINE], filename[FN_MAX];
  FILE *fp;

  servsock = socket (AF_INET, SOCK_STREAM, 0);
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(TCP_PORT);
  servaddr.sin_addr.s_addr = inet_addr(IP);

  while(1) {

    /* 切断状態のときクライアントからの接続があるまで待機する
       接続したらIP,PORTを表示し状態変数を1にする */

    if (statement != 1) {
      bind(servsock, (struct sockaddr *)&servaddr, sizeof(servaddr));

      listen(servsock, 1);
      printf("Wait for access...\n");

      clisock = accept(servsock, (struct sockaddr *)&cliaddr, &cliaddrlen);
      printf("Connected. IP=%s, PORT=%d\n", IP, TCP_PORT);
      statement = 1;
    }

    recv(clisock, buf, MAXLINE, 0);

    /* lsコマンドを受信したとき
       fileディレクトリの情報を取得し、クライアントに送信する */

    if (strcmp(buf,"ls") == 0) {
      printf("ls command recieved.\n");
      fp = popen("ls -lah", "r");
      while (fgets(buf, MAXLINE, fp) != NULL) {
        send(clisock, buf, MAXLINE, 0);       
      }
      send(clisock, END, MAXLINE, 0);
      printf("send finished.\n");
      pclose(fp);
      continue;
    }

    /* getコマンドを受信したとき
       ファイル名が一致しないならエラーメッセージを表示する
       一致したらファイルを読み込み、バッファを送信する */  

    if (strcmp(buf, "get") == 0) {
      printf("get command recieved.\n");
      recv(clisock, buf, MAXLINE, 0);
      if ((fp = fopen(buf, "r")) == NULL) {
        printf("file is not found.\n");
        send(clisock, END, MAXLINE, 0);
        continue;
      }
      while ((readlen = fread(buf, 1, MAXLINE, fp)) != 0) {
        send(clisock, buf, readlen, 0);
      }
      send(clisock, END, MAXLINE, 0);
      printf("send finished.\n");
      fclose(fp);
      continue;
    }

    /* closeコマンドを受信したとき
       クライアントとの接続を切り、状態変数を0にする */

    if (strcmp(buf, "close") == 0) {
      printf("Disconnected.\n");
      close(clisock);
      statement = 0;
      continue;
    }

    /* quitコマンドを受信したとき
       通信を切断しプログラムを終了する */

    if (strcmp(buf, "quit") == 0){
      printf("quited.\n");
      close(servsock);
      close(clisock);
      break;
    }
  }
  return 0;
}
