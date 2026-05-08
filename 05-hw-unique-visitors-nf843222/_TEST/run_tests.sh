#!/bin/bash
echo '\033[0;33m'"###################################################################" '\033[m'
echo '\033[0;33m'"The following should produce errors" '\033[m'
echo '\033[0;33m'"###################################################################" '\033[m'
echo _TEST/a.out
_TEST/a.out
echo
echo _TEST/a.out log.txt
_TEST/a.out log.txt
echo
echo _TEST/a.out a b 
_TEST/a.out a b 
echo
echo _TEST/a.out a b c
_TEST/a.out a b c
echo 
echo _TEST/a.out a b
_TEST/a.out doesNotExist.txt unique.txt
echo
echo '\033[0;33m'"###################################################################" '\033[m'
echo '\033[0;33m'"The following command should produce the correct report in unique.txt" '\033[m'
echo '\033[0;33m'"###################################################################" '\033[m'
echo _TEST/a.out _TEST/log-grade.txt unique.txt
_TEST/a.out _TEST/log-grade.txt _TEST/unique.txt
echo
echo '\033[0;33m'"###################################################################" '\033[m'
echo '\033[0;33m'"Below is the content of unique.txt" '\033[m'
echo '\033[0;33m'"###################################################################" '\033[m'
cat _TEST/unique.txt
echo
