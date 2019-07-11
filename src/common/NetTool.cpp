

int Listen(const char *ip, int port, int backlog)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口
    if (0 < bind(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) {
        return -1;
    }

    int listen_fd = listen(fd, 1024);
    
}

int Connect(const char *ip, int port)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    //将套接字和IP、端口绑定
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    pServer->AddToEpoll()
    set_close_on_exec(fd);
    if (0 > connect(fd, (struct sockaddr*)&addr, sizeof(addr))) {
        if (!block && errno == EINPROGRESS) {
            return fd; 
        }   
        perror("fs net connect");
        close(fd);
        return -1; 
    }   

    return fd;
}

int SetCloseOnExec(int fd)
{
    int flag = fcntl(fd, F_GETFD, 0);
    int result = fcntl(fd, F_SETFD, flag | FD_CLOEXEC);
    return result;
}


int SetBlock(int fd, int block, int *oldflag)
{
    int flag = fcntl(fd, F_GETFL, 0); 
    if (oldflag != NULL) {
        *oldflag = flag;
    }   
    return fcntl(fd, F_SETFL, block == 0 ? flag | O_NONBLOCK : flag & (~O_NONBLOCK));
}

