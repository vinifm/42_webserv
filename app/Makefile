#*************
#            *
#    VARS    *
#            *
#*************
NAME=webserv
FLAGS=-Wall -Wextra -Werror -std=c++98 -g3 -fstandalone-debug
BANNER_PATH=srcs/view/.banner
SOURCES=Parser.cpp \
		ParserUtils.cpp \
		ErrorPages.cpp \
		Listen.cpp \
		Location.cpp \
		Server.cpp \
		Socket.cpp \
		SocketUtils.cpp \
		Request.cpp \
		RequestProcessor.cpp \
		RequestProcessorUtils_Access.cpp \
		RequestProcessorUtils_BufferGenerators.cpp \
		RequestProcessorUtils_Extractors.cpp \
		RequestProcessorUtils_Fixers.cpp \
		RequestProcessorUtils_Validators.cpp \
		Response.cpp \
		StatusLine.cpp \
		exception.cpp \
		scripts.cpp \
		main.cpp
OBJECTS_DIR=.objects
INCLUDES_PATH=-I./srcs/model/1_parse/ -I./srcs/model/2_socket/ -I./srcs/model/3_request/ -I./srcs/model/4_response/ -I./srcs/model/5_exception/ -I./srcs/model/6_cgi -I./srcs/controller/ -I./srcs/view/ -I./srcs/controller/
OBJECTS= $(SOURCES:%.cpp=$(OBJECTS_DIR)/%.o)
DS= $(SOURCES:%.cpp=$(OBJETS_DIR)/%.d)

vpath %.cpp srcs srcs/model srcs/model/1_parse srcs/model/2_socket srcs/model/3_request srcs/model/4_response srcs/model/5_exception srcs/model/6_cgi srcs/controller
vpath %.hpp srcs srcs/model srcs/model/1_parse srcs/model/2_socket srcs/model/3_request srcs/model/4_response srcs/model/5_exception srcs/model/6_cgi srcs/controller

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
	mkdir -p srcs/model/1_parse
	mkdir -p srcs/model/2_socket
	mkdir -p srcs/model/3_request
	mkdir -p srcs/model/4_response
	mkdir -p srcs/model/5_exception
	mkdir -p srcs/model/6_cgi
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
	rm -rfd $(NAME) $(BANNER_PATH) log

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
DEFAULT=srcs/view/conf/default.conf
run:
	@make
	@clear
	@rm -rfd log
	@./$(NAME) $(DEFAULT)

runr:
	@make re
	@clear
	@./$(NAME) $(DEFAULT)

runs:
	@make
	@clear
	@valgrind ./$(NAME) $(DEFAULT)

runrs:
	make re
	@clear
	@valgrind ./$(NAME) $(DEFAULT)

runl:
	@make
	@clear
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children-skip='*/bin/*,*/sbin/*' --trace-children=yes ./$(NAME) $(DEFAULT)

runrl:
	@make re
	@clear
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children-skip='*/bin/*,*/sbin/*' --trace-children=yes ./$(NAME) $(DEFAULT)

-include $(DS)
