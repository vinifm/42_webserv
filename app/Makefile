#*************
#            *
#    VARS    *
#            *
#*************
NAME=webserv
SOURCES= srcs/Socket.cpp \
		 srcs/main.c

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
