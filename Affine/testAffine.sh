#! /bin/bash

#this script isn't very great

infile=$(cat ./testFile)

echo "Test file size: $(stat --printf="%s" "./testFile") bytes." #unsanitized input - make sure your input file is just letters

echo "Encrypting test file. Execution time:"
time ./affine "$infile" -e 17 5

encrypted=$(./affine "$infile" -e 17 5) #lazy way to capture output seperately to time

echo "Decrypting test output. Execution time:"
time ./affine "$encrypted" -d 17 5
