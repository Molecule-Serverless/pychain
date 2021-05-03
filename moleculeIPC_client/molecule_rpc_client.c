#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#include "common/common.h"
#include <molecule-ipc.h>
#include <global_syscall_interfaces.h>
#include <global_syscall_protocol.h>
#include "molecule_rpc_client.h"
#include <chos/errno.h>

void parse_server_arguments(server_args_t *server_args, int argc, char *argv[]) {
    // For getopt long options
	int long_index = 0;
	// For getopt chars
	int opt;

	// Reset the option index to 1 if it
	// was modified before (e.g. in check_flag)
	optind = 0;

	// Default values
	server_args->os_port = GLOBAL_OS_PORT;
	// Command line arguments
	// clang-format off
	static struct option long_options[] = {
			{"server Id", required_argument, NULL, 'i'},
			{"global os port", required_argument, NULL, 'p'},
			{0,       0,                 0,     0}
	};
	// clang-format on

	while (true) {
		opt = getopt_long(argc, argv, "+:i:p:h:", long_options, &long_index);

		switch (opt) {
			case -1: return;
			case 'i': server_args->server_id = atoi(optarg); break;
			case 'p': server_args->os_port = atoi(optarg); break;
			default: continue;
		}
	}
}

void parse_cfork_arguments(cfork_args_t *arguments, int argc, char *argv[]) {
    // For getopt long options
	int long_index = 0;
	// For getopt chars
	int opt;
	// Reset the option index to 1 if it
	// was modified before (e.g. in check_flag)
	optind = 0;
    
	// Default values
	strcpy(arguments->template, DEFAULT_TEMPLATE_CONTAINER_ID);
	strcpy(arguments->endpoint, DEFAULT_ENDPOINT_CONTAINER_ID);
    
	static struct option long_options[] = {
			{"template",  required_argument, NULL, 't'},
			{"endpoint", required_argument, NULL, 'e'},
			{0,       0,                 0,     0}
	};

	while (true) {
		opt = getopt_long(argc, argv, ":t:e:", long_options, &long_index);

		switch (opt) {
			case -1: return;
			case 't': strcpy(arguments->template, optarg); break;
			case 'e': strcpy(arguments->endpoint, optarg); break;
			default: continue;
		}
	}
}

void parse_run_arguments(run_args_t *arguments, int argc, char *argv[]) {
    // For getopt long options
	int long_index = 0;
	// For getopt chars
	int opt;
	// Reset the option index to 1 if it
	// was modified before (e.g. in check_flag)
	optind = 0;

	char* default_bundle = (char *)malloc(MAXIMUM_BUNDLE_SIZE);
	sprintf(default_bundle, "%s/%s", getenv("HOME"), DEFAULT_ROOTFS);

	// Default values
	strcpy(arguments->containerID, DEFAULT_CONTAINER_ID);
	strcpy(arguments->bundle, default_bundle);
	free(default_bundle);

	static struct option long_options[] = {
			{"containerID",  required_argument, NULL, 'c'},
			{"bundle",  required_argument, NULL, 'b'},

			{0,       0,                 0,     0}
	};

	while (true) {
		opt = getopt_long(argc, argv, ":c:b:", long_options, &long_index);

		switch (opt) {
			case -1: return;
			case 'c': strcpy(arguments->containerID, optarg); break;
			case 'b': strcpy(arguments->bundle, optarg); break;
			default: continue;
		}
	}
}

int prepare_send_buf(char* test_buf, int argc, char *argv[], enum COMMANDS command){
    switch(command){
        case run: return prepare_command_run_buf(test_buf, argc, argv);
        case cfork: return prepare_command_cfork_buf(test_buf, argc, argv); 
        case send: return prepare_command_send_buf(test_buf, argc, argv); 
        default: ERROR_ON("no such command");
    }
}

int prepare_command_run_buf(char* test_buf, int argc, char *argv[]){
	run_args_t args;
	int size;
	parse_run_arguments(&args, argc, argv);
	size = sprintf(test_buf, COMMAND_RUN_FORMAT, args.containerID, args.bundle);
    if(size < 0){
        ERROR_ON("fail to generate a cfork test_buf");
    }
    test_buf[size] = '\0';
    return size + 1;
}

int prepare_command_cfork_buf(char* test_buf, int argc, char *argv[]){
    cfork_args_t args;
    int size;
    parse_cfork_arguments(&args, argc, argv);
    size = sprintf(test_buf, COMMAND_CFORK_FORMAT, args.template, args.endpoint);
    if(size < 0){
        ERROR_ON("fail to generate a cfork test_buf");
    }
    test_buf[size] = '\0';
    return size + 1;
}

int prepare_command_send_buf(char* test_buf, int argc, char *argv[]){
    memset(test_buf,'l',9);
    test_buf[9] = '\0';
    return 10;
}

int main(int argc, char *argv[]) {
     if (argc < 2){
        ERROR_ON("no specified command");
    }
    
    char* command_str = argv[1];
    enum COMMANDS command;
    if(strcmp(command_str, "run") == 0){
        command = run;
    } 
    else if(strcmp(command_str, "cfork") == 0){
        command = cfork;
    }
    else if(strcmp(command_str, "send") == 0){
        command = send;
    } 
    else if(strcmp(command_str, "help") == 0){
        printf(USAGE);
        exit(0);
    }
    
    else{
        ERROR_ON("No such command. Use \"./molecule_rpc_client help\" to see the usage");
    }

    int fifo_self;
	int global_fifo;
	int fifo_server;

	int i;
    char test_buf[MAX_TEST_BUF_SIZE];
	char send_buf[MAX_TEST_BUF_SIZE];
    //////////////////////// HARD CODING
    int server_id = 175;
    int size = 10;
    /////////////////////// MUST BE DESTROYED
    server_args_t server_args;
    parse_server_arguments(&server_args, argc - 1, argv + 1);
    
    size = prepare_send_buf(test_buf, argc - 1, argv + 1, command);
	int uuid = 1111;
	// make test_buf to json
	size = sprintf(send_buf, "{\"uuid\": %d, \"message\": \"%s\"}", uuid, test_buf);
    printf("port: %d, server_id: %d\n", server_args.os_port, server_args.server_id);

	register_self_global(server_args.os_port);
	fprintf(stderr, "[Client] Before fifo_init\n");
	
	fifo_self = fifo_init_uuid(uuid);
	//global_fifo = global_fifo_init_uuid(getpid(), uuid);
	global_fifo = global_fifo_init_uuid(uuid, uuid);
	
	fifo_server = global_fifo_connect(0x1beef);
	printf("fifo_server in client: %d\n", fifo_server);
	struct timeval tv;
    gettimeofday(&tv,NULL);
    printf("before client send ipc: %ld\n", tv.tv_sec*1000 + tv.tv_usec/1000);

	global_fifo_write(fifo_server, send_buf, size);

	char* receive_buf = malloc(MAX_TEST_BUF_SIZE);
	int ret = global_fifo_read(global_fifo, receive_buf, MAX_TEST_BUF_SIZE);

	if (ret == -EFIFOLOCAL){
		ret = fifo_read(fifo_self, receive_buf, MAX_TEST_BUF_SIZE);
	}
	printf("%s\n", receive_buf);
	return EXIT_SUCCESS;
}
