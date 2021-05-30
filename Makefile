NAME = ft_containers

CC = clang++
CFLAGS = -std=c++98 -Wall -Wextra -Werror

# HEADER = $(addsuffix .hpp, $(HEADER_FILE))

DIR = test/

FILE = \
new_test_vector.cpp \
list.cpp \
map.cpp \
stack.cpp \
queue.cpp \
main.cpp

FILES = $(addprefix $(DIR), $(FILE))

all: $(NAME)

$(NAME): $(FILES)
	@$(CC) -g $(FLAGS) $(FILES) -o $(NAME)
	@./$(NAME)


vector:
	@$(CC) -g $(FLAGS) $(FILES) -o $(NAME)
	@./$(NAME) "vector"

list:
	@$(CC) -g $(FLAGS) $(FILES) -o $(NAME)
	@./$(NAME) "list"

map:
	@$(CC) -g $(FLAGS) $(FILES) -o $(NAME)
	@./$(NAME) "map"

stack:
	@$(CC) -g $(FLAGS) $(FILES) -o $(NAME)
	@./$(NAME) "stack"

queue:
	@$(CC) -g $(FLAGS) $(FILES) -o $(NAME)
	@./$(NAME) "queue"

clean:
	@rm -rf test/list_output test/vector_output test/map_output test/stack_output test/queue_output
	@echo "\033[1;33m clean completed\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[1;31m fclean completed\033[0m"

re: fclean all

.PHONY: all clean fclean re