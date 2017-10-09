#!/bin/bash
$1 $2

./a.out < in.txt > stud.txt

echo "The Difference is "
diff out.txt stud.txt
echo "******************"
