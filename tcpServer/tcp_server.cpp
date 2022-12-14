#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define TCP_PORT 5100  // 서버의 포트 번호

int main(int argc, char **argv)
{
    int serverSock_fd, clientSock_fd;  //소켓 디스크립트 정의
    socklen_t clen;
    int n;
    struct sockaddr_in servaddr, cliaddr;  // 주소 구조체 정의
    char mesg[BUFSIZ];

    // 서버 소켓 생성
    if((serverSock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket()");
        return -1;
    }
    int option = -1;
    setsockopt(serverSock_fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    
    // 주소 구조체에 주소 지정
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // all local ip
    servaddr.sin_port = htons(TCP_PORT);
    
    // bind함수를 사용하여 서버 소켓의 주소 설정
    if(bind(serverSock_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind()");
        return -1;
    }

    // 동시에 접속하는 클라이언트의 처리를 위한 대기 큐를 설정
    if(listen(serverSock_fd, 8) < 0)
    {
        perror("listen()");
        return -1;
    }

    clen = sizeof(cliaddr);
    do{
        // 클라이언트가 접속하면 접속을 허용하고 클라이언트 소켓 생성
       clientSock_fd = accept(serverSock_fd, (struct sockaddr *)&cliaddr, &clen);

        // 네트워크 주소를 문자열로 변경
        inet_ntop(AF_INET, &cliaddr.sin_addr, mesg, BUFSIZ);
        printf("Client is connected : %s\n", mesg);

        if((n = read(clientSock_fd, mesg, BUFSIZ)) <= 0)
            perror("read()");

        printf("Received data : %s", mesg);

        // 클라이언트로 buf에 있는 문자열 전송
        if(write(clientSock_fd, mesg, n) <= 0)
            perror("write()");
        
        close(clientSock_fd);   // 클라이언틑 소켓을 닫음.
    }while(strncmp(mesg, "q", 1));

    close(serverSock_fd);   //서버 소켓을 닫음.
    
    return 0;
}