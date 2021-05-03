#ifndef MOLECULEIPC_H
#define MOLECULEIPC_H

#include "common/common.h"
#include <molecule-ipc.h>
#include <chos/errno.h>
#include <global_syscall_protocol.h>
#include <global_syscall_interfaces.h>
#include <string.h>

void init_server(int* fifo_self_ptr, int* global_fifo_ptr, int uuid);
char* receive_from_client(int fifo_self, int global_fifo);

#endif