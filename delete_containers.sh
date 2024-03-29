#!/bin/bash
source config
# sudo runc delete -f $BASELINE_DRIVER_CONTAINER_ID
# sudo runc delete -f $BASELINE_MAPPER_CONTAINER_ID
# sudo runc delete -f $BASELINE_REDUCER_CONTAINER_ID
docker stop $BASELINE_DRIVER_CONTAINER_ID
docker stop $BASELINE_MAPPER_CONTAINER_ID
docker stop $BASELINE_REDUCER_CONTAINER_ID

docker stop $MOLECULEIPC_DRIVER_CONTAINER_ID
docker stop $MOLECULEIPC_MAPPER_CONTAINER_ID
docker stop $MOLECULEIPC_REDUCER_CONTAINER_ID

docker rm $(docker ps -aq)
