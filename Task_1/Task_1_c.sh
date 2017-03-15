#!bin/bash

for i in `ls b*.txt`; do
	new=${i:1}
	mv $i newb$new
done
