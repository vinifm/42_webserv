#*************
#            *
#    VARS    *
#            *
#*************
NAME=webserv
SOURCES= srcs/Socket.cpp \
		srcs/Utils.cpp \
		 srcs/main.cpp
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
#   this part is temporary  *
#     for debug reasons!    *
#                           *
#****************************
run:
	@clear
	@./$(NAME)

runr:
	@make re
	@clear
	@./$(NAME)

runs:
	@clear
	@valgrind ./$(NAME)

runrs:
	make re
	@clear
	@valgrind ./$(NAME)

runl:
	@clear
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children-skip='*/bin/*,*/sbin/*' --trace-children=yes ./$(NAME)

runrl:
	@make re
	@clear
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children-skip='*/bin/*,*/sbin/*' --trace-children=yes ./$(NAME)
