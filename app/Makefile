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
FLAGS=-Wall -Wextra -Werror -std=c++98 -g3
BANNER_PATH=.banner
SOURCES=Conf.cpp \
		Request.cpp \
		Response.cpp \
		RequestUtils.cpp \
		StatusLine.cpp \
		Socket.cpp \
		Utils.cpp \
		main.cpp
INCLUDES_PATH=-I./srcs/model/ -I./srcs/model/socket/ -I./srcs/model/parse/
INCLUDES=Conf.hpp \
		Request.hpp \
		Response.hpp \
		StatusLine.hpp \
		Socket.hpp \
		Utils.hpp
OBJECTS_DIR=.objects
OBJECTS= $(SOURCES:%.cpp=$(OBJECTS_DIR)/%.o)
DS= $(SOURCES:%.cpp=$(OBJETS_DIR)/%.d)

vpath %.cpp srcs srcs/model srcs/model/socket srcs/model/parse srcs/controller
vpath %.hpp srcs srcs/model srcs/model/socket srcs/model/parse srcs/controller

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
all: $(NAME)

$(NAME): $(BANNER_PATH) $(OBJECTS_DIR) $(OBJECTS)
	c++ $(FLAGS) $(OBJECTS) -o $(NAME)

$(OBJECTS_DIR):
	mkdir -p $(OBJECTS_DIR)
	mkdir -p srcs/model
	mkdir -p srcs/model/parse
	mkdir -p srcs/model/socket
	mkdir -p srcs/controller

$(OBJECTS_DIR)/%.o: %.cpp
	c++ $(FLAGS) -c $< -o $@ $(INCLUDES_PATH)

bonus: all

re:
	make fclean
	make

clean:
	find . -maxdepth 1 -type f ! -name "Makefile" ! -name "webserv" ! -name ".banner" ! -name "log" -delete
	rm -rfd $(OBJECTS_DIR)

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
DEFAULT=srcs/view/conf/default
run:
	@clear
	@./$(NAME) $(DEFAULT)

runr:
	@make re
	@clear
	@./$(NAME) $(DEFAULT)

runs:
	@clear
	@valgrind ./$(NAME) $(DEFAULT)

runrs:
	make re
	@clear
	@valgrind ./$(NAME) $(DEFAULT)

runl:
	@clear
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children-skip='*/bin/*,*/sbin/*' --trace-children=yes ./$(NAME) $(DEFAULT)

runrl:
	@make re
	@clear
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children-skip='*/bin/*,*/sbin/*' --trace-children=yes ./$(NAME) $(DEFAULT)

-include $(DS)