#!/bin/bash

# Make sure the script stops if any command fails
set -e

echo "Cleaning old builds..."
make clean

echo "Building scanner..."
make

# Run scanner on each input file
echo -e "\nRunning scanner on input1.txt..."
./scanner < input1.txt

echo -e "\nRunning scanner on input2.txt..."
./scanner < input2.txt

echo -e "\nRunning scanner on input3.txt..."
./scanner < input3.txt

echo -e "\nAll done."