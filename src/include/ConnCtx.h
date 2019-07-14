#ifndef __CONN_CTX__
#define __CONN_CTX__

#include "Buffer.h"

namespace XEngine 
{

enum eConnState
{
    UNAUTH = 1,
    AUTHED = 2,
    VERSION = 3,
};

enum eConnType
{
    CLIENT_TYPE= 1,
    SERVER_TYPE= 2,
};

class CConnCtx
{
public:
    CConnCtx();
    CConnCtx(eConnType type, eConnState state);
    ~CConnCtx();
    CBuffer *GetRecvBuf();
    CBuffer *GetSendBuf();
    int GetVfd() { return m_Vfd; };
    int GetFd() { return m_Fd; };
    int GetType() { return m_Type; };
    int GetState() { return m_State; };
    int SetState(int state) { m_State = state; };
private:
    int m_Vfd;
    int m_Fd;
    int m_Type;
    int m_State;
    CBuffer *m_RecvBuf;
    CBuffer *m_SendBuf;
    void *pUserData;
};

}

#endif //__CONN_CTX__
