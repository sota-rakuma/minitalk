CC = gcc
CFLAGS = -Wall -Wextra -Werror
CLIENT_NAME = client
SERVER_NAME = server
NAME = $(CLIENT_NAME) $(SERVER_NAME)
SHARED_BONUS_SRCS := shared_utils_bonus.c
CLIENT_BONUS_SRCS := client_bonus.c\
			client_utils_bonus.c
SERVER_BONUS_SRCS := server_bonus.c
SHARED_SRCS := shared_utils.c
CLIENT_SRCS := client.c\
			client_utils.c
SERVER_SRCS := server.c
SHARED_OBJS = $(SHARED_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
SHARED_BONUS_OBJS = $(SHARED_BONUS_SRCS:.c=.o)
CLIENT_BONUS_OBJS = $(CLIENT_BONUS_SRCS:.c=.o)
SERVER_BONUS_OBJS = $(SERVER_BONUS_SRCS:.c=.o)
DEPS = $(CLIENT_SRCS:.c=.d) $(SERVER_SRCS:.c=.d) $(SHARED_SRCS:.c=.d) $(SHARED_BONUS_SRCS:.c=.d) $(CLIENT_BONUS_SRCS:.c=.d) $(SERVER_BONUS_SRCS:.c=.d)

ifdef WITH_BONUS
S_OBJS = $(SHARED_BONUS_OBJS) $(SERVER_BONUS_OBJS)
C_OBJS = $(SHARED_BONUS_OBJS) $(CLIENT_BONUS_OBJS)
else
S_OBJS = $(SHARED_OBJS) $(SERVER_OBJS)
C_OBJS = $(SHARED_OBJS) $(CLIENT_OBJS)
endif

.PHONY:all
all: $(NAME)

$(NAME): $(S_OBJS) $(C_OBJS)
	$(CC) $(CFLAGS) -o $(CLIENT_NAME) $(C_OBJS)
	$(CC) $(CFLAGS) -o $(SERVER_NAME) $(S_OBJS)

bonus:
	$(MAKE) WITH_BONUS=1 all

$(CLIENT_OBJS):$(CLIENT_SRCS)
	${CC} ${CFLAGS} -c -MMD -MP -o $@ $*.c

$(SERVER_OBJS):$(SERVER_SRCS)
	${CC} ${CFLAGS} -c -MMD -MP -o $@ $*.c

$(SHARED_OBJS):$(SHARED_SRCS)
	${CC} ${CFLAGS} -c -MMD -MP -o $@ $*.c

$(CLIENT_BONUS_OBJS):$(CLIENT_BONUS_SRCS)
	${CC} ${CFLAGS} -c -MMD -MP -o $@ $*.c

$(SERVER_BONUS_OBJS):$(SERVER_BONUS_SRCS)
	${CC} ${CFLAGS} -c -MMD -MP -o $@ $*.c

$(SHARED_BONUS_OBJS):$(SHARED_BONUS_SRCS)
	${CC} ${CFLAGS} -c -MMD -MP -o $@ $*.c

-include $(DEPS)

.PHONY: clean
clean:
	rm -f $(CLIENT_OBJS) $(SERVER_OBJS) $(SHARED_OBJS) $(CLIENT_BONUS_OBJS) $(SERVER_BONUS_OBJS) $(SHARED_BONUS_OBJS) $(DEPS)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all