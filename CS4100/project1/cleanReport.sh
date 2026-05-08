#!/bin/bash
# Usage: ./clean_report.sh PlagarismReport.txt
# Shows comparisons with similarity >= 75%

INPUT="$1"
THRESHOLD=0.75  # 75% similarity threshold

if [[ ! -f "$INPUT" ]]; then
    echo "File not found: $INPUT"
    exit 1
fi

# Step 1: Remove Zone.Identifier lines
grep -v "Zone.Identifier" "$INPUT" > temp_clean.txt

# Step 2: Filter lines with similarity >= 75%
awk -v t="$THRESHOLD" '{ if ($NF+0 >= t) print }' temp_clean.txt > PlagarismReport_highSimilarity.txt

# Cleanup
rm temp_clean.txt

echo "High similarity report (>= 75%) saved as PlagarismReport_highSimilarity.txt"