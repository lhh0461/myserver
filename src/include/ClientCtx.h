#ifndef __BASE_SERVER__
#define __BASE_SERVER__

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
    ~CConnCtx();
    CBuffer *GetRecvBuf();
    CBuffer *GetSendBuf();
    int GetFd() { return m_Fd };
    int GetType() { return m_Type; };
    int GetState() { return m_State };
    int SetState(int state) { m_State = state };
private:
    int m_Fd;
    int m_Type;
    int m_State;
    CBuffer *m_RecvBuf;
    CBuffer *m_SendBuf;
    void *pUserData;
};

}

#endif //__BASE_SERVER__
