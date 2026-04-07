CC	?=	clang
CFLAGS	:=	-Wall -Wextra -std=gnu17
CPPFLAGS	:=	-I ./include -I ./libs/myteams
LDFLAGS	:= -L ./libs/myteams
LDLIBS	:=	-lmyteams -luuid

ifeq ($(ENV), dev)
	CFLAGS	+=	-g3
endif

UTILS_SRC	:=	src/utils/remove_crlf.c \
				src/utils/strccount.c \
				src/utils/strcmp_end.c \
				src/utils/strcmp_start.c \
				src/utils/get_arg.c \
				src/utils/arg_amount.c \
				src/utils/read_bytes_from_arg_nb.c

SERVER_SRC	:= 	$(UTILS_SRC) \
				src/server/main.c \
				src/server/args.c \
				src/server/server.c \
				src/server/poller.c \
				src/server/socket.c \
				src/server/poll.c \
				src/server/clients.c \
				src/server/client_data.c \
				src/server/users.c \
				src/server/user_data.c \
				src/server/messages.c \
				src/server/message_data.c \
				src/server/teams.c \
				src/server/team_data.c \
				src/server/channels.c \
				src/server/channel_data.c \
				src/server/threads.c \
				src/server/thread_data.c \
				src/server/comments.c \
				src/server/comment_data.c \
				src/server/texts.c \
				src/server/text_data.c

# Commands
SERVER_SRC	+=	src/server/commands/handler.c \
				src/server/commands/login.c \
				src/server/commands/logout.c \
				src/server/commands/users.c \
				src/server/commands/user.c \
				src/server/commands/message_send.c \
				src/server/commands/messages.c \
				src/server/commands/create_team.c \
				src/server/commands/teams.c \
				src/server/commands/team.c \
				src/server/commands/subscribe_team.c \
				src/server/commands/unsubscribe_team.c \
				src/server/commands/subscribed.c \
				src/server/commands/list_subscribed_users.c \
				src/server/commands/create_channel.c \
				src/server/commands/channel.c \
				src/server/commands/channels.c \
				src/server/commands/create_thread.c \
				src/server/commands/threads.c \
				src/server/commands/thread.c \
				src/server/commands/create_comment.c \
				src/server/commands/comments.c \
				src/server/commands/create_text.c

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
	$(CC) -o $(SERVER_BINARY) $(SERVER_OBJ) $(LDFLAGS) $(LDLIBS)

$(CLI_BINARY):	$(CLI_OBJ)
	$(CC) -o $(CLI_BINARY) $(CLI_OBJ) $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(SERVER_OBJ)
	$(RM) $(CLI_OBJ)

fclean:	clean
	$(RM) $(SERVER_BINARY)
	$(RM) $(CLI_BINARY)

re:	fclean all

dev-server:	all
	LD_LIBRARY_PATH=./libs/myteams ./myteams_server 4242

.PHONY:	all clean fclean re
