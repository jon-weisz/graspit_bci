#include "BCI/requests/objectRecognitionStub.h"

ObjectRecognitionStub::ObjectRecognitionStub(rpcz::rpc_channel * channel):
    objectRecognition_stub(channel, "RecognitionService", true)
{

}

void ObjectRecognitionStub::sendRequestImpl()
{
    objectRecognition_stub.RunObjectRecognition(request,&response, &_rpc,rpcz::new_callback(this, &ObjectRecognitionStub::callback));
}

void ObjectRecognitionStub::callback()
{
    std::cout << "hello world I am a callback!!!!"<< std::endl;
}
