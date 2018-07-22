#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "zmq.h"

int main(int argc, char *argv[])
{
    void* context = zmq_ctx_new();
    void* respond = zmq_socket(context, ZMQ_REP);
    zmq_bind(respond, "tcp://*:4040");

    printf("Starting server... \n");

    for(;;) {
        zmq_msg_t request;
        zmq_msg_init(&request);
        zmq_msg_recv(&request, respond, 0);
        printf("Received: \n");
        zmq_msg_close(&request);

        sleep(1);

        zmq_msg_t msg1, msg2, msg3;
        zmq_msg_init_size(&msg1, 2);
        zmq_msg_init_size(&msg2, 2);
        zmq_msg_init_size(&msg3, 2);

        memcpy(zmq_msg_data(&msg1), "w", 2);
        zmq_msg_send(&msg1, respond, ZMQ_SNDMORE);

        memcpy(zmq_msg_data(&msg2), "o", 2);
        zmq_msg_send(&msg2, respond, ZMQ_SNDMORE);

        memcpy(zmq_msg_data(&msg3), "t", 2);
        zmq_msg_send(&msg3, respond, ZMQ_SNDMORE);

        zmq_msg_close(&msg1);
        zmq_msg_close(&msg2);
        zmq_msg_close(&msg3);
    }

    zmq_close(respond);
    zmq_ctx_destroy(context);

    return 0;
}
