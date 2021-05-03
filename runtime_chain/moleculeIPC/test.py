import moleculeIPC

fifo_self, global_fifo = moleculeIPC.init_server()
while(True):
    message = moleculeIPC.receive_from_server(fifo_self, global_fifo)
    print("response: %s" %message)
