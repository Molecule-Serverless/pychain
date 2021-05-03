#!/bin/bash
source config
BASEDIR=$PWD
# Build moleculeIPC chain runtime image
cd $BASEDIR/runtime_chain/moleculeIPC
docker build -t moleculeipc_chain_runtime_image -f moleculeIPC_chain_runtime.Dockerfile .

cd $BASEDIR/src/moleculeIPC/driver
docker build -t $MOLECULEIPC_DRIVER_IMAGE -f moleculeIPC_driver.Dockerfile .

cd $BASEDIR/src/moleculeIPC/mapper
docker build -t $MOLECULEIPC_MAPPER_IMAGE -f moleculeIPC_mapper.Dockerfile .

cd $BASEDIR/src/moleculeIPC/reducer
docker build -t $MOLECULEIPC_REDUCER_IMAGE -f moleculeIPC_reducer.Dockerfile .