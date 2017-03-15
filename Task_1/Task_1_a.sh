#!bin/bash
a="a"
b="b"
c="c"

for i in `seq 1 33`; do
   touch > a$i.txt
done
for i in `seq 34 66`; do
   touch > b$i.txt
done
for i in `seq 67 100`; do
   touch > c$i.txt
done

