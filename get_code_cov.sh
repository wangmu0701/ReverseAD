#!/bin/bash
for filename in `find ./ReverseAD/test/regression | egrep '\.cpp'`;
do
  gcov -n -o ./ReverseAD/test/regression/ $filename;
done
