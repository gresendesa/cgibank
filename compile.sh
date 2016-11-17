#!/bin/bash
chmod 777 -R public > /dev/null
g++ --std=c++11 src/*.cpp src/framework/include/*.hpp src/framework/*.cpp src/app/include/views/*.hpp src/app/views/*.cpp -o public/index.cgi 2> compiler-errors.log

if [ "$?" = "0" ]; then
	rm compiler-errors.log
else
	echo "Something is wrong!! Check out the file compiler-errors.log"
	exit 1
fi
