#!/bin/bash

sed -i 's/Cat/Dog/g; s/🐱/🐶/g; s/cat_image_url/dog_image_url/g; s/fetch cat/fetch dog/g; s/thecatapi/thedogapi/g' ./templates/index.html app.py
bash docker-push.sh 2
