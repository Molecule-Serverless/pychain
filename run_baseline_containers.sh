#!/bin/bash
source config

cd $BASELINE_DRIVER_BUNDLE
# TODO: add -d when baseline_driver becomes daemon
sudo $RUNC run -d $BASELINE_DRIVER_CONTAINER_ID
echo "run baseline driver complete"

cd $BASELINE_MAPPER_BUNDLE
# TODO: add -d when baseline_driver becomes daemon
sudo $RUNC run -d $BASELINE_MAPPER_CONTAINER_ID
echo "run baseline mapper complete"

cd $BASELINE_REDUCER_BUNDLE
# TODO: add -d when baseline_driver becomes daemon
sudo $RUNC run -d $BASELINE_REDUCER_CONTAINER_ID
echo "run baseline reducer complete"