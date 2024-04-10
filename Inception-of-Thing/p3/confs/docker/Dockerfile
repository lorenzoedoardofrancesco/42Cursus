FROM python:3.8-slim
WORKDIR /app
COPY ./app.py /app
COPY ./templates/index.html /app/templates/
RUN pip install --no-cache-dir flask requests
EXPOSE 80
CMD ["python", "app.py"]