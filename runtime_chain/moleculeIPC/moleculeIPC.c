#include "moleculeIPC.h"

void init_server(int* fifo_self_ptr, int* global_fifo_ptr, int uuid){
    int fifo_self;
	int global_fifo;
	register_self_global(GLOBAL_OS_PORT); //server always use the default globalOS

	fprintf(stderr, "[liu] init global_fifo with uuid: 0x%x\n", uuid);
	fifo_self = fifo_init_uuid(uuid);
	//Here, the getpid is the uuid used in local fifo
	fprintf(stderr, "[liu] init global_fifo with uuid: 0x%x\n", uuid);
	//global_fifo = global_fifo_init_uuid(getpid(), uuid);
	global_fifo = global_fifo_init_uuid(uuid, uuid);
	fprintf(stderr, "[liu] global_fifo: %d\n", global_fifo);
	*fifo_self_ptr = fifo_self;
	*global_fifo_ptr = global_fifo;
}

char* receive_from_client(int fifo_self, int global_fifo){
	int ret;

	#define MAX_TEST_BUF_SIZE 2048
	char* test_buf = malloc(MAX_TEST_BUF_SIZE);
	ret = global_fifo_read(global_fifo, test_buf, MAX_TEST_BUF_SIZE);

	if (ret == -EFIFOLOCAL){
		ret = fifo_read(fifo_self, test_buf, MAX_TEST_BUF_SIZE);
	}
	return test_buf;
}
