#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>  //处理信号问题 应忽略socket 信号
#include <iostream>
#define MY_IP     "127.0.0.1"
#define MY_PORT  8000
#define BACKLOG  100

#define DEBUF(X) printf(X)
int fd = -1;
char buf[100];    //最大连接数
void *func(void *arg)
{    
    char recv_buf[100];
    //char send_buf[100];
    int client_fd = *((int*)arg);//传参
    int ret = 1;
    int count = 1;
    char clientname[200];
    ret = send(client_fd,"Welcome to my server\n",21,0);
    while((ret = recv(client_fd,recv_buf,sizeof(recv_buf),0))>0)
    {
        recv_buf[ret] = '\0';
        if(count==1)
        {
            std::cout<<"用户名为"<<recv_buf<<"的用户加入"<<std::endl;
            sprintf(clientname,"%s",recv_buf);
            char tempbuf[200];
            int j;
            char s[] = "你好！";
            j = sprintf(tempbuf,"%s",recv_buf);
            sprintf(tempbuf+j,"%s",s);     
            if(send(client_fd,tempbuf,strlen(tempbuf),0)<0)
            {
                recv_buf[ret] = '\0';
                perror("write error");
                break;
            }
        }
        else
        {
            printf("收到客户端%s信息:%s\n",clientname,recv_buf);
            
            if(send(client_fd,recv_buf,ret,0)<0)
            {
                perror("write error");
                break;
            }
        }
        count = 0;
    }
    printf("over \n");
    close(client_fd);
}
 int main()
{    
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;//客户地址
    socklen_t len = 0;//接收长度
    char recv_buf[100];
    char send_buf[100];
    int sock_fd = -1;//监听描述符
    int client_fd = -1;//连接fd

    int ret = -1;
    pthread_t th =-1 ;
    
    signal(SIGPIPE, SIG_IGN);//忽略管道破裂信号
    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    if(-1 == sock_fd)
    {
        perror("socket");
        return -1;
    }
    //printf("sock_fd = %d.\n",sock_fd);
    //2.bind绑定socket 和本机IP 端口
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;//IPV4
    server_addr.sin_port = htons(MY_PORT);//设置端口模式
    server_addr.sin_addr.s_addr = inet_addr(MY_IP);//设置IP
    ret = bind(sock_fd,(struct  sockaddr  *)&server_addr,sizeof(server_addr));
    if(-1 == ret)
    {
        perror("bind");
        return -1;
    }
    DEBUF("绑定成功！\n");
    //3.listen 设 置监听
    ret = listen(sock_fd, BACKLOG);//BACKLOG为排队处理
    if(-1 == ret)
    {
        perror("listen");
        return -1;
    }
    DEBUF("监听成功！\n");
    char serbuf[BUFSIZ];
    while(1)
    {
        //增加 停止服务器的命令
        client_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &len);
        if(-1 == client_fd)
        {
            perror("listen");
            return -1;
        }
        ret = pthread_create(&th ,NULL , func , (void *)&client_fd);//创建线程
        //DEBUF("新用户加入\n");
        if(ret != 0)
        {
            printf("pthread_create error \n");
            return -1;
        } 
        // scanf("%s",serbuf);
		// //用于接收字符串；
		// getchar();
		// if(!strcmp(serbuf,"quit"))
		// 	break;
    }
    close(sock_fd);
    close(client_fd);
    return 0;
}