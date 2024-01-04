NAME = philo
CC = @clang
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address 
RM = @rm -rf

FILES = 

SRCS_DIR = ./src/
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./obj/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c -o $@ $<

all: ../$(NAME)

$(NAME): $(SRCS_DIR)philo.h $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "push_swap compiled"

clean:
	$(RM) $(NAME)

fclean:
	$(RM) $(OBJS) $(NAME) $(OBJS_DIR)

re: fclean $(NAME)

.PHONY: all clean fclean re fre