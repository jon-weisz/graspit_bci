#ifndef REQUEST_H
#define REQUEST_H
#include <QObject>
#include "rpcz/rpcz.hpp"


class Request :public QObject
{
    Q_OBJECT
public:

    void sendRequest(QObject * callbackReceiver = NULL, const char * slot = NULL)
    {
        if(callbackReceiver)
        {
            connect(this, SIGNAL(requestComplete()), callbackReceiver, slot);

        }
           try
           {
               sendRequestImpl();
               std::cout << "REQUEST SENT" << std::endl;;
           }
           catch(rpcz::rpc_error &e)
           {
               std::cout << "RPCZ Error: " << e.what() << std::endl;;
           }
           catch(const std::exception &e)
           {
               std::cout << "NON RPCZ Error: " << e.what() << std::endl;;
           }
    }

    void callback()
    {
        std::cout << "RESPONSE RECEIVED" << std::endl;;
        callbackImpl();
        emit requestComplete();
    }

protected:

    virtual void sendRequestImpl() = 0;
    virtual void callbackImpl() = 0;

    rpcz::rpc _rpc;

signals:

    void requestComplete();

};

#endif // REQUEST_H
