CC = cc
CF = -Wall -Wextra -g
NAME = SteganPlaza
OBJDIR = obj
SRCS = $(shell find src/ -name '*.c')
OBJS = $(patsubst src/%.c, $(OBJDIR)/%.o, $(SRCS))


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CF) -o $@ $^

$(OBJS): $(OBJDIR)/%.o : src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CF) -c -o $@ $<

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

run:
	@./$(NAME)

.PHONY: all clean fclean re run
