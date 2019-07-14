#ifndef __MSG_ID__
#define __MSG_ID__

struct sMsgHeader {
    uint32_t packet_len;
    uint16_t reserve;
    uint16_t msg_id;
};

enum  {
   MSG_CHECK_VERSION  = 1, //检查版本号
   MSG_CLIENT_AUTH  = 2,
   MSG_CLIENT_LOGIN  = 3,
   MSG_CLIENT_RPC  = 3,

};

#endif //__RPC__

