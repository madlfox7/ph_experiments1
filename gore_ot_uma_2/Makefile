NAME := philo
OBJ  := ./obj
SRCDIR := .
SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJ)/%.o, $(SRCS))
INCS := -I.
HEADER := $(wildcard *.h)
RM := rm -rf
CC := cc
FLAGS := -Wall -Wextra -Werror #-g3 -fsanitize=address

all: $(OBJ) $(NAME)

$(OBJ)/%.o: $(SRCDIR)/%.c $(HEADER)
	$(CC) $(FLAGS) $(INCS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) 

$(OBJ):
	mkdir -p $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

