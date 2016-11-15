#!/bin/bash
chmod 777 -R files bin/assets
g++ source/*.cpp source/core/*.cpp source/core/*.hpp source/http/*.cpp -o bin/index.cgi 2> compiler-errors.log
if [ "$?" = "0" ]; then
	rm compiler-errors.log
else
	echo "Something is wrong!! Check out the file compiler-errors.log"
	exit 1
fi