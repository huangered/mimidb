#include "mimi.hpp"
#include "port/mmsocket.hpp"

#ifdef _WIN32
  #include <winsock2.h>
  #pragma comment(lib, "Ws2_32.lib")

void
startup() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(1234);
    bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

    listen(servSock, 20);

    SOCKADDR clntAddr;
    int nSize = sizeof(SOCKADDR);
    SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);

    char recvbuf[512];

    for (;;) {
        int recvResult = recv(clntSock, recvbuf, 512, 0);
        if (recvResult > 0) {
            printf("receive %d chars\r\n", recvResult);
            for (int i = 0; i < recvResult; i++) {
                printf("%c", recvbuf[i]);
            }
            printf("\r\n");
        }

        char* str = "Hello World!";
        send(clntSock, str, strlen(str) + sizeof(char), NULL);
    }
    closesocket(clntSock);
    closesocket(servSock);

    WSACleanup();
}

#endif