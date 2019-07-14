#ifndef __LOGIC_SERVER__
#define __LOGIC_SERVER__

#include "BaseServer.h"

namespace XEngine 
{

class CLogicServer : public CBaseServer
{
public:
    CLogicServer();
    ~CLogicServer();
    void Init();
    void Run();
    int RpcCall(int fd);
    int RpcDispatch(int fd);
    int OnNewConn(int conn_fd);
};

}

#endif //__LOGIC_SERVER__
