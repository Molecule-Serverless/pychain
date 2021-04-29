FROM baseline_chain_runtime_image
COPY index.py /code
CMD ["python", "/env/daemon.py"]