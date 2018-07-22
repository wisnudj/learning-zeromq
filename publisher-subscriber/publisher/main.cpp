/*
* Stock Market Server
* Binds PUB socket to tcp://*:4040
* Publishes random stock values of random companies
*/

#include <string.h>
#include "zmq.h"

int main(int argc, char *argv[])
{
    void* context = zmq_ctx_new();
    void* publisher = zmq_socket(context, ZMQ_PUB);
    printf("Starting server...\n");
    int conn = zmq_bind(publisher, "tcp://*:4040");
    const char* companies[2] = {"Company1", "Company2"};
    int count = 0;
    for(;;) {
        int price = count % 2;
        int which_company = count % 2;
        int index = strlen(companies[0]);
        char update[12];
        snprintf(update, sizeof update, "%s", companies[which_company]);
        printf(update);
        zmq_msg_t message;
        zmq_msg_init_size(&message, index);
        memcpy(zmq_msg_data(&message), update, index); // memasukkan string update ke message
        zmq_msg_send(&message, publisher, 0); //kirim message company1 / company2 yang didapat dari memcpy
        zmq_msg_close(&message);
        count++;
    }
    zmq_close(publisher);
    zmq_ctx_destroy(context);
    return 0;
}
