#include <stdlib.h>
#include <string.h>
#include "zmq.h"

int main(int argc, char *argv[])
{
    void* context = zmq_ctx_new();
    void* subscriber = zmq_socket(context, ZMQ_SUB);

    const char* filter;

    filter = "Company1";

    printf("Collecting information from server");

    int conn = zmq_connect(subscriber, "tcp://localhost:4040");

    conn = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, filter, strlen(filter));

    int i = 0;

    for(i = 0; i < 20; i++) {
        zmq_msg_t reply;
        zmq_msg_init(&reply);
        zmq_msg_recv(&reply, subscriber, 0);

        int length = zmq_msg_size(&reply);
        char* value = (char*) malloc(length + 1);
        memcpy(value, zmq_msg_data(&reply), length);
        zmq_msg_close(&reply);
        printf("%s\n", value);
        free(value);
    }

    zmq_close(subscriber);
    zmq_ctx_destroy(context);
}
