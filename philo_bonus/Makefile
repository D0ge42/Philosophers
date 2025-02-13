NAME = philo_bonus

SRC = srcs/input_parsing.c \
	  srcs/philosophers_bonus.c \
	  srcs/clean_processes.c \
	  srcs/utils.c\
	  srcs/routine.c\
	  srcs/actions.c\
	  srcs/create_bonus.c\
	  srcs/initialize.c\
	  srcs/utils2.c

OBJS = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -gdwarf-4
RM = rm -rf
AR = ar crs

# Regola per creare l'eseguibile
$(NAME): $(OBJS)
	@$(CC) -o $@ $(CFLAGS) $^
	@echo "\033[32m$(NAME) compiled :D\033[0m"

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
