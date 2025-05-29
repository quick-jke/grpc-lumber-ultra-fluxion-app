#include <iostream>

#include "server_impl.hpp"


int main(){

    ServerImpl app;

    app.run(50051);

    
    return 0;
}