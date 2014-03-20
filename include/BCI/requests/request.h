#include "rpcz/rpcz.hpp"

class Request
{
public:
    Request();
    void sendRequest();

protected:
    virtual void sendRequestImpl() = 0;
    virtual void callback() = 0;


    rpcz::rpc rpc;

};
