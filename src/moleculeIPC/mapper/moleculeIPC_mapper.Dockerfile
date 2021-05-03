FROM moleculeipc_chain_runtime_image
# COPY index.py /code
COPY / /code
CMD ["python", "/env/daemon.py"]