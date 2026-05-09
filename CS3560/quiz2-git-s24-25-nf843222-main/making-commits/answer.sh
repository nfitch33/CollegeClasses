#!/bin/bash

mkdir repo
cd repo
git init


touch 80c4a57
git add 80c4a57
git commit -m "First File"
git push

git branch feat-1
git checkout feat-1


touch c76c4de
git add c76c4de
git commit -m "Seperate branch file 1"
git push

touch 882e4fa
git add 882e4fa
git commit -m "Seperate branch file 2"
git push

git checkout master

touch d14463f
git add d14463f
git commit -m "Second File"
git push

git merge feat-1 

cd ..
tar -czvf repo.tar.gz repo
# Please write the rest of the commands to re-create the commit history tree.