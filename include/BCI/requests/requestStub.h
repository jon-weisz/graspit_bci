#ifndef REQUEST_H
#define REQUEST_H

#include "rpcz/rpcz.hpp"

class Request
{
public:
    void sendRequest();

protected:
    virtual void sendRequestImpl() = 0;
    virtual void callback() = 0;


    rpcz::rpc _rpc;

};

#endif // REQUEST_H
