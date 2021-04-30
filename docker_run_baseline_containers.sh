#!/bin/bash
source config
# docker-compose -f docker-compose-baseline.yml --env-file config up

BASE_ENV="-e LC_ALL=C.UTF-8 -e LANG=C.C.UTF-8"
# Run driver containers
docker run -itd --rm $BASE_ENV \
    -e FUNC_NAME=baseline_driver \
    -e NEXT_FUNC=baseline_mapper \
    -e FLASK_PORT=5000 \
    -e NEXT_FUNC_PORT=5001 \
    --net=host \
    --name $BASELINE_DRIVER_CONTAINER_ID \
    $BASELINE_DRIVER_IMAGE

# Run mapper containers
docker run -itd --rm $BASE_ENV \
    -e FUNC_NAME=baseline_mapper \
    -e NEXT_FUNC=baseline_reducer \
    -e FLASK_PORT=5001 \
    -e NEXT_FUNC_PORT=5002 \
    --net=host \
    --name $BASELINE_MAPPER_CONTAINER_ID \
    $BASELINE_MAPPER_IMAGE

# Run reducer containers
docker run -itd --rm $BASE_ENV \
    -e FUNC_NAME=baseline_reducer \
    -e FLASK_PORT=5002 \
    --net=host \
    --name $BASELINE_REDUCER_CONTAINER_ID \
    $BASELINE_REDUCER_IMAGE