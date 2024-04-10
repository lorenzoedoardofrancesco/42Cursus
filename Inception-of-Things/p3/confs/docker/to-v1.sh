#!/bin/bash

sed -i 's/Dog/Cat/g; s/🐶/🐱/g; s/dog_image_url/cat_image_url/g; s/fetch dog/fetch cat/g; s/thedogapi/thecatapi/g' ./templates/index.html app.py
bash docker-push.sh 1
