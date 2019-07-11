#include "BaseServer.h"

int main()
{
    CBaseServer *pServer = new CBaseServer();
    pServer->Init();
    pServer->Run();
}
