CC = gcc
CFLAG = -Wall -Wextra -Werror
SRC = main.c 
SRC_DIR = ./src
SRC_C = $(patsubst %, $(SRC_DIR)/%, $(SRC))
OBJ = $(SRC:.c=.o)
OBJ_DIR = ./obj
OBJ_O = $(patsubst %, $(OBJ_DIR)/%, $(OBJ))
HDIR = include
LIB = libft/libft.a
FILE = 
NAME = minishell
.PHONY: re run rr clean fclean all

all: $(LIB) $(NAME)

%.a:
	@make -C $(dir $@)

clean_lib:
	@make fclean -C $(dir $(LIB))

$(NAME): $(OBJ_DIR) $(OBJ_O)
	@$(CC) -o $@ -I $(HDIR) $(LIB) $(OBJ_O) $(CFLAG)
	@echo "\033[32m$(NAME) done\033[0m"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) -c $< -o $@ -I $(HDIR) $(CFLAG)

clean:
	@rm -rf $(OBJ_O)
	@echo "\033[31mobject files removed\033[0m"

fclean: clean clean_lib
	@rm -rf $(NAME)
	@rm -rf $(OBJ_DIR)
	@echo "\033[31m$(NAME) removed\033[0m"

re: fclean all

run:
	@./$(NAME) $(FILE) | cat -e

rr: re run