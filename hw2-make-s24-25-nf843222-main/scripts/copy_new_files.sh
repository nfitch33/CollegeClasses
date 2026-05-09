#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
TEMPLATE_PATH=$SCRIPT_DIR/../

if [ -d tmp/ ]; then
  rm -rf tmp
fi

# Clone into a tmp dir
git clone $1 tmp

pushd tmp

# Switching over to my own branch.
git switch -c krerkkiat/fix-grading-scripts

# Copy problem.toml files.
problem_files=(".github/workflows/grading.yml" "requirements.txt" "broken-shell/problem.toml" "odd-or-even-makefile/problem.toml" "sandstorm/problem.toml" "simple-project/problem.toml")
for f in ${problem_files[@]}; do
  echo "cp ${TEMPLATE_PATH}${f} to ./${f}"
  cp ${TEMPLATE_PATH}${f} ./$f
done

# Copy scripts/ folder.
folders=("broken-shell/scripts" "odd-or-even-makefile/scripts" "sandstorm/scripts" "simple-project/scripts")
for f in ${folders[@]}; do
  echo "cp -r ${TEMPLATE_PATH}${f} to ./${f}"
  cp -r ${TEMPLATE_PATH}${f}/* ./$f
done

# Make a commit and push it out.
git add .
git commit -m "fix: fix grading scripts"
git push -u origin krerkkiat/fix-grading-scripts

# Create a PR.
gh pr create --title "New version of the grading scripts" --body "Merge this PR if you want to switch over to the new version. If not, we will merge it when we grade your submission."

popd