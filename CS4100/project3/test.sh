#!/bin/bash

make clean
make

echo "===== TEST 1 ====="
echo -e "A = root 1 [A1 2, A2 3]\nPRINT A" | ./treebuilder

echo ""
echo "===== TEST 2 ====="
echo -e "B = root 5 [X 1, Y 2 [Z 9]]\nPRINT B" | ./treebuilder

echo ""
echo "===== TEST 3 ====="
echo -e "T = root 10 [A 1, B 2, C 3 [D 4, E 5]]\nPRINT T" | ./treebuilder