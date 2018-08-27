#include <sys/socket.h>
#include <memory.h>
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAX_SOCKET_BUFFER       (1024 * 1024 * 4)  
#define PORT 8000
int main()
{
    int server_sockfd;
    int client_sockfd;
    int len;
    struct sockaddr_in my_addr;
    struct sockaddr_in remote_addr;
    socklen_t sin_size;
    char buf[MAX_SOCKET_BUFFER];
    memset(&my_addr,0,sizeof(my_addr));
    //bzero(&(my_addr.sin_zero), 8); /* 将整个结构剩余*/
    /* 部分数据设为 0 */
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //my_addr.sin_addr.s_addr=htonl(INADDR_ANY)//("127.0.0.1");//服务器IP地址--允许连接到所有本地地址上
    my_addr.sin_port = htons(PORT);
    
    if((server_sockfd=socket(PF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket error");
        return 1;
    }
    int opt = 1;
    // sockfd为需要端口复用的套接字
    setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(opt));
    if(bind(server_sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))<0)
    {
        perror("bind error");
        return 1;
    }
    if(listen(server_sockfd,5)<0)
    {
        perror("listen error");
        return 1;
    }
    sin_size = sizeof(struct sockaddr);
    if((client_sockfd = accept(server_sockfd,(struct sockaddr *)&remote_addr,&sin_size))<0)
    {
        perror("accept error");
        return 1;
    }
    printf("accept client %s\n",inet_ntoa(remote_addr.sin_addr));
    len = send(client_sockfd,"Welcome to my server\n",21,0);
    
    while((len = recv(client_sockfd,buf,BUFSIZ,0))>0)
    {
        buf[len] = '\0';
        printf("%s\n",buf);
        if(send(client_sockfd,buf,len,0)<0)
        {
            perror("write error");
            return 1;
        }
    }
    close (client_sockfd);
    close (server_sockfd);
    return 0;
}