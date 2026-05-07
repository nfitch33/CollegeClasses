#!/bin/bash
# Usage: ./run_agent.sh examples/textbook.pdf "linear algebra" 5

PDF_FILE="$1"
QUERY="$2"
TOP_K="$3"

if [ -z "$PDF_FILE" ] || [ -z "$QUERY" ] || [ -z "$TOP_K" ]; then
    echo "Usage: $0 <PDF_FILE> <QUERY> <TOP_K>"
    exit 1
fi

# Run Textbook Agent
make run PDF="$PDF_FILE" PROMPT="$QUERY" TOP_K="$TOP_K"