#!/bin/bash
source config
docker-compose --env-file config up

# Run driver containers
# docker run -itd --rm  \
#     -v /tmp/fifo_dir/:/tmp/fifo_dir \
#     -e FUNC_NAME=moleculeIPC_driver \
#     -e NEXT_FUNC=moleculeIPC_mapper \
#     -e IPC_UUID=$MOLECULEIPC_DRIVER_IPC_UUID \
#     -e NEXT_UUID=$MOLECULEIPC_MAPPER_IPC_UUID \
#     --net=host --ipc=host \
#     --name $MOLECULEIPC_DRIVER_CONTAINER_ID \
#     $MOLECULEIPC_DRIVER_IMAGE 

# sleep 1s

# docker run -itd --rm  \
#     -v /tmp/fifo_dir/:/tmp/fifo_dir \
#     -e FUNC_NAME=moleculeIPC_mapper \
#     -e NEXT_FUNC=moleculeIPC_reducer \
#     -e IPC_UUID=$MOLECULEIPC_MAPPER_IPC_UUID \
#     -e NEXT_UUID=$MOLECULEIPC_REDUCER_IPC_UUID \
#     --net=host --ipc=host \
#     --name $MOLECULEIPC_MAPPER_CONTAINER_ID \
#     $MOLECULEIPC_MAPPER_IMAGE 

# sleep 1s

# docker run -itd --rm  \
#     -v /tmp/fifo_dir/:/tmp/fifo_dir \
#     -e FUNC_NAME=moleculeIPC_reducer \
#     -e IPC_UUID=$MOLECULEIPC_REDUCER_IPC_UUID \
#     --net=host --ipc=host \
#     --name $MOLECULEIPC_REDUCER_CONTAINER_ID \
#     $MOLECULEIPC_REDUCER_IMAGE 