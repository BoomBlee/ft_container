NAME = ft_containers

CC = clang++
CFLAGS = -std=c++98 -Wall -Wextra -Werror

# HEADER = $(addsuffix .hpp, $(HEADER_FILE))

DIR = test/

FILE = \
new_test_vector.cpp \
list.cpp \
main.cpp

FILES = $(addprefix $(DIR), $(FILE))

all: $(NAME)

$(NAME): $(FILES)
	@$(CC) -g $(FLAGS) $(FILES) -o $(NAME)
	@./$(NAME)


vector:
	@$(CC) -g $(FLAGS) test/new_test_vector.cpp -o vector
	@./vector
	@rm vector

list:
	@$(CC) -g $(FLAGS) test/list.cpp -o list
	@./list
	@rm list

# $(NAME): $(SRCS) # $(HEADER)
# 	@$(CC) -g $(FLAGS) $(SRCS) -o $(NAME)
# 	@echo "\033[1;32m Identify created\033[0m"

clean:
	@rm -rf test/list_output test/vector_output
	@echo "\033[1;33m clean completed\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[1;31m fclean completed\033[0m"

re: fclean all

.PHONY: all clean fclean re