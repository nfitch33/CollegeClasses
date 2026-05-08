Run:
In terminal:
    make
# Creates scanner, tokens.txt etc. Everything in the make file

    ./PlagarismDetector Examples
# This does the detector over Examples folder

    ./cleanReport.sh PlagarismReport.txt
# This will show any files that have an x% of similarity. Currently I have x set to 75%
# The top of the page is 100% and moves down as you go by line. 
# 