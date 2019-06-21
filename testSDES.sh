#! /bin/bash

echo "Test file size: $(stat --printf="%s" "./testFile") bytes."

echo "Encrypting test file. Execution time:"
time ./sdes -e "./testFile" "./encryptedTestFile" "password"

echo "Decrypting test file. Execution time:"
time ./sdes -d "./encryptedTestFile" "./testFileOut" "password"

if !(diff -q "./testFile" "./testFileOut")
  then
    echo "Error: Input and resultant decrypted file differ. Failure in consistency."
  else
    echo "Input files and resultant decrypted file identical. Success!"
fi
