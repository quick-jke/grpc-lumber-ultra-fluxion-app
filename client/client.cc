#include <iostream>
#include "QueueStreamingClient.hpp"


int main(){

    std::string connection_string = "localhost:50051";
    QueueStreamingClient service(connection_string);

#ifdef PUSH_CLIENT
    service.Push();
#elif POP_CLIENT
    service.Pop();
#endif

    return 0;

}