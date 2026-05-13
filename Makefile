# ┌────────────────────────────────────────────────────────────────────────────┐
# │                                   NAMES                                    │
# └────────────────────────────────────────────────────────────────────────────┘
NAME		= philo
CFLAGS		= -Wall -Wextra -Werror -I${INCLUDE_DIR}
CC			= cc
INCLUDE_DIR	= ./include
OBJ_DIR		= obj
# ┌────────────────────────────────────────────────────────────────────────────┐
# │                                   SOURCES                                  │
# └────────────────────────────────────────────────────────────────────────────┘
SRC_FILES	= src/main.c \
			  src/messages.c \
			  src/parsing.c \
			  src/utils.c \
			  src/init.c \
			  src/wrappers.c \
			  src/clean.c \
			  src/helpers.c \
			  src/routine_helpers.c \
			  src/routine.c \
			  src/forks.c \
			  src/monitoring.c

OBJ_FILES	= $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

LIBS		= philo.h
# ┌────────────────────────────────────────────────────────────────────────────┐
# │                                   RULES                                    │
# └────────────────────────────────────────────────────────────────────────────┘
all: ${NAME}

${NAME}: ${OBJ_FILES}
			${CC} -o $@ ${OBJ_FILES}

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	${CC} ${CFLAGS} -c $< -o $@


$(OBJ_DIR):
		@mkdir -p $@

clean:
		rm -rf ${OBJ_DIR}

fclean: clean
		rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re