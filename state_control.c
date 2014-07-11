#include "config.h"
#include "socketcand.h"
#include "statistics.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>
#include <getopt.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <linux/can.h>
#include <linux/can/bcm.h>
#include <linux/can/error.h>

inline void state_control() {
    char buf[MAXLEN];
    int i, items;

    if(previous_state != STATE_CONTROL) {
        PRINT_VERBOSE("starting statistics thread...\n")
        pthread_create(&statistics_thread, NULL, &statistics_loop, NULL);

        previous_state = STATE_CONTROL;
    }

    i = receive_command(client_socket, (char *) &buf);

    if(i != 0) {
        PRINT_ERROR("Connection terminated while waiting for command.\n");
        state = STATE_SHUTDOWN;
        return;
    }

    if(!strncmp("< statistics ", buf, 13)) {
        items = sscanf(buf, "< %*s %u >",
            &i);

        if (items != 1) {
            PRINT_ERROR("Syntax error in statistics command\n")
        } else {
            statistics_ival = i;
        }
    } else if(!strcmp("< rawmode >", buf)) {
        pthread_cancel(statistics_thread);
        state = STATE_RAW;
        strcpy(buf, "< ok >");
        send(client_socket, buf, strlen(buf), 0);
        return;
    } else if(!strcmp("< bcmmode >", buf)) {
        pthread_cancel(statistics_thread);
        state = STATE_BCM;
        strcpy(buf, "< ok >");
        send(client_socket, buf, strlen(buf), 0);
        return;
    } else {
        PRINT_ERROR("unknown command '%s'.\n", buf)
        strcpy(buf, "< error unknown command >");
        send(client_socket, buf, strlen(buf), 0);
    }
}
