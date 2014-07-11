#include <pthread.h>
#include <syslog.h>

#define MAXLEN 100
#define MAX_BUSNAME 16+1
#define PORT 29536

#define STATE_NO_BUS 0
#define STATE_BCM 1
#define STATE_RAW 2
#define STATE_SHUTDOWN 3
#define STATE_CONTROL 4

#define PRINT_INFO(...) if(daemon_flag) syslog(LOG_INFO, __VA_ARGS__); else printf(__VA_ARGS__);
#define PRINT_ERROR(...) if(daemon_flag) syslog(LOG_ERR, __VA_ARGS__); else fprintf(stderr, __VA_ARGS__);
#define PRINT_VERBOSE(...) if(verbose_flag && !daemon_flag) printf(__VA_ARGS__);

#ifndef VERSION_STRING
    #define VERSION_STRING "SNAPSHOT"
#endif

#undef DEBUG_RECEPTION

extern int client_socket;
extern char **interface_names;
extern int interface_count;
extern int port;
extern int verbose_flag;
extern int daemon_flag;
extern int state;
extern int previous_state;
extern char bus_name[];
extern char* description;
extern pthread_t statistics_thread;
extern int more_elements;
extern struct sockaddr_in broadcast_addr;
extern struct sockaddr_in saddr;

int receive_command(int socket, char *buf);
