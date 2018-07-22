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
    printf("Starting server... \n");

    int conn = zmq_bind(publisher, "tcp://*:4040");

    const char *companies[2] = {"Company1", "Company2"};

    int count = 0;

    for(;;) {
        int price = count % 2;
        int which_company = count % 2;
        int index = strlen(companies[0]);
        char update[12];
        snprintf(update, sizeof update, "%s%d", companies[which_company], price);
        printf(update);
        printf("\n");
        zmq_msg_t message;
        zmq_msg_init_size(&message, 12);
        memcpy(zmq_msg_data(&message), update, 12);
        zmq_msg_send(&message, publisher, 0);
        zmq_msg_close(&message);
        count++;
    }

    zmq_close(publisher);
    zmq_ctx_destroy(context);

    return 0;
}
