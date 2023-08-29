#*****************************
#                            *
#    WEBSERV_KINGS - TOUR    *
#                            *
#*****************************
# The project try to implement MVC software arquitecture for a better organization and make software more manutanable.
#
# M (srcs/model): all classes, and builtin functions to make application works;
# V (srcs/view): everything about user interface, our pages and configuration files that deal direct with what the user will see on screen;
# C (srcs/controller): all files that control the software flow, and how models and view connect themselves and the "business rules" of our software;
#
# enjoy the webserv_kings! Thank you very much!
# By lipi, vini and acapela-

#*************
#            *
#    VARS    *
#            *
#*************
NAME=webserv
FLAGS= -Wall -Wextra -Werror -std=c++98 -g3
BANNER_PATH=.banner
SOURCES=	srcs/model/socket/Socket.cpp \
			srcs/model/Utils.cpp \
			srcs/controller/main.cpp

#*******************
#                  *
#     PALLETE      *
#                  *
#*******************
WHITE				=	\e[00m
GREEN				=	\e[32m
RED					=	\e[91m
YELLOW				=	\e[033m
BLUE				=	\e[34m

#*****************
#                *
#   MANDATORY    *
#    TARGETS     *
#                *
#*****************
$(NAME): $(BANNER_PATH)
	c++ -Isrcs/model -Isrcs/model/socket -Isrcs/model/parse $(FLAGS) $(SOURCES) -o $(NAME)

all: $(NAME)

bonus: all

re:
	make fclean
	make

clean:
	find . -maxdepth 1 -type f ! -name "Makefile" ! -name "webserv" ! -name ".banner" ! -name "log" -delete

fclean:
	make clean
	rm -rfd $(NAME) .banner log

.PHONY: all clean fclean re

#******************
#                 *
#     SPECIAL     *
#     TARGETS     *
#                 *
#******************
$(BANNER_PATH):
	@printf "\
                                                               \n\
                                                               \n\
                                                               \n\
  ██╗       ██╗███████╗██████╗  ██████╗███████╗██████╗ ██╗   ██╗\n\
  ██║  ██╗  ██║██╔════╝██╔══██╗██╔════╝██╔════╝██╔══██╗██║   ██║\n\
  ╚██╗████╗██╔╝█████╗  ██████╦╝╚█████╗ █████╗  ██████╔╝╚██╗ ██╔╝\n\
   ████╔═████║ ██╔══╝  ██╔══██╗ ╚═══██╗██╔══╝  ██╔══██╗ ╚████╔╝ \n\
   ╚██╔╝ ╚██╔╝ ███████╗██████╦╝██████╔╝███████╗██║  ██║  ╚██╔╝  \n\
    ╚═╝   ╚═╝  ╚══════╝╚═════╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝   ╚═╝   \n\
                    By lipi, vini & acapela-                    \n\
                                                               \n\
                                                               \n\
" > $(BANNER_PATH)

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
