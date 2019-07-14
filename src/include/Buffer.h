#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <list>
#include <string>

class CBuffer
{
public:
    CBuffer();
    CBuffer(int size);
    ~CBuffer();
public:
    void *operator new(size_t size);
    void operator delete(void *ptr);
public:
    CBuffer & operator<<(const uint32_t i);
    CBuffer & operator<<(const uint16_t i);
    CBuffer & operator<<(const uint8_t i);
    CBuffer & operator<<(const uint64_t i);
    CBuffer & operator<<(const float i);
    CBuffer & operator<<(const std::string &str);
public:
    CBuffer & operator>>(uint32_t &i);
    CBuffer & operator>>(uint16_t &i);
    CBuffer & operator>>(uint8_t &i);
    CBuffer & operator>>(uint64_t &i);
    CBuffer & operator>>(float &i);
    CBuffer & operator>>(std::string &str);
public:
    char *GetBufData();
    int GetDataLen();
    int SetDataLen(int size);
    int GetBufTotalLen();
    int ReSize(size_t size);
private:
    char *buf;
    int end;
    int tail;
    int head;
};

class CMemBlockPool
{
public:
    CMemBlockPool();
    ~CMemBlockPool();
public:
    std::list<CBuffer *>m_FreeBuffer;
};

#endif //__BUFFER_H__

