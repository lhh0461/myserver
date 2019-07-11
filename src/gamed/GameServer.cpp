#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "BaseServer.h"

using namespace std;

CBaseServer::CBaseServer()
    :m_epoll_fd(0), m_fd(0)
{

}

CBaseServer::~CBaseServer()
{

}

void CBaseServer::Init()
{
    m_epoll_fd = epoll_create(1024); 
    
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口
    bind(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    int listen_fd = listen(fd, 1024);

    struct epoll_event ev;
    ev.data.fd = m_epoll_fd;
    ev.events = EPOLLIN|EPOLLET; //监听读状态同时设置ET模式
    epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, listen_fd, &ev); //注册epoll事件
    m_fd = listen_fd;
}

void CBaseServer::Run()
{
    struct epoll_event events[5];
    for(;;)
    {
        int nfds = epoll_wait(m_epoll_fd, events, 5, -1);
        for(int i = 0; i < nfds; i++)
        {
            if (events[i].events & EPOLLERR) {
                if(events[i].data.fd == m_fd) {
                    cout << "recv connect!" << endl;
                }
            }
        }
    }
}
