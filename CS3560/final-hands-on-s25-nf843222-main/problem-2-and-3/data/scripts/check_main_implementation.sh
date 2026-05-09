#!/bin/bash
#
# This is an internal tooling.
# Use it at your own risks.
#
# Author: Krerkkiat Chusap
#

# Testing with no argument.
./build/count | diff -su "./data/output0.txt" -

# Testing with file as argument.
for i in {1..7};
do
    ./build/count "./data/input$i.txt" | diff -su "./data/output$i.txt" -
done
