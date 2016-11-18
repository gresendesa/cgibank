#!/bin/bash
chmod 777 -R public src/app/views/html > /dev/null
g++ --std=c++11 src/*.cpp include/framework/*.hpp src/framework/*.cpp include/app/views/*.hpp  include/app/*.hpp src/app/views/*.cpp include/app/controllers/*.hpp src/app/controllers/*.cpp src/app/*.cpp -o public/index.cgi 2> compiler-errors.log

if [ "$?" = "0" ]; then
	rm compiler-errors.log
else
	echo "Something is wrong!! Check out the file compiler-errors.log"
	exit 1
fi
