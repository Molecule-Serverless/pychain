
//#define FIFO_PATH "/tmp/ipc_bench_fifo"
#define COMMAND_LEN 20
#define MAX_TEST_BUF_SIZE 2048
#define MAXIMUM_CONTAINER_ID_SIZE 64
#define MAXIMUM_BUNDLE_SIZE 256

#define DEFAULT_TEMPLATE_CONTAINER_ID "python-test"
#define DEFAULT_ENDPOINT_CONTAINER_ID "app-test"
#define DEFAULT_CONTAINER_ID "container_id"
#define DEFAULT_ROOTFS ".base/baseline/"

#define COMMAND_RUN_FORMAT "command:run;containerID:%s;bundle:%s"
#define COMMAND_CFORK_FORMAT "command:cfork;template:%s;endpoint:%s"


#define ERROR_ON(err) printf("error: %s\n", err); exit(-1);

enum COMMANDS{
    run,
    cfork,
    send // use to send a single string message, for test
};

typedef struct cfork_args{
    char template[MAXIMUM_CONTAINER_ID_SIZE]; //ID of template container
    char endpoint[MAXIMUM_CONTAINER_ID_SIZE]; //ID of endpoint container
} cfork_args_t;

typedef struct run_args{
    char containerID[MAXIMUM_CONTAINER_ID_SIZE];
    // TODO: Specify the bundle?
    char bundle[MAXIMUM_BUNDLE_SIZE];
} run_args_t;

typedef struct server_args {
	int server_id;
	int os_port;
} server_args_t;

int prepare_command_run_buf(char* test_buf, int argc, char *argv[]);
int prepare_command_cfork_buf(char* test_buf, int argc, char *argv[]);
int prepare_command_send_buf(char* test_buf, int argc, char *argv[]);
int prepare_send_buf(char* test_buf, int argc, char *argv[], enum COMMANDS command);

void parse_cfork_arguments(cfork_args_t *arguments, int argc, char *argv[]);
void parse_run_arguments(run_args_t *arguments, int argc, char *argv[]);
void parse_server_arguments(server_args_t *server_args, int argc, char *argv[]);


#define USAGE \
"USAGE:\n" \
"./molecule_rpc_client <command> -i <server_id> -p <os_port> command_args...\n"\
"\n"\
"DEFAULT ARGS:\n"\
"    os_port: 65259\n"\
"\n"\
"COMMANDS:\n"\
"    run: run a container\n"\
"        ARGS: TODO\n"\
"        DEFAULT ARGS:\n"\
"            TODO\n"\
"\n"\
"    cfork: fork a container from template to endpoint\n"\
"        ARGS: -t <template_container_id> -e <endpoint_container_id>\n"\
"        DEFAULT ARGS:\n"\
"            template_container_id: python-test\n"\
"            endpoint_container_id: app-test\n"\
"\n"\
"    send: send messages to runc\n"\
"        ARGS: TODO\n"\
"        DEFAULT ARGS:\n"\
"            TODO\n"\

