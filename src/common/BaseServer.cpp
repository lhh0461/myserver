#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "BaseServer.h"
#include "ConnCtx.h"

//#include "NetTools.h"

using namespace std;

CBaseServer::CBaseServer()
    :m_epoll_fd(0), m_listen_fd(0)
{

}

CBaseServer::~CBaseServer()
{

}

void CBaseServer::Init()
{
    m_epoll_fd = epoll_create(MAX_EVENT); 
    
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口
    bind(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(fd, 1024);

    m_listen_fd = fd;
    AddFdToEpoll(fd);
}

void CBaseServer::Run()
{
    struct epoll_event events[MAX_EVENT];
    for (;;)
    {
        int nfds = epoll_wait(m_epoll_fd, events, MAX_EVENT, 500);
        //cout << "epoll wait !" << endl;
        for(int i = 0; i < nfds; i++)
        {
            if (events[i].data.fd == m_listen_fd) {
                struct sockaddr addr;
                socklen_t addrlen;
                int conn_fd = accept(m_listen_fd, (struct sockaddr *) &addr, &addrlen);
                cout << "accept connect!" << conn_fd << endl;

                int flag = fcntl(conn_fd, F_GETFL, 0); 
                fcntl(conn_fd, F_SETFL, flag | O_NONBLOCK);

                OnNewConnection(conn_fd);
            }
            else if (events[i].events & EPOLLIN) {
                    OnRecvMessage(events[i].data.fd);
                }
            }
            else if (events[i].events & EPOLLOUT) {
                cout << "accept connect!" << conn_fd << endl;
                }
            }
        }
    }
}

int CBaseServer::OnNewConnection(int conn_fd)
{
    struct epoll_event ev;
    ev.data.fd = conn_fd;
    ev.events = EPOLLIN|EPOLLET;
    epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, conn_fd, &ev);

    CConnCtx * ctx = new ConnCtx();
    
}

void CBaseServer::OnRecvMessage(int fd)
{
    for (;;)
    {
        cout << "recv connect!" << fd  << endl;
        char buf[1024] = {0};
        ssize_t recv_num = ::recv(fd, buf, 1024, 0);
        if (recv_num > 0) {

        }
        else if (recv_num == -1) {
            if (errno == EINTR) {
                continue;
            }
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                continue;
            }
            cout << "errno=" << errno << ",errmsg="  << strerror(errno)  << endl;
            break;
        }

        cout << "recv msg!" << buf <<"123"  << endl;
    }
}
