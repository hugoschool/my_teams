CC	?=	clang
CFLAGS	:=	-Wall -Wextra -std=gnu17
CPPFLAGS	:=	-I ./include -I ./libs/myteams

ifeq ($(ENV), dev)
	CFLAGS	+=	-g3
endif

SERVER_SRC	:= 	src/server/main.c

SERVER_OBJ	:=	$(SERVER_SRC:.c=.o)

SERVER_BINARY	:=	myteams_server

CLI_SRC	:= 	src/cli/main.c

CLI_OBJ	:=	$(CLI_SRC:.c=.o)

CLI_BINARY	:=	myteams_cli

all:	server cli

.PHONY:	server
server:	$(SERVER_BINARY)

.PHONY:	cli
cli:	$(CLI_BINARY)

$(SERVER_BINARY):	$(SERVER_OBJ)
	$(CC) -o $(SERVER_BINARY) $(SERVER_OBJ)

$(CLI_BINARY):	$(CLI_OBJ)
	$(CC) -o $(CLI_BINARY) $(CLI_OBJ)

clean:
	$(RM) $(SERVER_OBJ)
	$(RM) $(CLI_OBJ)

fclean:	clean
	$(RM) $(SERVER_BINARY)
	$(RM) $(CLI_BINARY)

re:	fclean all

.PHONY:	all clean fclean re
