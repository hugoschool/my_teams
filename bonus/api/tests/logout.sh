#!/usr/bin/env bash

curl --header "Content-Type: application/json" \
  --request POST \
  http://127.0.0.1:8000/logout
