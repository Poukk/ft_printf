#------------------ Config -----------------#
NAME = libftprintf.a

#---------------- Variables ----------------#
CC = gcc
CFLAGS = -Wall -Wextra -Werror -O2
DEPFLAGS = -MMD -MP
INCLUDES = -I./include

SRCDIR = src
OBJDIR = obj
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS = $(OBJS:.o=.d)

GREEN = \033[0;32m
RESET = \033[0m

#----------------- Targets ----------------#
all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@echo "$(GREEN)Created object directory$(RESET)"

$(NAME): $(OBJDIR) $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(GREEN)Library $(NAME) created successfully!$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@

-include $(DEPS)

clean:
	@rm -rf $(OBJDIR)
	@rm -f run_test
	@echo "$(GREEN)Cleaned object files$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN)Cleaned library$(RESET)"

re: fclean all

.PHONY: all clean fclean re
