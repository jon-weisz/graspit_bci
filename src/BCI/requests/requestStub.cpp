#include "BCI/requests/requestStub.h"


void Request::sendRequest()
{
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
