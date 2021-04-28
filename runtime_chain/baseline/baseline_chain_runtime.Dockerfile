FROM val01:5000/python-base-image:dev-base-3.6
RUN mkdir /env && mkdir /code && pip install Flask

COPY daemon.py /env