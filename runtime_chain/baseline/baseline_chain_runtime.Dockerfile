FROM ddnirvana/python-base-image:dev-base-3.6
RUN mkdir /env && mkdir /code && pip install Flask requests

COPY daemon.py /env
