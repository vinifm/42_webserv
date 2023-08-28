SERVER=webserv
CLIENT=client

$(SERVER):
	c++ server.cpp -o $(SERVER)

$(CLIENT):
	c++ client.cpp -o $(CLIENT)

all: 
	make $(SERVER)
	make $(CLIENT)

fclean:
	rm -rfd $(SERVER) $(CLIENT)

re:
	make fclean
	make

runserver:
	make re
	./$(SERVER)

runclient:
	make re
	./$(CLIENT)

