struct CConnInfo
{
    int fd;
    int state;
}

class CConnWorker : 
    public CBaseWorker
{
public:
    CConnWorker();
    ~CConnWorker();
    virtual void Run();
private:
    std::map<int, ConnInfo*> m_conn_infos;
};

void CConnWorker::Run()
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
