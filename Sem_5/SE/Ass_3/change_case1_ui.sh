#!/bin/bash

string=$1
echo "The string in uppercase is: $(echo "$string" | tr '[:lower:]' '[:upper:]')"
