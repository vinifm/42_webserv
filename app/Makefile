#*************
#            *
#    VARS    *
#            *
#*************
NAME=webserv
SOURCES= srcs/Socket.cpp \
		srcs/Utils.cpp \
		 srcs/main.c
FLAGS= -Wall -Wextra -Werror -std=c++98 -g3

#***************
#              *
#    TARGET    *
#              *
#***************
$(NAME):
	c++ -Isrcs $(SOURCES) -o $(NAME)

all: $(NAME)

fclean:
	rm -rfd $(NAME)

re:
	make fclean
	make

#****************************
#                           *
#    TESTERS & SHORTCUTS    *
#                           *
#****************************
run:
	./$(NAME)

runr:
	make re
	./$(NAME)

runs:
	valgrind ./$(NAME)

runrs:
	make re
	valgrind ./$(NAME)

runl:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children-skip='*/bin/*,*/sbin/*' --trace-children=yes ./$(NAME)

runrl:
	make re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children-skip='*/bin/*,*/sbin/*' --trace-children=yes ./$(NAME)
