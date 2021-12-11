# Python Chain Test
## baseline
``` bash
# Build baseline images. 3 functions are all based on "baseline_chain_runtime_image", whose dockerfile is in runtime_chain/baseline
./build_baseline_images.sh

# Run baseline containers. 3 containers listen 5000, 5001, 5002 port on host respectively
./docker_run_baseline_containers.sh

# Send invoke request to driver
./baseline_send_invoke.sh

# stop all containers
./delete_containers.sh # a little bit slow....
```
## moleculeIPC
``` bash
# Build images with moleculeIPC
./build_moleculeIPC_images.sh

# Run the molecule OS
cd $WHERE_THE_XPU_SHIM_IS (e.g., ../xpu-shim/src)
sudo moleculeos -i 0

# Run 3 containers. For now, we use docker-compose to debug (easier to deploy/delete containers and see the output)
./docker_run_moleculeIPC_containers.sh

# Send invoke request to driver
cd moleculeIPC_client
make
# The client is used to send a message with useless information
sudo ./molecule_rpc_client cfork

```
