NAME = philo

SRC = srcs/philosophers.c \
			srcs/input_parsing.c \
			srcs/time_handler.c \
			srcs/threads.c \
			srcs/routine.c \
			srcs/clean_memory.c

OBJS = $(SRC:.c=.o)
# BONUS_OBJS = $(BONUS_SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -gdwarf-4
RM = rm -rf
AR = ar crs

# Regola per creare l'eseguibile
$(NAME): $(OBJS)
	@$(CC) -o $@ $(CFLAGS) $^
	@echo "\033[32m$(NAME) compiled :D\033[0m"

# $(BONUS): $(BONUS_OBJS) $(LIBFT)
#@$(CC) -o $@ $(CFLAGS) $^ -Llibft -lft
#@echo "\033[32m$(BONUS) compiled :D\033[0m"

# Regola per creare i file .o
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Regola all
all: $(NAME)

# Pulizia degli oggetti
clean:
	@$(RM) $(OBJS)

# Pulizia completa
fclean: clean
	@$(RM) $(NAME) 

# Ricostruzione completa
re: fclean all

.PHONY: all clean fclean re bonus
