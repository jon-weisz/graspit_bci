#include "BCI/requests/objectRecognitionRequest.h"

ObjectRecognitionServiceRequest::ObjectRecognitionServiceRequest(rpcz::rpc_channel * channel):
    objectRecognition_stub(channel, "Service")
{

}

void ObjectRecognitionServiceRequest::sendRequestImpl()
{
    //objectRecognition_stub.RunObjectRecognition(request,response, &rpc,rpcz::new_callback(this, &ObjectRecognitionServiceRequest::callback));
}

void ObjectRecognitionServiceRequest::callback()
{
    std::cout << "hello world I am a callback!!!!"<< std::endl;
}
