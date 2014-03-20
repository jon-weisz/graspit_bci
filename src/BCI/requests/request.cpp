#include "BCI/requests/request.h"

Request::Request()
{
}

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
