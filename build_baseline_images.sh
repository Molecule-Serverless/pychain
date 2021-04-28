#!/bin/bash
source config
BASEDIR=$PWD
# Build baseline chain runtime image
cd $BASEDIR/runtime_chain/baseline
docker build -t baseline_chain_runtime_image -f baseline_chain_runtime.Dockerfile .

cd $BASEDIR/src/baseline/driver
docker build -t $BASELINE_DRIVER_IMAGE -f baseline_driver.Dockerfile .
sudo rm -rf $BASELINE_DRIVER_BUNDLE/rootfs
sudo mkdir -p $BASELINE_DRIVER_BUNDLE/rootfs
if [[ ! -f "$BASELINE_DRIVER_BUNDLE/config.json" ]]; then
    echo "Cannot find config.json. Paste a new one"
    sudo cp $BASEDIR/runtime_chain/baseline/baseline_chain_config.json $BASELINE_DRIVER_BUNDLE/config.json
fi
sudo docker export `docker create $BASELINE_DRIVER_IMAGE` | sudo tar -C $BASELINE_DRIVER_BUNDLE/rootfs -xf -

cd $BASEDIR/src/baseline/mapper
docker build -t $BASELINE_MAPPER_IMAGE -f baseline_mapper.Dockerfile .
sudo rm -rf $BASELINE_MAPPER_BUNDLE/rootfs
sudo mkdir -p $BASELINE_MAPPER_BUNDLE/rootfs
if [[ ! -f "$BASELINE_MAPPER_BUNDLE/config.json" ]]; then
    echo "Cannot find config.json. Paste a new one"
    sudo cp $BASEDIR/runtime_chain/baseline/baseline_chain_config.json $BASELINE_MAPPER_BUNDLE/config.json
fi
sudo docker export `docker create $BASELINE_MAPPER_IMAGE` | sudo tar -C $BASELINE_MAPPER_BUNDLE/rootfs -xf -

cd $BASEDIR/src/baseline/reducer
docker build -t $BASELINE_REDUCER_IMAGE -f baseline_reducer.Dockerfile .
sudo rm -rf $BASELINE_REDUCER_BUNDLE/rootfs
sudo mkdir -p $BASELINE_REDUCER_BUNDLE/rootfs
if [[ ! -f "$BASELINE_REDUCER_BUNDLE/config.json" ]]; then
    echo "Cannot find config.json. Paste a new one"
    sudo cp $BASEDIR/runtime_chain/baseline/baseline_chain_config.json $BASELINE_REDUCER_BUNDLE/config.json
fi
sudo docker export `docker create $BASELINE_REDUCER_IMAGE` | sudo tar -C $BASELINE_REDUCER_BUNDLE/rootfs -xf -