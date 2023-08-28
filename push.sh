#!bin/bash

if [[ $1 ]]; then
	clear
	make fclean -C app
	make clean -C tester
	git add .
	git commit -m " $1 "
	git push origin master
	echo "Repository pushed successfuly!"

else
	echo "Enter a message describing the commit!"
fi