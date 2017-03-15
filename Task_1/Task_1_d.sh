#!bin/bash

for i in `ls c*.txt`; do
	new=${i:1}
	cp $i newc$new
done