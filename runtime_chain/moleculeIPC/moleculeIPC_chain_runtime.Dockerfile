FROM val01:5000/python-base-image:dev-base-3.6
RUN mkdir /env && mkdir /code 

COPY / /env
RUN cd /env && python3 setup.py build_ext --inplace