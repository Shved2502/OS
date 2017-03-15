#bin/bash

echo "Enter string"
read string
grep "$string" search.txt > result.txt
