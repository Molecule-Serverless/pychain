# Python Chain Test
## baseline
``` bash
# Build baseline images. 3 functions are all based on "baseline_chain_runtime_image", whose dockerfile is in runtime_chain/baseline
./build_baseline_images.sh

# Run baseline containers. 3 containers listen 5000, 5001, 5002 port on host respectively
./run_baseline_containers.sh
```
