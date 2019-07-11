#ifndef __BASE_SERVER__
#define __BASE_SERVER__

#include <unordered_map>
#include "ConnCtx.h"

namespace XEngine 
{

enum
{
    MAX_EVENT = 9999,
};

class CBaseServer
{
public:
    CBaseServer();
    virtual ~CBaseServer();
    virtual void Init();
    virtual void Run();
    virtual int RpcCall(int fd);
    virtual int RpcDispatch(int fd);
    int OnNewConnection(conn_fd);
private:
    void OnRecvMessage(int fd);
private:
    int m_epoll_fd; 
    int m_listen_fd; 
    int m_tick; 
    std::unordered_map<int, CConnCtx *> *m_ConnStat;
};

}

#endif //__BASE_SERVER__
