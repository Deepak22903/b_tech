#!/bin/bash

string=$1
echo "The string in lowercase is: $(echo "$string" | tr '[:upper:]' '[:lower:]')"
