NAME		= ft_traceroute

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -Iinclude -g
RM			= rm -f
MKDIR		= mkdir -p

SRCDIR		= src
OBJDIR		= obj
INCDIR		= include
LIBDIR		= lib

SRC			= $(wildcard $(SRCDIR)/*.c) #no wildcard before pushing
OBJ			= $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEP			= $(OBJ:%.o=%.d)

all: $(NAME)

-include $(DEP)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(MKDIR) $(OBJDIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@ -lm

clean:
	@echo "Removing object files..."
	@$(RM) -r $(OBJDIR)

fclean: clean
	@echo "Removing executable..."
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re