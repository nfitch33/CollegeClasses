#!/bin/bash
# Usage:
# ./run_agent.sh examples "Why do plants grow" 5

DIR="$1"
QUERY="$2"
TOP_K="$3"

TOP_K=${TOP_K:-5}

if [ -z "$QUERY" ]; then
    echo "Starting in interactive mode..."
    python3 main.py --dir "$DIR" --top_k "$TOP_K" --interactive
else
    python3 main.py --dir "$DIR" --prompt "$QUERY" --top_k "$TOP_K"
fi