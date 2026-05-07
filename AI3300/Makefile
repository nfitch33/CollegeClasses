# Makefile for Textbook Agent

# Virtual environment folder
VENV_NAME=venv

# Default target: set up environment
all: setup

# Step 1: Create virtual environment and install dependencies
setup:
	python3 -m venv $(VENV_NAME)
	$(VENV_NAME)/bin/pip install --upgrade pip
	$(VENV_NAME)/bin/pip install -r requirements.txt

# Step 2: Run the agent
# Usage: make run PDF=examples/textbook.pdf PROMPT="linear algebra" TOP_K=5
run:
	@echo "Running Textbook Agent..."
	$(VENV_NAME)/bin/python main.py --pdf $(PDF) --prompt "$(PROMPT)" --top_k $(TOP_K)

# Step 3: Clean virtual environment and generated files
clean:
	rm -rf $(VENV_NAME)