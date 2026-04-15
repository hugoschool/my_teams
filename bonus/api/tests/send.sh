#!/usr/bin/env bash

curl --header "Content-Type: application/json" \
  --request POST \
  --data "{\"uuid\": \"$1\", \"body\": \"Hello world!\"}" \
  http://127.0.0.1:8000/send
