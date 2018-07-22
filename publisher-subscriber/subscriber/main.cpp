#include <stdlib.h>
#include <string.h>
#include "zmq.h"

int main(int argc, char *argv[])
{
    void* context = zmq_ctx_new();
    void* subscriber = zmq_socket(context, ZMQ_SUB);
    printf("Collecting stock information from the server.\n");
    int conn = zmq_connect(subscriber, "tcp://localhost:4040");
    conn = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, 0, 0);
    int i;
    for(i = 0; i < 10; i++) {
    zmq_msg_t reply;
    zmq_msg_init(&reply);
    zmq_msg_recv(&reply, subscriber, 0);
    int length = zmq_msg_size(&reply); // menentukan panjang dari reply
    char* value = (char*)malloc(length); // alokasi panjang dari memori untuk menampung reply
    memcpy(value, zmq_msg_data(&reply), 8);
    zmq_msg_close(&reply);
    printf("%s\n", value);
    free(value);
    }
    zmq_close(subscriber);
    zmq_ctx_destroy(context);
    return 0;
}
