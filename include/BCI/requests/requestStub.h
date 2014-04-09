#ifndef REQUEST_H
#define REQUEST_H
#include <QObject>
#include "rpcz/rpcz.hpp"

//template <class ServiceStub, class RequestType, class ResponseType>
//class TypedRequest :public Request
//class Request
//{
////typename MyType Request<ServiceStub, RequestType, ResponseType>;
//public:
//    void sendRequest(){
//        try
//        {
//            //stub.run(request, &response, &_rpc, rpcz::new_callback(this, &MyType::callback));
//        }
//        catch(rpcz::rpc_error &e)
//        {
//            std::cout << "RPCZ Error: " << e.what() << std::endl;;
//        }
//        catch(const std::exception &e)
//        {
//            std::cout << "NON RPCZ Error: " << e.what() << std::endl;;
//        }
//    }


//protected:

//    virtual void callback() = 0;


//    rpcz::rpc _rpc;


//protected:
//    ServiceStub stub;
//    RequestType request;
//    ResponseType response;
//};


class Request :public QObject
{
    Q_OBJECT
public:

    void sendRequest(){
           try
           {
               sendRequestImpl();
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

//#define RequestType(ServiceType) Request<#(ServiceType)Service_Stub, #(ServiceType)ServiceRequest, #(ServiceType)Response>

#endif // REQUEST_H
